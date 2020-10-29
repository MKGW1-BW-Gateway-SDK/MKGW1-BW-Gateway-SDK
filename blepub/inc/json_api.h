/************************************************************************
#
#  Copyright (c) 2019-2029  MOKOTECHNOLOGY Co., Ltd.
#  All Rights Reserved
#
#  author: lichuanhe
#  create date: 2019-3-9
# 
# Unless you and 100msh execute a separate written software license 
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
# this software in any way with any other 100msh software provided 
# under a license other than the GPL, without 100msh's express prior 
# written consent. 
#
# Revision Table
#
# Version     | Name             |Date           |Description
# ------------|------------------|---------------|-------------------
#  0.0.1      |lichuanhe         |2019-3-9       |Trial Version
#
*************************************************************************/
#ifndef __JSON_HEADER__
#define __JSON_HEADER__
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */
#include <json-c/json.h>
#include <unistd.h>  
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>  
#include <sys/types.h>
#include "common.h"

typedef enum{
    V_INT = 1,
    V_INT64,
    V_DBL,    
    V_STR,
    V_IMS,
    V_SMI,
    V_ARY,
    V_OBJ,    
    V_LINT,
    V_LSTR,
    V_LIMS,
    V_LSMI,
    V_LARY,
    V_LOBJ,
}V_TYPE;

/*Json define*/
typedef enum JSON_T {
    JSON_T_NULL = json_type_null,
    JSON_T_BOOL = json_type_boolean,
    JSON_T_DOUBLE = json_type_double,
    JSON_T_INT = json_type_int,
    JSON_T_OBJECT = json_type_object,
    JSON_T_ARRAY = json_type_array,
    JSON_T_STRING = json_type_string,
}JSON_T;

typedef struct json_object JSON;

/*Json func define*/
__inline__ JSON *Json_Parse(const char *str);

/*Json New*/
JSON *Json_New_Object(void);
JSON *Json_New_Array(void);
__inline__ JSON *Json_New_Int(int i);
__inline__ JSON *Json_New_Int64(int64_t i);
__inline__ JSON *Json_New_Dbl(double i);
__inline__ JSON *Json_New_Str(const char *s);
__inline__ void Json_Free(JSON *jso);

/*Json Get*/
char *Json_Get_String(JSON *jso, const char *name);
int Json_Get_Int(JSON *jso, const char *name, int *value);
int Json_Get_Int64(JSON *jso, const char *name, int64_t *value);
int Json_Get_Dbl(JSON *jso, const char *name, double *value);
__inline__ JSON *Json_Get_Object(JSON *jso, const char *key);
__inline__ JSON_T Json_Get_Type(JSON *jso);
__inline__ int Json_Get_Array_Length(JSON *jso);
__inline__ JSON *Json_Get_Array_Index(JSON *jso, int idx);

/*Json Add*/
int Json_Add_Obj_Obj(JSON *obj, const char *name, JSON *new_obj);
int Json_Add_Obj_Str(JSON *obj, const char *name, const char *value);
int Json_Add_Obj_Int(JSON *obj, const char *name, const int value);
int Json_Add_Obj_Int64(JSON *obj, const char *name, const int64_t value);
int Json_Add_Obj_Dbl(JSON *obj, const char *name, const double value);
int Json_Add_Obj_Arr(JSON *obj,JSON *new_obj);

/*Json To String*/
char *Json_Obj_To_String(JSON *obj, int *len);

int Prase_Json_String(char *body, int num, ...);
char *Create_Json_String(int *len, int num, ...);

int Prase_Json(JSON *data, int num, ...);
JSON *Create_Json(int num, ...);

int _Get_Obj_Vargs(JSON *jso, int num, va_list args);
JSON *_Set_Obj_Vargs(int num, va_list args);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
#endif /* __JSON_HEADER__ */

