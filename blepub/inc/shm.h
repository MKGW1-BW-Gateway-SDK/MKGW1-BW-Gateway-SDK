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


#ifndef __SHM_H__
#define __SHM_H__

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

typedef struct
{
	int key;
    uint32_t head;      
    uint32_t tail;   
    uint32_t used;
	uint32_t total;
	uint32_t unit_size; 
    uint8_t buffer[0];
}shm_queue;

void *new_shm(int key, size_t len, bool check_exist);
int put_shm(void *shm);
int *new_memint(int key);
int *renew_memint(int key);
int set_memint(int *shm, int value);
int get_memint(int *shm);
int put_memint(int *shm);



shm_queue *init_shm_queue(uint32_t unit_size, uint32_t unit_num, int key);

shm_queue *get_shm_queue(uint32_t unit_size, uint32_t unit_num, int key);

int free_shm_queue(shm_queue *queue);

bool shm_queue_push(shm_queue *queue, void *unit);

bool shm_queue_pop(shm_queue *queue, void *unit);

bool shm_queue_empty(shm_queue *queue);

bool shm_queue_full(shm_queue *queue);

int shm_queue_used(shm_queue *queue);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __SHM_H__ */

