
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include "mqtt.h"
#include "blepub.h"

static void mqtt_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
	char *pmsg;
	int len;
	int i;
	char *pdata;
	st_serv *serv = userdata;
	mqtt_t *mt = &serv->so.mt;	
	return ;
	if(message->payloadlen)
	{
		MSG("%s %s\n", message->topic, message->payload);
	}
	else
	{
		MSG("%s (null)\n", message->topic);
	}
	pdata=(char*)message->payload;
	pmsg=(char*)malloc(4096);
  
	if(message->topic[0]=='a' && message->topic[1]=='t')
	{
		if(pdata[0]=='A'&&pdata[1]=='T')
		{

			memcpy(pmsg,pdata,message->payloadlen);
			//if(pdata[message->payloadlen-1]!=0x0a)
			{
				pmsg[message->payloadlen]=0x0d;
				pmsg[message->payloadlen+1]=0x0a;
				//write(bt->uart_fd,pmsg,message->payloadlen+2); 
			}
		}
	}
	else
	{
		len=sprintf(pmsg,"mid:%d topic:%s qos:%d retain:%d msg len:%d  data:",message->mid,message->topic,message->qos,message->retain,message->payloadlen);
		for(i=0;i<message->payloadlen;i++)
		{
			len+=sprintf(pmsg+len,"%02x",pdata[i]);  
		}
		pmsg[len++]=0x0d;
		pmsg[len++]=0x0a;
		//write(bt->uart_fd,pmsg,len); 
	}
	fflush(stdout);
	safe_free(pmsg);
}

static void mqtt_connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
	static bool subtopic = false;
	st_serv *serv = userdata;
	mqtt_t *mt = &serv->so.mt;	
	
	if(!result)
	{
		if(subtopic == false)
		{
			/* Subscribe to broker information topics on successful connect. */
			mosquitto_subscribe(mosq, NULL, mt->subtopic, mt->qos);
			if(str_not_null(mt->msgsubtopic))
				mosquitto_subscribe(mosq, NULL, mt->msgsubtopic, mt->qos);
			subtopic = true;
		}
	}
	else
	{
		MSG("This time Connect failed!\n");
		exit(1);
	}
}

static void mqtt_disconnect_callback(struct mosquitto *mosq, void *userdata, int result)
{
	st_serv *serv = userdata;
	set_memint(serv->disnet, result);
	MSG("Warning Disconnect Server..%d..!\n", result);
}

static void mqtt_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)
{
	int i;
	MSG("Subscribed (mid: %d): %d", mid, granted_qos[0]);
	for(i=1; i < qos_count; i++)
	{
		MSG(", %d", granted_qos[i]);
	}
	MSG("\n");
}

static void mqtt_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
	MSG("MQTT LOG:%s\n", str);
}

int load_mqttconf(st_serv *serv)
{
	mqtt_t *mt = &serv->so.mt;
	char value[BUF_256] = {0};
	
	uci_get_value("bleserve.mqtt.intv", value);
	serv->postintv= atoi(value);
	uci_get_value("bleserve.mqtt.type", value);
	if(0 == safe_strcasecmp(value, "SSL"))
		mt->ssl = 1;
	uci_get_value("bleserve.mqtt.certtype", mt->type);		
	uci_get_value("bleserve.mqtt.host", mt->host);
	uci_get_value("bleserve.mqtt.port", value);
	mt->port = atoi(value);	
	uci_get_value("bleserve.mqtt.clientid", mt->clientid);
	uci_get_value("bleserve.mqtt.qos",  value);
	mt->qos = atoi(value);	
	uci_get_value("bleserve.mqtt.username", mt->username);
	uci_get_value("bleserve.mqtt.password", mt->password);	
	uci_get_value("bleserve.mqtt.keepalive", value);
	mt->keepalive = atoi(value);	
	uci_get_value("bleserve.mqtt.pubtopic", mt->pubtopic);
	uci_get_value("bleserve.mqtt.subtopic", mt->subtopic);	
	uci_get_value("bleserve.mqtt.msgpubtopic", mt->msgpubtopic);	
	uci_get_value("bleserve.mqtt.msgsubtopic", mt->msgsubtopic);	
}

int mqtt_send_srmsg(void *arg)
{
	st_serv *serv = arg;
	mqtt_t *mt = &serv->so.mt;	
	return mosquitto_publish(mt->mosq, NULL, mt->pubtopic, serv->postlen, serv->postbuff, mt->qos, 0);
}

int init_mqtt(st_serv *serv)
{
	mqtt_t *mt = &serv->so.mt;
	char *clientid = NULL;
	const char *username = NULL;
	const char *password = NULL;
	mosquitto_lib_init(); 
	if(str_not_null(mt->clientid))
		clientid = mt->clientid;
	while(NULL == (mt->mosq = mosquitto_new(clientid,true,NULL)))
	{
		MSG("create client failed..\n");
		sleep(2);
	}
	if(mt->ssl)
	{
			if(0 == safe_strcasecmp(mt->type, "CA_SIGN")) {
        		mosquitto_tls_opts_set(mt->mosq, 0, "tlsv1.2", NULL);
        		mosquitto_tls_insecure_set(mt->mosq, true);
        		mosquitto_tls_set(mt->mosq, F_DEFCA, NULL, NULL, NULL, NULL);				
			} else if(0 == safe_strcasecmp(mt->type, "CA_CERT")) {
        		mosquitto_tls_opts_set(mt->mosq, 1, "tlsv1.2", NULL);
        		mosquitto_tls_insecure_set(mt->mosq, true);
        		mosquitto_tls_set(mt->mosq, F_SCA, NULL, NULL, NULL, NULL);				
			} else if(0 == safe_strcasecmp(mt->type, "SE_SIGN")) {
        		mosquitto_tls_opts_set(mt->mosq, 1, "tlsv1.2", NULL);
        		mosquitto_tls_insecure_set(mt->mosq, true);
        		mosquitto_tls_set(mt->mosq, F_CA, NULL, F_CERT, F_KEY, NULL);				
			}

	}

	if(str_not_null(mt->username))
		username = mt->username;
	if(str_not_null(mt->password))
		password = mt->password;
	if(username)
		mosquitto_username_pw_set(mt->mosq, username, password);

	mosquitto_user_data_set(mt->mosq, serv);
	mosquitto_log_callback_set(mt->mosq, mqtt_log_callback);
	mosquitto_connect_callback_set(mt->mosq, mqtt_connect_callback);
	mosquitto_disconnect_callback_set(mt->mosq, mqtt_disconnect_callback);	
	mosquitto_message_callback_set(mt->mosq, mqtt_message_callback);
	mosquitto_subscribe_callback_set(mt->mosq, mqtt_subscribe_callback);

	if(0 != mosquitto_connect(mt->mosq, mt->host, mt->port, mt->keepalive))
	{
		MSG("Unable to connect..\n");	
		sleep(5);
		return 1;
	}
   
	while(0 != mosquitto_loop_start(mt->mosq))
	{
		MSG("mosquitto loop error\n");
		sleep(2);
	}

	set_memint(serv->disnet, 0);
	serv->send = mqtt_send_srmsg;

    return 0;
}

int stop_mqtt(st_serv *serv)
{
	mqtt_t *mt = &serv->so.mt;
	mosquitto_destroy(mt->mosq);
	mosquitto_lib_cleanup();
}
