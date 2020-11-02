#include "msgdata.h"
#include "blepub.h"


static uint32_t count;

JSON *get_one_data(char *macaddr, iBeacon_DT accept, iBeacon_Data *idata)
{	
	JSON *jdata = NULL;
	char str_date[BUF_32] = {0};
	RawData_T *rawdata = &idata->rawdata;
	iBeacon_T *ibeacon = NULL;
	MkiBeacon_T *mkibeacon = NULL;
	MkiBeacon3Axis_T *mkibeacon3x = NULL;
	MkBeaconX_3Axis_T *mkbeaconx_3x = NULL;
	MkBeaconX_HT_T *mkbeaconx_ht = NULL;
	Eddystone_UID_T *eddystone_uid = NULL;
	Eddystone_URL_T *eddystone_url = NULL;
	Eddystone_TLM_T *eddystone_tlm = NULL;	
	
	str_date_time(str_date, sizeof(str_date), rawdata->TimeStamp);
	switch(accept & idata->itype)
	{
		case DT_NilData:
			break;		
		case DT_RawData:
			{
			char str_data[BUF_128] = {0};
			hextostr(str_data, (uint8_t *)rawdata->RawData, rawdata->RawDataLen);
			jdata = Create_Json(7,
				                V_STR, "TimeStamp",     str_date,
				                V_STR, "DeviceMac(hex)",macaddr,
				                V_STR, "DataFormat",    "RawData",
				                V_STR, "BLEMac(hex)",   rawdata->BLEMac,
				                V_INT, "RSSI(dBm)",     rawdata->RSSI,
				                V_STR, "BLEName",       rawdata->BLEName,
				                V_STR, "RawData(hex)",  str_data);
			break;
			}
    	case DT_iBeacon:
			//printf("#####################iBeacon######################.\n");
			ibeacon = &idata->custdata.ibeacon;
			jdata = Create_Json(9,
				                V_STR, "TimeStamp",         str_date,
				                V_STR, "DeviceMac(hex)",	macaddr,
				                V_STR, "DataFormat",        "iBeacon",
				                V_STR, "BLEMac(hex)",       rawdata->BLEMac,
				                V_INT, "RSSI(dBm)",         rawdata->RSSI,
				                V_STR, "iBeaconUUID(hex)",  ibeacon->iBeaconUUID,
				                V_INT, "iBeaconMajor",      ibeacon->iBeaconMajor,
				                V_INT, "iBeaconMinor",      ibeacon->iBeaconMinor,
				                V_INT, "RSSI@1m(dBm)",      ibeacon->RSSI1m);
			break;	
    	case DT_MkiBeacon:
			//printf("#####################MkiBeacon######################.\n");
			mkibeacon = &idata->custdata.mkibeacon;
			ibeacon = &idata->custdata.mkibeacon.ibase;
			jdata = Create_Json(13,
				                V_STR, "TimeStamp",         str_date,
				                V_STR, "DeviceMac(hex)",	macaddr,
				                V_STR, "DataFormat",        "MkiBeacon",
				                V_STR, "BLEMac(hex)",       rawdata->BLEMac,
				                V_INT, "RSSI(dBm)",         rawdata->RSSI,
				                V_STR, "iBeaconUUID(hex)",  ibeacon->iBeaconUUID,
				                V_INT, "iBeaconMajor",      ibeacon->iBeaconMajor,
				                V_INT, "iBeaconMinor",      ibeacon->iBeaconMinor,
				                V_INT, "RSSI@1m(dBm)",      ibeacon->RSSI1m,
				                V_STR, "BLEName",           mkibeacon->BLEName,
				                V_STR, "iBeaconID",         mkibeacon->iBeaconID,
				                V_INT, "TxPower(dBm)",      mkibeacon->TxPower,
				                V_INT, "Batterylevel(%)",   mkibeacon->Batterylevel);
			break;
    	case DT_MkiBeacon3Axis:
			//printf("#####################MkiBeacon-3Axis######################.\n");
			mkibeacon3x = &idata->custdata.mkibeacon3x;
			mkibeacon = &idata->custdata.mkibeacon3x.mibase;
			ibeacon = &idata->custdata.mkibeacon3x.mibase.ibase;
			jdata = Create_Json(16,
				                V_STR, "TimeStamp",         str_date,
				                V_STR, "DeviceMac(hex)",	macaddr,
				                V_STR, "DataFormat",        "MkiBeacon&3axis",
				                V_STR, "BLEMac(hex)",       rawdata->BLEMac,
				                V_INT, "RSSI(dBm)",         rawdata->RSSI,
				                V_STR, "iBeaconUUID(hex)",  ibeacon->iBeaconUUID,
				                V_INT, "iBeaconMajor",      ibeacon->iBeaconMajor,
				                V_INT, "iBeaconMinor",      ibeacon->iBeaconMinor,
				                V_INT, "RSSI@1m(dBm)",      ibeacon->RSSI1m,
				                V_STR, "BLEName",           mkibeacon->BLEName,
				                V_STR, "iBeaconID",         mkibeacon->iBeaconID,
				                V_INT, "TxPower(dBm)",      mkibeacon->TxPower,
				                V_INT, "Batterylevel(%)",   mkibeacon->Batterylevel,
				                V_STR, "3axisdata-X(hex)",  mkibeacon3x->three_axisdata_X,
				                V_STR, "3axisdata-Y(hex)",  mkibeacon3x->three_axisdata_Y,
				                V_STR, "3axisdata-Z(hex)",  mkibeacon3x->three_axisdata_Z);
			break;
    	case DT_MkBeaconX_3Axis:
			mkbeaconx_3x = &idata->custdata.mkbeaconx_3x;
			//printf("#####################BeaconX Pro-3Axis######################.\n");
			jdata = Create_Json(13,
				                V_STR, "TimeStamp",         str_date,
				                V_STR, "DeviceMac(hex)",	macaddr,
				                V_STR, "DataFormat",        "BeaconX Pro-3Axis",
				                V_STR, "BLEMac(hex)",       rawdata->BLEMac,
				                V_INT, "RSSI(dBm)",         rawdata->RSSI,
				                V_INT, "Datarate(Hz)",      mkbeaconx_3x->Datarate,
				                V_STR, "Scale",             mkbeaconx_3x->Scale,
				                V_STR, "3axisdata-X(hex)",  mkbeaconx_3x->three_axisdata_X,
				                V_STR, "3axisdata-Y(hex)",  mkbeaconx_3x->three_axisdata_Y,
				                V_STR, "3axisdata-Z(hex)",  mkbeaconx_3x->three_axisdata_Z,
				                V_INT, "RSSI@0m(dBm)",      mkbeaconx_3x->RSSI0m,
				                V_INT, "TxPower(dBm)",      mkbeaconx_3x->TxPower,
				                V_INT, "AdvInterval(ms)",   mkbeaconx_3x->AdvInterval);				
			break;
    	case DT_MkBeaconX_HT:
			mkbeaconx_ht = &idata->custdata.mkbeaconx_ht;
			//printf("#####################BeaconX Pro-TH######################.\n");
			jdata = Create_Json(10,
				                V_STR, "TimeStamp",         str_date,
				                V_STR, "DeviceMac(hex)",	macaddr,
				                V_STR, "DataFormat",        "BeaconX Pro-T&H",
				                V_STR, "BLEMac(hex)",       rawdata->BLEMac,
				                V_INT, "RSSI(dBm)",         rawdata->RSSI,
				                V_DBL, "Temperature",       (float)mkbeaconx_ht->Temperature/10,
				                V_DBL, "Humidity(%)",       (float)mkbeaconx_ht->Humidity/10,
				                V_INT, "RSSI@0m(dBm)",      mkbeaconx_ht->RSSI0m,
				                V_INT, "TxPower(dBm)",      mkbeaconx_ht->TxPower,
				                V_INT, "AdvInterval(ms)",   mkbeaconx_ht->AdvInterval);				
			break;
    	case DT_Eddystone_UID:
			eddystone_uid = &idata->custdata.eddystone_uid;
			//printf("#####################Eddystone-UID######################.\n");
			jdata = Create_Json(8,
				                V_STR, "TimeStamp",         str_date,
				                V_STR, "DeviceMac(hex)",	macaddr,
				                V_STR, "DataFormat",        "Eddystone-UID",
				                V_STR, "BLEMac(hex)",       rawdata->BLEMac,
				                V_INT, "RSSI(dBm)",         rawdata->RSSI,
				                V_STR, "Namespace(hex)",    eddystone_uid->Namespace,
				                V_STR, "InstanceID(hex)",   eddystone_uid->InstanceID,
				                V_INT, "RSSI@0m(dBm)",      eddystone_uid->RSSI0m);	
			break;
    	case DT_Eddystone_URL:
			eddystone_url = &idata->custdata.eddystone_url;
			//printf("#####################Eddystone-URL######################.\n");
			jdata = Create_Json(7,
				                V_STR, "TimeStamp",         str_date,
				                V_STR, "DeviceMac(hex)",	macaddr,
				                V_STR, "DataFormat",        "Eddystone-URL",
				                V_STR, "BLEMac(hex)",       rawdata->BLEMac,
				                V_INT, "RSSI(dBm)",         rawdata->RSSI,
				                V_STR, "URL",               eddystone_url->URL,
				                V_INT, "RSSI@0m(dBm)",      eddystone_url->RSSI0m);	
			break;
    	case DT_Eddystone_TLM:
			eddystone_tlm = &idata->custdata.eddystone_tlm;
			//printf("#####################Eddystone-TLM######################.\n");
			jdata = Create_Json(10,
				                V_STR, "TimeStamp",         str_date,
				                V_STR, "DeviceMac(hex)",	macaddr,
				                V_STR, "DataFormat",        "Eddystone-TLM",
				                V_STR, "BLEMac(hex)",       rawdata->BLEMac,
				                V_INT, "RSSI(dBm)",         rawdata->RSSI,
				                V_STR, "TLMVersion(hex)",   eddystone_tlm->TLMVersion,
				                V_INT, "VBATT(mV)",         eddystone_tlm->VBATT,
				                V_DBL, "TEMP(C)",           eddystone_tlm->TEMP,
				                V_INT64, "ADV_CNT",         (int64_t)eddystone_tlm->ADV_CNT,
				                V_STR, "SEC_CNT",           eddystone_tlm->SEC_CNT);
			break;
		default:
			break;
	}
exit:
	return jdata;
}

