#ifndef __MSG_H__
#define __MSG_H__

#include "common.h"

#define APP_MESSAGE_PATH            "/tmp/app_server_addr/"

/*
 * This is the number of fully connected connections that can be queued
 *  up at the message server socket.
 *
 *  It is highly unlikely that this needs to be changed.
 */
#define APP_MESSAGE_BACKLOG         128

/** Number of micro-seconds in a milli-second. */
#define USECS_IN_MSEC   1000

/** Number of milliseconds in 1 second */
#define MSECS_IN_SEC    1000

/** Invalid file descriptor number. */
#define MSG_INVALID_FD  (-1)

/******************************************************************************
 *                                 ENUM                                       *
 ******************************************************************************/
typedef enum
{
    RX_MSG      = 1,
    TX_MSG      = 2,
} msg_flag;

#pragma pack(1)
typedef struct
{
    unsigned int cmd;
    unsigned int seq;
    int index;
    unsigned int res;            //used as flags
    int len;
    char data[0];
} unix_msg;

typedef struct
{
    unsigned int cmd;
    unsigned int seq;
    unsigned int res;
    int len;
    char data[0];
} tcp_msg;
#pragma pack()


/*******************************************************************************
 * Function:
 *    SINT32 InetServerInit(SINT32 iDomain, SINT32 iPort, SINT32 iType, SINT32 iBackLog, SINT32 *iSkFd)
 * Description:
 *    This function creates and initializes a TCP or UDP listening socket
 *    for an application.
 * Parameters:
 *    iDomain  (IN) Specifies whether it is a client-side socket or 
 *                  server-side socket.
 *    iPort    (IN) The application TCP or UDP port.
 *    iType    (IN) The socket type, either SOCK_STREAM or SOCK_DGRAM.
 *    iBackLog (IN) Number of connections to queue. 
 *    iFd      (OUT)The socket file descriptor. 
 * Returns:
 *    0,success;others,err
 *******************************************************************************/

SINT32 InetServerInit(SINT32 iDomain, SINT32 iPort, SINT32 iType, SINT32 iBackLog, SINT32 *iSkFd);

/*******************************************************************************
 * Function:
 *    void InetServerDeinit(SINT32 iFd)
 * Description:
 *    This function deinit the socket created for internet server
 * Parameters:
 *    iFd    (IN) The socket file descriptor 
 * Returns:
 *    void
 *******************************************************************************/
void InetServerDeinit(SINT32 iFd);

/** Domain socket **/
/*******************************************************************************
 * Function:
 *    SINT32 DomainServerInit(const SINT8 *pName, SINT32 *iSkFd)
 * Description:
 *    This function creates a socket, binds server with path and listen
 * Parameters:
 *    pName   (IN) Name of process used as a server 
 *    iSkFd   (OUT)The socket file descriptor
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
SINT32 DomainServerInit(const SINT8 *pName, SINT32 *iSkFd);

/*******************************************************************************
 * Function:
 *    void DomainServerDeinit(SINT32 iFd)
 * Description:
 *    This function deinit the socket created for domain(local) server
 * Parameters:
 *    iFd    (IN) The socket file descriptor 
 * Returns:
 *    void
 *******************************************************************************/
void DomainServerDeinit(SINT32 iFd);

/*******************************************************************************
 * Function:
 *    SINT32 DomainClientInit(const SINT8 *pServerName)
 * Description:
 *    This function creates a socket, connects to server
 * Parameters:
 *    pServerName   (IN) Name of server process 
 *    iSkFd         (OUT)The socket file descriptor 
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
SINT32 DomainClientInit(const SINT8 *pServerName, SINT32 *iSkFd);

/*******************************************************************************
 * Function:
 *    void DomainClientDeinit(SINT32 iFd)
 * Description:
 *    This function deinit the socket created for domain(local) client
 * Parameters:
 *    iFd    (IN) The socket file descriptor 
 * Returns:
 *    void
 *******************************************************************************/
void DomainClientDeinit(SINT32 iFd);

/*******************************************************************************
 * Function:
 *    SINT32 IM_ServerAcceptClient(SINT32 iListenFd, SINT32 *iSkFd)
 * Description:
 *    Before server recieve or send message,server should accept a client
 * Parameters:
 *    iFd    (IN) The listening socket file descriptor 
 *    iSkFd  (OUT)The accept socket file descriptor 
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
SINT32 ServerAcceptClient(SINT32 iListenFd, SINT32 *iSkFd);

/*******************************************************************************
 * Function:
 *    SINT32 MsgSend(SINT32 iFd, const SINT8 *pBuf, UINT32 nLen)
 * Description:
 *    Use this function,client send message to server,
 *    or server send response message to client
 * Parameters:
 *    iFd    (IN) The socket file descriptor used to send message
 *    pBuf   (IN) Message for sending 
 *    nLen   (IN) Message length
 * Returns:
 *    The sending result
 *    0:success;others,error
 *******************************************************************************/
SINT32 MsgSend(SINT32 iFd, const SINT8 *pBuf, UINT32 nLen);

/*******************************************************************************
 * Function:
 *    SINT32 MsgReceive(SINT32 iFd, SINT8 *pBuf, UINT32 nLen, UINT32 pnTimeOut, UINT32 *rLen)
 * Description:
 *    Use this function,server recieve message from client,
 *    or client recieve response message from server
 * Parameters:
 *    iFd         (IN)  The socket file descriptor used to recieve message
 *    pBuf        (OUT) The recieve message buf 
 *    nLen        (IN)  The recieve message buf size
 *    pnTimeOut   (IN)  Timeout for recieving
 *    rLen        (OUT) The recieve message len
 * Returns:
 *    1 success; 0 timeout; -1,recieve error
 *******************************************************************************/
SINT32 MsgReceive(SINT32 iFd, SINT8 *pBuf, UINT32 nLen, UINT32 pnTimeOut, UINT32 *rLen);

/*******************************************************************************
 * Function:
 *    void MsgPrintf(const void *pBuf, SINT8 *pszDscrptn, UINT32 nLen, SINT32 iFlag)
 * Description:
 *    dump message with hex and ascii
 * Parameters:
 *    pBuf        (IN)  Message buf
 *    pszDscrptn  (IN)  Message description 
 *    nLen        (IN)  Message length
 *    iFlag       (IN)  Message flag:1,RX;2:TX;other,unkown
 * Returns:
 *    void
 *******************************************************************************/
void MsgPrintf(const void *pBuf, SINT8 *pszDscrptn, UINT32 nLen, SINT32 iFlag);
int create_listen(int port);
int make_skt_nonblock(int skt);

#endif
