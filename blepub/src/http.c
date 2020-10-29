#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <netdb.h>
#include <sys/socket.h>

#include "http.h"
#include "blepub.h"


#define BUF_SIZE 1024
char req[BUF_SIZE];

#define GET_HEADER         \
	"GET %s HTTP/1.1\r\n"  \
    "Host: %s:%s\r\n"          \
    "Accept: application/json\r\n"          \
    "Accept-Encoding: gzip, deflate\r\n"          \
    "Connection: keep-alive\r\n"              \
    "User-Agent:Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36\r\n"           \
    "\r\n" 

#define POST_HEADER         \
	"POST %s HTTP/1.1\r\n"  \
    "Host: %s:%s\r\n"          \
    "Accept: application/json\r\n"          \
    "Accept-Encoding: gzip, deflate\r\n"    \
    "Content-Type: application/json\r\n"    \
    "Content-Length: %d\r\n"          \
    "Connection: keep-alive\r\n"              \
    "User-Agent:Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36\r\n"           \
    "\r\n"     

// Get host information (used to establishConnection)
struct addrinfo *getHostInfo(char *host, char *port) {
    int r;
    struct addrinfo hints, *getaddrinfo_res;
    // Setup hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    if ((r = getaddrinfo(host, port, &hints, &getaddrinfo_res)) != 0) {
        MSG("[getHostInfo:getaddrinfo] %s\n", gai_strerror(r));
        return NULL;
    }

    return getaddrinfo_res;
}

// Establish connection with host
SOCKET establishConnection(struct addrinfo *info) {
    if (info == NULL) return SOCK_ERROR;
    SOCKET clientfd;
    
    for (; info != NULL; info = info->ai_next) {
        if ((clientfd = socket(info->ai_family,
                               info->ai_socktype,
                               info->ai_protocol)) < 0) {
            //MSG("[establishConnection:socket]");
            continue;
        }

        if (connect(clientfd, info->ai_addr, info->ai_addrlen) < 0) {
            close(clientfd);
            //MSG("[establishConnection:connect]");
            continue;
        }

        //freeaddrinfo(info);
        return clientfd;
    }

    //freeaddrinfo(info);
    return SOCK_ERROR;
}

