/************************************************************************
#
#  Copyright (c) 2019-2029  MOKOTECHNOLOGY Co., Ltd.
#  All Rights Reserved
#
#  author: lichuanhe
#  create date: 2020-8-7
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
#  1.0.0      |lichuanhe         |2020-8-7       |Trial Version
#
*************************************************************************/


#ifndef __BEACON_H__
#define __BEACON_H__

/******************************************************************************
 *                               INCLUDES                                     *
 ******************************************************************************/

#include <unistd.h>  
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>  
#include "common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/******************************************************************************
 *                                 MACRO                                      *
 ******************************************************************************/
 
typedef enum{
	DT_NilData = 0x0,	
	DT_RawData = 0x1,
	DT_iBeacon = 0x2,
	DT_MkiBeacon = 0x4,
	//DT_BXiBeacon = 0x8,
	DT_MkiBeacon3Axis = 0x10, 	
	DT_MkBeaconX_3Axis = 0x20, 
	DT_MkBeaconX_HT = 0x40, 
	DT_Eddystone_UID = 0x80, 
	DT_Eddystone_URL = 0x100, 
	DT_Eddystone_TLM = 0x200,
	DT_ALL = 0xffffffff,
}iBeacon_DT;

typedef struct {
	int RSSI;	
	int RawDataLen;	
	time_t TimeStamp;
	char BLEName[BUF_32];	
	uint8_t RawData[BUF_128];	
	char BLEMac[MAC_STR_LEN];
}RawData_T;

typedef struct{
	int8_t RSSI1m;	
	u_int16_t iBeaconMajor;
	u_int16_t iBeaconMinor;
	char iBeaconUUID[BUF_32+1];
}iBeacon_T;

typedef struct{
	iBeacon_T ibase;	
	int8_t TxPower;
	u_int8_t Batterylevel;
	char BLEName[BUF_32];	
	char iBeaconID[BUF_8];
}MkiBeacon_T;

typedef struct{
	iBeacon_T ibase;	
	int TxPower;
	int AdvInterval;
}BXiBeacon_T;

typedef struct{
	MkiBeacon_T mibase;
	char three_axisdata_X[BUF_8];
	char three_axisdata_Y[BUF_8];
	char three_axisdata_Z[BUF_8];
}MkiBeacon3Axis_T;

typedef struct{
	int8_t RSSI0m;	
	int8_t TxPower;
	int Datarate;
	int AdvInterval;
	char Scale[BUF_8];
	char three_axisdata_X[BUF_8];
	char three_axisdata_Y[BUF_8];
	char three_axisdata_Z[BUF_8];	
}MkBeaconX_3Axis_T;

typedef struct{
	int8_t RSSI0m;	
	int8_t TxPower;
	int Humidity;
	int AdvInterval;
	int Temperature;
	char Scale[BUF_8];	
}MkBeaconX_HT_T;

typedef struct{
	int8_t RSSI0m;	
	char InstanceID[BUF_16];
	char Namespace[BUF_32];	
}Eddystone_UID_T;

typedef struct{
	int8_t RSSI0m;	
	char URL[BUF_64];	
}Eddystone_URL_T;

typedef struct{
	float TEMP;
	u_int16_t VBATT;
	u_int32_t ADV_CNT;	
	char SEC_CNT[BUF_32];	
	char TLMVersion[BUF_8];
}Eddystone_TLM_T;

typedef union{
		iBeacon_T           ibeacon;
		MkiBeacon_T         mkibeacon;
		BXiBeacon_T         bxibeacon;
		MkiBeacon3Axis_T    mkibeacon3x;
		MkBeaconX_3Axis_T   mkbeaconx_3x;
		MkBeaconX_HT_T      mkbeaconx_ht;
		Eddystone_UID_T     eddystone_uid;
		Eddystone_URL_T     eddystone_url;
		Eddystone_TLM_T     eddystone_tlm;
}Customized_T;

typedef struct{	
	iBeacon_DT          itype;		
	RawData_T           rawdata;	
    Customized_T        custdata;
}iBeacon_Data;

uint8_t get_fiforatio(void);
uint32_t get_scanrate(void);
bool pop_idata(iBeacon_DT accept, iBeacon_Data *idata, uint8_t*data, int len);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __BEACON_H__ */


