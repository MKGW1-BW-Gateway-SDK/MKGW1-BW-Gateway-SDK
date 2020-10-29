
#ifndef __HTTP_H__
#define __HTTP_H__


    
#include <osapi.h>
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/dh.h>

#define SOCKET int
#define SOCK_ERROR -1

typedef struct{
	bool https;
	SOCKET clientfd;
	SSL *ssl;
	SSL_CTX *ctx;
	SSL_METHOD *method;	
	struct addrinfo *saddr;
	char path[BUF_256];	
	char host[BUF_256];
	char port[BUF_16];
	char username[BUF_256];
	char password[BUF_256];	
}http_t;

#endif

 

 
