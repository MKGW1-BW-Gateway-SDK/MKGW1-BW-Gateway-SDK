#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <uci_cmd.h>
#include "blepub.h"

#define MAX_BEACON_DATA 256

#define UART_FIFO_SHM_KEY 0x9999
#define SERV_FIFO_SHM_KEY 0x8888
#define SERV_DISNET_SHM_KEY 0x4321

#define UART_SEM_NAME "/uart"
#define SERV_SEM_NAME "/serv"

static int load_config(blepub_t *bt)
{
	int ret = 0;
	char value[BUF_32] = {0};
	st_serv *serv = &bt->serv;

	uci_get_value("bleserve.blescan.enable", value);
	bt->enable = !!atoi(value);

	uci_get_value("bleserve.custom.enable", value);
	bt->enable &= !!atoi(value);

	
	uci_get_value("bleserve.custom.fifo", value);
	if(str_yes_null(value))
	{
		MSG("Exit Program!\n");
		exit(0);
	}else if(0 == safe_strcasecmp(value, "raw"))
	{
		serv->fifo = RAW_FIFO;
	}else if(0 == safe_strcasecmp(value, "beacon"))
	{
		serv->fifo = BEACON_FIFO;
	}else{
		MSG("Invalid parameter,Exit Program!\n");
		exit(0);
	}
	
	uci_get_value("bleserve.blescan.RawData", value);
	if(atoi(value)) serv->accept |= DT_RawData;
	uci_get_value("bleserve.blescan.iBeacon", value);
	if(atoi(value)) serv->accept |= DT_iBeacon;
	uci_get_value("bleserve.blescan.MkiBeacon", value);
	if(atoi(value)) serv->accept |= DT_MkiBeacon;	
	uci_get_value("bleserve.blescan.MkiBeacon_3Axis", value);
	if(atoi(value)) serv->accept |= DT_MkiBeacon3Axis;
	uci_get_value("bleserve.blescan.MkBeaconX_HT", value);
	if(atoi(value)) serv->accept |= DT_MkBeaconX_HT;
	uci_get_value("bleserve.blescan.MkBeaconX_3Axis", value);
	if(atoi(value)) serv->accept |= DT_MkBeaconX_3Axis;
	uci_get_value("bleserve.blescan.Eddystone_TLM", value);
	if(atoi(value)) serv->accept |= DT_Eddystone_TLM;
	uci_get_value("bleserve.blescan.Eddystone_UID", value);
	if(atoi(value)) serv->accept |= DT_Eddystone_UID;
	uci_get_value("bleserve.blescan.Eddystone_URL", value);
	if(atoi(value)) serv->accept |= DT_Eddystone_URL;

	uci_get_value("bleserve.server.type", value);
	if(0 == safe_strcasecmp(value, "HTTP"))
	{
		serv->mode = SE_HTTP;
		load_httpconf(serv);
	}
	else if(0 == safe_strcasecmp(value, "MQTT"))
	{
		serv->mode = SE_MQTT;
		load_mqttconf(serv);
	}
	else
	{	
		MSG("not support service proto(%s)!!!\n", value);
		ret = -1;
	}
	return ret;
	
}

int init_service(blepub_t *bt)
{
	int ret = 0;
	st_serv *serv = &bt->serv;
	st_uart *uart = &bt->uart;
	char mac[MAC_HEX_LEN] = {0};
	
	if(bt->enable == 0)
		loop_forever();

	if(serv->fifo == RAW_FIFO)
	{
		uart->hsem = sem_open(UART_SEM_NAME, O_CREAT, 0644, 0);
		if(uart->hsem == SEM_FAILED)
		{
			MSG("Open semaphore failed. Name: %s, Reason: %s\n", UART_SEM_NAME, strerror(errno));
			ret = -1;
			goto exit;
		}	
		uart->queue = get_shm_queue(sizeof(iFrame_Data), MAX_BEACON_DATA, UART_FIFO_SHM_KEY);
		if(uart->queue == NULL)
		{
			MSG("get_shm_queue failed. key: 0x%x\n", UART_FIFO_SHM_KEY);
			ret = -1;
			goto exit;
		}
	}
	serv->hsem = sem_open(SERV_SEM_NAME, O_CREAT, 0644, 0);
	if(serv->hsem == SEM_FAILED)
	{
		MSG("Open semaphore failed. Name: %s, Reason: %s\n", SERV_SEM_NAME, strerror(errno));
		ret = -1;
		goto exit;
	}
	
	serv->disnet = new_memint(SERV_DISNET_SHM_KEY);
	set_memint(serv->disnet, 1);
	serv->queue = get_shm_queue(sizeof(iBeacon_Data), MAX_BEACON_DATA, SERV_FIFO_SHM_KEY);
	if(serv->queue == NULL)
	{
		MSG("get_shm_queue failed. key: 0x%x\n", SERV_FIFO_SHM_KEY);
		ret = -1;
		goto exit;
	}

	
	switch(serv->mode)
	{
		case SE_HTTP:
			ret = init_http(serv);
			break;
		case SE_MQTT:
			ret = init_mqtt(serv);
			break;		
		default: 
			ret = -1;
			MSG("not support service proto!!!\n");
			break;
	}
	if(!get_mac_addr("ra0", mac));
		sprintf(serv->macaddr, "%02X%02X%02X%02X%02X%02X", PRINT_MAC(mac));
exit:
	return ret;
}

