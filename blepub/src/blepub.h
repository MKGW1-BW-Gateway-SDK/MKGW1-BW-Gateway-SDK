
#ifndef __BLEPUB_H__
#define __BLEPUB_H__
#include <osapi.h>

#include "http.h"
#include "mqtt.h"

#define UART_FRAM_LEN  256

#define MSG(args...) fprintf(stderr, args)

typedef enum{
	SE_HTTP = 1,
	SE_MQTT = 2,
}SE_PROTO;

typedef enum{
	NILL_FIFO = 0,
	RAW_FIFO = 1,
	BEACON_FIFO = 2,
}CUST_FIFO;

typedef int (*send_srmsg)(void *arg);

typedef struct {
	pthread_t tid;	
	int *disnet;  //Server connection status, it will affect server led status
	int fifo;	
	int cachetime;	
	
	SE_PROTO mode;
	union {
		http_t	ht;
		mqtt_t	mt;
	}so;
	
	int postintv;
	iBeacon_DT accept;		
	send_srmsg send;   //Parsed(beacon) data send function pointer	
	time_t lastpost;

	iBeacon_Data idata;
	sem_t  *hsem;
	shm_queue *queue;  //Parsed(beacon) data queue waiting to be sent to the server
	
	char macaddr[MAC_STR_LEN]; //gateway macaddr
	int postlen;
	char *postbuff;	
}st_serv;

typedef struct{
	uint16_t len;
	uint16_t data;	
	uint8_t addr[UART_FRAM_LEN];	//uart raw data form nf52832
}iFrame_Data;

typedef struct{
	iFrame_Data iframe;
	sem_t  *hsem;
	shm_queue *queue;	//uart raw data queue form nf52832
}st_uart;

typedef struct{	
	int enable;
	pthread_t tid;	
	st_uart uart;
	st_serv serv;	
}blepub_t;

#endif

 

 
