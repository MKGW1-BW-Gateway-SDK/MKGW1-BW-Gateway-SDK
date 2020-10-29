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


#ifndef __SYSTEM_H__
#define __SYSTEM_H__

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
#include <dirent.h> 
#include <termios.h>

#include "common.h"
#include "uci_cmd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

typedef struct 
{
	char username[BUF_64];
	char ssid[BUF_64];
	char macaddr[MAC_STR_LEN];
	char version [BUF_64];
	char localtime [BUF_64];	
	char uptime [BUF_64];
	char cpuinfo [BUF_16];
	char meminfo [BUF_16];
}sysinfo_t;

typedef struct
{
	int cpu;
    int mem;
}system_t;

/******************************************************************************
 *                                 MACRO                                      *
 ******************************************************************************/

/******************************************************************************
 *                               FUNCTION                                     *
 ******************************************************************************/
/*******************************************************************************
 * Function:
 *    long get_system_uptime(void)
 * Description:
 *    get system uptime
 * Parameters:
 *    void      
 * Returns:
 *    the uptime.
 *******************************************************************************/
long get_system_uptime(void);

/*******************************************************************************
 * Function:
 *    apply_system_restore(void)
 * Description:
 *    Set system restore
 * Parameters:
 *    void
 * Returns:
 *    0,success;others,err.
 *******************************************************************************/
int apply_system_restore(void);
		
/*******************************************************************************
 * Function:
 *    int apply_ntpd_restart(void)
 * Description:
 *    Set Clocksync
 * Parameters:
 *    void
 * Returns:
 *    0,success;others,err.
 *******************************************************************************/
int apply_ntpd_restart(void);

/*******************************************************************************
 * Function:
 *    int apply_system_upgrade(const char *firmware, int savecfg)
 * Description:
 *    Upgrade system 
 * Parameters:
 *    firmware      (IN)firmware info
 *    savecfg       (IN)save config 
 * Returns:
 *    0,success;others,err.
 *******************************************************************************/
int apply_system_upgrade(const char *firmware, int savecfg);

/*******************************************************************************
 * Function:
 *    int apply_system_reboot(void)
 * Description:
 *    Reboot system 
 * Parameters:
 *    void      
 * Returns:
 *    0,success;others,err.
 *******************************************************************************/
int apply_system_reboot(void);
int open_uart(const char *dev,int nSpeed, int nBits, char nEvent, int nStop);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __SYSTEM_H__ */
