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


#ifndef __WIFI_H__
#define __WIFI_H__

/******************************************************************************
 *                               INCLUDES                                     *
 ******************************************************************************/

#include <unistd.h>  
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>  
#include <syslog.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <math.h>

#include "common.h"
#include "uci_cmd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/******************************************************************************
 *                                 MACRO                                      *
 ******************************************************************************/

#define SYSTEM                "system"
#define MAX_WIFI_IFACE        2
//#define MAX_SSID_NAME_LEN     IW_ESSID_MAX_SIZE
#define MAX_SSID_NAME_LEN     32

typedef struct
{
	char ssid[BUF_128];
	int hidessid;
	char authmode[BUF_16];	
	char encrypt[BUF_64];
	char password[BUF_128];
	char rpenable[BUF_16];
	char rpssid[BUF_128];
	char rpauthmode[BUF_16];
	char rpencrytype[BUF_16];
	char rpencrypt[BUF_32];
	char rppassword[BUF_128];
}wifi_iface;

typedef struct
{
	char mode[BUF_16];	
	char country[BUF_8];
	char channel[BUF_8];
	wifi_iface ra[MAX_WIFI_IFACE];
}wifi_device;

typedef struct site_node {
	char mac[18];
	char ssid[128];
	char cipher[32];
	char auth_suite[32];
	int wpa1;
	int wpa2;
	int wpa1_version;
	int wpa2_version;
	char key[32];
	char mode[32];
	char phy_mode[32];
	int ssid_index;
	char security[32];
	int signal;
	int protocol;
	char channel[32];
	int band;
	int channel_width;
	int level;
	int noise;
	struct site_node *next;
}site_node_t;

bool is_wepkey(const char *key);
bool is_apencrypt(const char *encrypt);
void iw_get_channel(char *vap, int *channel);
int iw_get_essid(char *iface, char *essid);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __WIFI_H__ */
