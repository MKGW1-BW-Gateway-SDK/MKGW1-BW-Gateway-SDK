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


#ifndef __LOGIC_DBG_H__
#define __LOGIC_DBG_H__

/******************************************************************************
 *                               INCLUDES                                     *
 ******************************************************************************/

#include "common.h" 

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/******************************************************************************
 *                                 MACRO                                      *
 ******************************************************************************/

/*debug off*/
#define DLOG_OFF               0x00 
/*debug level*/
#define DLOG_ERR               0x01  /*print log + __FUNCTION__ + __LINE__ and print log to file*/
#define DLOG_NOTICE            0x02  /*print log + __FUNCTION__ + __LINE__ and print log to file*/
#define DLOG_WARN              0x04  /*print log + __FUNCTION__ + __LINE__*/
#define DLOG_INFO              0x08  /*print log + __FUNCTION__ + __LINE__*/
#define DLOG_TRACE             0x10  /*print log <=> printf*/
#define DLOG_DEBUG             0x20  /*print log + __FUNCTION__ + __LINE__*/
/*debug all*/
#define DLOG_ALL               (DLOG_ERR | DLOG_NOTICE | DLOG_WARN | DLOG_INFO | DLOG_TRACE | DLOG_DEBUG)

#define LOG(LogLevel, fmt, args...) do { \
        _debug(__FILE__, __LINE__, LogLevel, fmt, ##args); \
} while (0)

#define FLOG(LogFlag, LogLevel, fmt, args...) do { \
    if ((LogFlag) & (LogLevel)) { \
        _debug(__FILE__, __LINE__, LogLevel, fmt, ##args); \
    } \
} while (0)
/******************************************************************************
 *                                 TYPEDEF                                    *
 ******************************************************************************/

	
typedef struct dbginfo{
	time_t   time;
	unsigned char level;
	struct u_string *scn;
	struct u_string *path;
	struct u_string *pname;
}dbginfo;
/******************************************************************************
 *                                 STRUCT                                     *
 ******************************************************************************/


/******************************************************************************
 *                               FUNCTION                                     *
 ******************************************************************************/
void _debug(const char *filename, int line, unsigned char level, const char *format, ...);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __LOGIC_DBG_H__ */