char *get_json_data(st_serv *serv)
{
	int i, num = 0;
	iBeacon_Data idata;
	JSON *jsonp = NULL;	
	JSON *data[MSG_MAX_JSON] = {0};

	while(!shm_queue_empty(serv->queue))
	{
		if((!get_memint(serv->disnet)) || (num == 0) || (time(NULL) - idata.rawdata.TimeStamp > serv->cachetime)) 
		{
			if(!shm_queue_pop(serv->queue, &idata))
				break;
			data[num] = get_one_data(serv->macaddr, serv->accept, &idata);
			if(data[num] != NULL)	num++;
			if(num == MSG_MAX_JSON)	break;
		}
	}

	if((num != 0) && (NULL != (jsonp = Json_New_Array()))){
		for(i = 0; i < num; i++)
			Json_Add_Obj_Arr(jsonp, data[i]);
		serv->postbuff = Json_Obj_To_String(jsonp, &serv->postlen);
		Json_Free(jsonp);
	}
	
    MSG("[mt7688] reportnum(%lu)=%d\n", count++, num);
    //MSG("bt->postbuff[%d]=[%s].\n", serv->postlen, serv->postbuff);   
	return serv->postbuff;
}

int send_json_data(st_serv *serv)
{
    MSG("[nf52832] fiforatio=%d%% scanrate=%lu/s..\n", get_fiforatio(),  get_scanrate()); 	
	if(NULL != get_json_data(serv))
	{
		set_memint(serv->disnet, serv->send(serv));		
		safe_free(serv->postbuff);		
	}
	serv->lastpost = time(NULL);		
}
