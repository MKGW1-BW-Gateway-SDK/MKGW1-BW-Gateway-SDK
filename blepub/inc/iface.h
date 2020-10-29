/************************************************************************
#
#  Copyright (c) 2019-2029  MOKOTECHNOLOGY Co., Ltd.
#  All Rights Reserved
#
#  author: lichuanhe
#  create date: 2019-3-5
# 
# Unless you and MOKOTECHNOLOGY execute a separate written software license 
# agreement governing use of this software, this software is licensed 
# to you under the terms of the GNU General Public License version 2 
# (the "GPL"), with the following added to such license:
# 
#    As a special exception, the copyright holders of this software give 
#    you permission to link this software with independent modules, and 
#    to copy and distribute the resulting executable under terms of your 
#    choice, provided that you also meet, for each linked independent 
#    module, the terms and conditions of the license of that module. 
#    An independent module is a module which is not derived from this
#    software.  The special exception does not apply to any modifications 
#    of the software.  
# 
# Not withstanding the above, under no circumstances may you combine 
# this software in any way with any other MOKOTECHNOLOGY software provided 
# under a license other than the GPL, without MOKOTECHNOLOGY's express prior 
# written consent. 
#
# Revision Table
#
# Version     | Name             |Date           |Description
# ------------|------------------|---------------|-------------------
#  1.0.1      |lichuanhe         |2019-3-5       |Trial Version
#
*************************************************************************/


#ifndef __IFACE_H__
#define __IFACE_H__

/******************************************************************************
 *                               INCLUDES                                     *
 ******************************************************************************/

#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <net/route.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/if_ether.h>

#include "common.h"
#include "wifi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/******************************************************************************
 *                                 MACRO                                      *
 ******************************************************************************/
#define ETH                 "eth"
#define ETH1_IFNAME         ETH"1"
#define ETH0_IFNAME         ETH"0"
#define LAN_IFNAME          "br-lan"

typedef struct
{
	char username[BUF_256];
	char password[BUF_256];
}proto_pppoe;

typedef struct
{
	char ipaddr[BUF_32];
	char netmask[BUF_32];
	char gateway[BUF_32];
	char dns1[BUF_32];
	char dns2[BUF_32];
}proto_static;

typedef struct
{
}proto_dhcp;

typedef struct
{
	char enable[BUF_8];
	char start[BUF_32];
	char end[BUF_32];
	char limit[BUF_32];
}dhcp_server;

typedef struct
{
	char enable[BUF_8];
}dhcp_client;

typedef struct
{
	char proto[BUF_32];
	proto_pppoe     pppoe;
	proto_static    statics;
	proto_dhcp      dhcp;
	char clone[BUF_8];
	char mac[MAC_STR_LEN];
	char macs[BUF_256];
	char mtu[BUF_8];
}interface_t;

typedef struct {
	int uptime;
	char proto[BUF_8];
	char ipaddr[BUF_32];
	char netmask[BUF_32];
	char gateway[BUF_32];
	char dns[2][BUF_32];
	char ports[BUF_16];
} ifaceinfo_t;

typedef struct
{
	char mode[BUF_32];
	interface_t lan;
	dhcp_client dhcpc;
	interface_t wan;
	dhcp_server dhcps;	
	wifi_device radio;
}network_t;

typedef struct 
{
	int link;
	char wifimode[BUF_32];
	char wanmode[BUF_32];
	char wanip[BUF_32];
	char lanip[BUF_32];
	char channel [BUF_32];	
	char access [BUF_32];
}netinfo_t;

/******************************************************************************
 *                                 ENUM                                       *
 ******************************************************************************/
enum{
    TXBYTE = 0,
    TXPACKET = 1,
    RXBYTE = 2,
    RXPACKET = 3,
};
	
/******************************************************************************
 *                                STRUCT                                      *
 ******************************************************************************/

/******************************************************************************
 *                               FUNCTION                                     *
 ******************************************************************************/


/*******************************************************************************
 * Function:
 *    int set_ip_addr(char *if_name, char *buf)
 * Description:
 *    Set interface ip
 * Parameters:
 *    if_name  (IN) name of interface 
 *    buf      (OUT)result of ip like 192.168.123.234
 * Returns:
 *    0,success;others,err,see err code for datail.
 *******************************************************************************/
int set_ip_addr(char *if_name, char *buf);


/*******************************************************************************
 * Function:
 *    int set_netmask(char *if_name, char *buf)
 * Description:
 *    Set interface mac
 * Parameters:
 *    if_name  (IN) name of interface 
 *    buf      (OUT)result of netmask, like 192.168.1.1
 * Returns:
 *    0,success;others,err,see err code for datail.
 *******************************************************************************/
int set_netmask(char *if_name, char *buf);

/*******************************************************************************
 * Function:
 *    int set_wan_gateway(char *buf)
 * Description:
 *    Set interface mac
 * Parameters:
 *    buf      (OUT)result of default wan gateway, like 192.168.1.1
 * Returns:
 *    0,success;others,err,see err code for datail.
 *******************************************************************************/
int set_wan_gateway(char *buf);
void network_restart(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __IFACE_H__ */