//Show certificate
void ShowCerts(SSL *ssl) {
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if (cert != NULL) {
        MSG("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        MSG("Subject: %s\n", line);
        free(line);       /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        MSG("Issuer: %s\n", line);
        free(line);       /* free the malloc'ed string */
        X509_free(cert);     /* free the malloc'ed certificate copy */
    } else
        MSG("Info: No client certificates configured.\n");
}

int read_ssl_response(SSL *ssl, char *buf) {
    int bytes_read = 0;
    while (1) {
        int bytes = SSL_read(ssl, buf + bytes_read, BUF_SIZE - bytes_read);
        if (bytes < 0) {
			MSG("SSL_read error\n");
			return -1;
        } else if (bytes == 0) {
            break;
        }
        bytes_read += bytes;
    }
    return bytes_read;
}

int read_response(int clientfd, char *buf) {
    int bytes_read = 0;
    while (1) {
        int bytes = read(clientfd, buf + bytes_read, BUF_SIZE - bytes_read);
        if (bytes < 0) {
			MSG("read error\n");		
			return -1;
        } else if (bytes == 0) {
            break;
        }
        bytes_read += bytes;
    }
	return bytes_read;
}

int com_write(int fd, const void *buf, size_t count) {
	int ret = -1;
	size_t wlen;
	wlen = write(fd, buf, count);
	if(wlen < 0)
		MSG("write error, return %s.\n", strerror(wlen));
	else if(wlen == 0)
		MSG("write error, server closed.\n");
	else if(wlen != count)
		MSG("write error, unexpect %d[%d].\n", wlen, count);
	else
		ret = 0;
	return ret;	
}

// Send GET request
char *GET(int clientfd, char *path, char *port, char *host) {
    memset(req, 0, sizeof(req));
    sprintf(req, GET_HEADER, path, host, port);
    com_write(clientfd, req, strlen(req));
    return req;
}

// Send POST request
char *POST(int clientfd, char *path, char *host, char *port, char *argument, int len) {
    memset(req, 0, sizeof(req));
    //sprintf(req, "POST %s HTTP/1.1\r\nHost: %s\r\n\r\n%s", path, host, argument);
    sprintf(req, POST_HEADER, path, host, port, len);
    com_write(clientfd, req, strlen(req));
	com_write(clientfd, argument, len);

    return req;
}

// Send GET request over TLS
char *SSL_GET(SSL *ssl, char *path, char *host, char *port) {
	int ret = 0;
    memset(req, 0, sizeof(req));
    sprintf(req, GET_HEADER, path, host, port);
	ret = SSL_write(ssl, req, strlen(req));
    if (ret < 0)
        MSG("SSL_ERROR: SSL_write %d.\n", SSL_get_error(ssl, ret));
    else if(ret == 0)
    	MSG("SSL_ERROR: SSL_write server closed.\n");
    return req;
}

// Send POST request over TLS
char *SSL_POST(SSL *ssl, char *path, char *host, char *port, char *argument, int len) {
	int ret = 0;
	memset(req, 0, sizeof(req));

    sprintf(req, POST_HEADER, path, host, port, len);
	ret = SSL_write(ssl, req, strlen(req));
    if (ret < 0) 
        MSG("SSL_ERROR: SSL_write error %d.\n", SSL_get_error(ssl, ret));
    else if(ret == 0)
    	MSG("SSL_ERROR: SSL_write server closed.\n");
	ret = SSL_write(ssl, argument, len);
    if (ret < 0)
        MSG("SSL_ERROR: SSL_write error %d.\n", SSL_get_error(ssl, ret));
    else if(ret == 0)
    	MSG("SSL_ERROR: SSL_write server closed.\n");
    return req;
}

char *common_get(http_t *res, char *path, char *host, char *port) {
	if(res->https)
		return SSL_GET(res->ssl, path, host, port);
	else
		return GET(res->clientfd, path, host, port);
};

char *common_post(http_t *res, char *path, char *host, char *port, char *argument, int len) {
	if(res->https)
		return SSL_POST(res->ssl, path, host, port, argument, len);
	else
		return POST(res->clientfd, path, host, port, argument, len);
}

int common_read_response(http_t *res) {
    if(res->https)
		return read_ssl_response(res->ssl, req);
	else
	    return read_response(res->clientfd, req);
}

int init_socket(http_t *ht)
{
	if(ht->https)
	{
		ht->ctx = SSL_CTX_new(ht->method);
		ht->ssl = SSL_new(ht->ctx);	
	}

	return 0;
}

int connect_server(http_t *ht)
{
	if(ht->saddr == NULL)
		ht->saddr = getHostInfo(ht->host, ht->port);
	ht->clientfd = establishConnection(ht->saddr);
	
	if (ht->clientfd == -1) {
		MSG("Failed to connect to: %s:%s \n", ht->host, ht->port);
		return -1;
	}
	
	if(ht->https)
	{	
		SSL_set_fd(ht->ssl, ht->clientfd);
		SSL_connect(ht->ssl);
		ShowCerts(ht->ssl);
		SSL_get_cipher(ht->ssl);
	}

	return 0;
}

int close_socket(http_t *ht)
{
	if(ht->https)
	{
		SSL_shutdown(ht->ssl);		
		SSL_CTX_free(ht->ctx);
		SSL_free(ht->ssl);
	}
	safe_close(ht->clientfd);
}

int load_httpconf(st_serv *serv)
{
	int ret = -1;
	char *p = NULL;
	http_t *ht = &serv->so.ht;
	char value[BUF_256] = {0};

	uci_get_value("bleserve.http.intv", value);
	serv->postintv = atoi(value);
	
	uci_get_value("bleserve.http.url", value);
	if(0 == safe_strncmp(value, "http://", 7))
		ht->https = 0;
	else if(0 == safe_strncmp(value, "https://", 8))
		ht->https = 1;
	else {
		MSG("Invalid Url[%s]", value);
		goto exit;
	}
	
	ht->path[0] = '/';
	sscanf(value, "%*[^/]//%*[^/]/%[^\n]", &ht->path[1]);
	sscanf(value, "%*[^/]//%[^/]/", ht->host);
	if(NULL == (p = strchr(ht->host, ':')))
	{
		if(ht->https)
			safe_strcpy(ht->port, "443");
		else
			safe_strcpy(ht->port, "80");
	}
	else
	{
		*p++ = '\0';
		strcpy(ht->port, p);
	}
	uci_get_value("bleserve.http.username", ht->username);
	uci_get_value("bleserve.http.password", ht->password);

	ret = 0;
exit:	
	return ret;
}

int http_send_srmsg(void *arg)
{
	st_serv *serv = arg;
	http_t *ht = &serv->so.ht;

	if(init_socket(ht))
		goto err;
	if(connect_server(ht))	
	{
			MSG("Lost Server To Exit!\n");
			exit(1);
	}
	common_post(ht, ht->path, ht->host, ht->port,serv->postbuff, serv->postlen);
	close_socket(ht);
	return 0;
err:
	return 1;
}

int init_http(st_serv *serv)
{
	
	http_t *ht = &serv->so.ht;
	if(ht->https)
	{
		if(SSLEAY_VERSION_NUMBER < 0x1010007fL) {
			OPENSSL_add_all_algorithms_conf();
			SSL_library_init();
			ht->method = (SSL_METHOD *)TLSv1_2_client_method();
		} else {
			ht->method = (SSL_METHOD *)TLS_client_method();
		}
	}

	init_socket(ht);
	while(connect_server(ht))	
	{
		MSG("[http%s://%s:%s] can't be connected!\n", ht->https ? "s" : "",  ht->host, ht->port);
		sleep(2); 
	}
	MSG("HTTP Initialized!\n");
	if(str_not_null(ht->username) || str_not_null(ht->password))
	{
		int len = 0;
		char *p = NULL;
		char loginpath[BUF_256] = {0};
		char content[BUF_256] = {0};
		safe_strcpy(loginpath, ht->path);
		len = strlen(loginpath);
		if((len > 1) && (loginpath[len-1] == '/'))
			loginpath[len-1] = '\0';
		if(NULL != (p = strrchr(loginpath, '/')))
			safe_strcpy(p+1, "login");
		else
			safe_strcpy(loginpath, "/login");	
		sprintf(content, "{\"username\":\"%s\",\"password\":\"%s\"}", ht->username, ht->password);
		common_post(ht, loginpath, ht->host, ht->port, content, strlen(content));
	}
	close_socket(ht);
	
	set_memint(serv->disnet, 0);
	serv->send = http_send_srmsg;

	return 0;
}

int stop_http(st_serv *serv)
{
	http_t *ht = &serv->so.ht;	
	if(ht->saddr != NULL)
		freeaddrinfo(ht->saddr);
}