//parse pop raw data and push them to prased(beacon) data queue
void trans_msg_idata(void *args)
{
	blepub_t *bt =args;
	st_serv *serv = &bt->serv;
	st_uart *uart = &bt->uart;
	iFrame_Data iframe;
	iBeacon_Data idata;
	
	if(serv->fifo == BEACON_FIFO)
		loop_forever();
	
	while(true)
	{			
		sem_wait(uart->hsem);
		if(!shm_queue_pop(uart->queue, &iframe))
			continue;
	
		if(true == pop_idata(serv->accept, &serv->idata, &iframe.addr[iframe.data], iframe.len))
		{
			if(!shm_queue_push(serv->queue, &serv->idata))
			{
				//MSG("serv fifo full..");	
				shm_queue_pop(serv->queue, &idata);
				shm_queue_push(serv->queue, &serv->idata);
			}	
		}
		sem_post(serv->hsem);
	}
}

//pop prased(beacon) data and send them to server
void send_serv_idata(void *args)
{
	bool full = false;
	st_serv *serv = args;
	
	while(true)
	{
		sem_wait(serv->hsem);		
		full = shm_queue_full(serv->queue);
		if( full || (time(NULL) - serv->lastpost >= serv->postintv))
		{
			MSG("send msg(%s)..\n", full ? "full" : "intv"); 
			send_json_data(serv);
		}
	}
	
}

int start_service(blepub_t *bt)
{
	int ret = -1;
	st_serv *serv = &bt->serv;

	if (0 != (ret = pthread_create(&bt->tid, NULL, (void *)trans_msg_idata, bt)))
	{ 
		MSG("Create trans_msg_idata thread failed: %s\n", strerror(ret));
		goto exit;
	}	
	
	if (0 != (ret = pthread_create(&serv->tid, NULL, (void *)send_serv_idata, serv)))
	{ 
		MSG("Create send_serv_idata thread failed: %s\n", strerror(ret));
		goto exit;
	}	

	ret = 0;
exit:
	return ret;
}

int loop_service(blepub_t *bt)
{
	int ret = -1;
	st_serv *serv = &bt->serv;

	pthread_join(bt->tid, NULL);
	pthread_join(serv->tid, NULL);

	ret = 0;
exit:
	return ret;
}

int stop_serv(st_serv *serv)
{
	int ret = 0;

	free_shm_queue(serv->queue); 
	sem_close(serv->hsem);
	put_memint(serv->disnet);
	switch(serv->mode)
	{
		case SE_HTTP:
		    ret = stop_http(serv);
			break;
		case SE_MQTT:
		    ret = stop_mqtt(serv);
			break;		
	    default: 
			ret = -1;
		    MSG("not support service proto!!!\n");
			break;
	}
	
exit:
	return ret;
}

int stop_uart(st_uart *uart)
{
	free_shm_queue(uart->queue); 
	sem_close(uart->hsem);
}


int stop_service(blepub_t *bt)
{
	int ret = -1;
	st_serv *serv = &bt->serv;
	st_uart *uart = &bt->uart;
	if(serv->fifo == RAW_FIFO)
	{
		if(0 != (ret = stop_uart(uart)))
			goto exit;
	}
	if(0 != (ret = stop_serv(serv)))
		goto exit;	
	
	ret = 0;
exit:
    return ret;
}


int main(int argc, char *argv[])
{
	int ret = 0;
	blepub_t bt = {0};	

	if(0 != (ret = load_config(&bt)))
	{
		MSG("load_config error\n");
		goto exit;
	}
	
	if(0 != (ret = init_service(&bt)))
	{
		MSG("init_service error\n");
		goto exit;
	}

	if(0 != (ret = start_service(&bt)))
	{
		MSG("start_service error\n");
		goto exit;
	}
    
	if(0 != (ret = loop_service(&bt)))
	{
		MSG("loop_service error\n");
		goto exit;
	}
	
    if(0 != (ret = stop_service(&bt)))
	{
		MSG("stop_service error\n");
		goto exit;
	}
	
exit:
	return ret;
}

