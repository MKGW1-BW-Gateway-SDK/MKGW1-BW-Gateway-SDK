
#ifndef __MQTT_H__
#define __MQTT_H__


#include <osapi.h>    
#include <mosquitto.h>

#define F_DEFCA  "/rom/etc_ro/web/res/defca"
#define F_SCA    "/etc_ro/web/res/sca"
#define F_CA     "/etc_ro/web/res/ca"
#define F_CERT   "/etc_ro/web/res/cert"
#define F_KEY    "/etc_ro/web/res/key"

typedef struct{
	bool ssl;
	char type[BUF_64];	
	struct mosquitto *mosq;	
	int qos;	
	int keepalive;
	char host[BUF_256];
	int port;
	char clientid[BUF_256];
	char username[BUF_256];
	char password[BUF_256];
	char pubtopic[BUF_256];
	char subtopic[BUF_256];
	char msgpubtopic[BUF_256];
	char msgsubtopic[BUF_256];	
}mqtt_t;

#endif

 

 
