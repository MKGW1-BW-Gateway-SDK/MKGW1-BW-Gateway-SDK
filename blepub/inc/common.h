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


#ifndef __LOGIC_COMMON_H__
#define __LOGIC_COMMON_H__

/******************************************************************************
 *                               INCLUDES                                     *
 ******************************************************************************/

#include <unistd.h>  
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>  
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/sysinfo.h>
#include <sys/file.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <errno.h>
#include <regex.h>
#include <resolv.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <stddef.h>
#include <ctype.h>
#include <crypt.h>
//#include <linux/rtnetlink.h>
#include <pthread.h>
#include <assert.h>
#include <sys/shm.h>
#include <semaphore.h>
#include "dbg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/******************************************************************************
 *                                 MACRO                                      *
 ******************************************************************************/

/* Some macros in common use. */
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef true
#define true  1
#endif

#ifndef false
#define false 0
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef BOOL
#define BOOL    unsigned int
#endif

#ifndef bool
#define bool    unsigned int
#endif

#ifndef NTOHL
#define NTOHL(x) (x) = ntohl(x)
#endif

#ifndef HTONL
#define HTONL(x) (x) = htonl(x)
#endif

#ifndef NTOHS
#define NTOHS(x) (x) = ntohs(x)
#endif

#ifndef HTONS
#define HTONS(x) (x) = htons(x)
#endif

#define MAX_CMD_LEN         256
#define MAX_DOMAIN_LEN      67
#define MAC_STR_LEN         18
#define MAC_HEX_LEN         6
#define MAX_IP_LEN          16

#define HTTP_URL_PATTERN    "(https?)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]"
#define IPV4_PATTERN        "^([0-9]{1,3}\\.){3}[0-9]{1,3}$"
#define IPV6_PATTERN        "^[0-9A-Fa-f:]+$"
#define DOMAIN_PATTERN      "^[[:alnum:]]([[:alnum:]-]+[.]?){1,5}[[:alpha:]]+$"

#define BUF_8               8
#define BUF_16              16
#define BUF_32              32
#define BUF_64              64
#define BUF_128             128
#define BUF_256             256
#define BUF_512             512

#define ARRAY_SIZE(x) 		(sizeof(x) / sizeof((x)[0]))
#define array_size(p)        ARRAY_SIZE(p)

/* Free a buffer and set the pointer to null. */
#define SAFE_FREE(p) \
        do { \
            if ((p) != NULL) {free((p)); (p) = NULL;}   \
        } while (0)
#define safe_free(p)        SAFE_FREE(p)

/* Close a fd and set fd to -1. */
#define SAFE_CLOSE(fd) \
        do { \
            if (fd > -1) {close(fd); (fd) = -1;}   \
        } while (0)
#define safe_close(fd)      SAFE_CLOSE(fd)

/* Close a file fd and set the pointer to null. */
#define SAFE_FCLOSE(pFd) \
        do { \
            if ((pFd) != NULL) {fclose((pFd)); (pFd) = NULL;}   \
        } while (0)
#define safe_fclose(pFd)    SAFE_FCLOSE(pFd)
            
#define SAFE_PCLOSE(pFd) \
        do { \
            if ((pFd) != NULL) {pclose((pFd)); (pFd) = NULL;}   \
        } while (0)
#define safe_pclose(pFd)    SAFE_PCLOSE(pFd)

#define PRINT_MAC(addr) \
        (uint8_t)addr[0], (uint8_t)addr[1], (uint8_t)addr[2], (uint8_t)addr[3], (uint8_t)addr[4], (uint8_t)addr[5]
#define print_mac(addr)     PRINT_MAC(addr)

#define STR_NOT_NULL(s) ((s != NULL) && (s[0]!='\0')) 
#define str_not_null(s)     STR_NOT_NULL(s)
#define STR_YES_NULL(s) ((s == NULL) || (s[0]=='\0'))
#define str_yes_null(s)     STR_YES_NULL(s)

#define Err_Goto(ret ,eno, oth)      do{ret = (eno); goto oth;}while(0)
#define Nil_Gono(ptr, ret, eno, oth) do{if(!(ptr)) {ret = (eno); goto oth;}}while(0)
#define Nil_Goto(ptr, oth)           do{if(!(ptr)) goto oth;}while(0)

#define loop_forever() do{sleep(60);}while(1)
/******************************************************************************
 *                                 TYPEDEF                                    *
 ******************************************************************************/

/* Integer and bool type definition. */
typedef int 		        SINT32;
typedef unsigned int        UINT32;
typedef short int 	        SINT16;
typedef unsigned short int  UINT16;
typedef char 		        SINT8;
typedef unsigned char       UINT8;
typedef unsigned char       UBOOL8;

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;

typedef __uint32_t      __u32;
typedef __int32_t       __s32;
typedef __uint16_t      __u16;
typedef __int16_t       __s16;
typedef __uint8_t       __u8;

typedef struct u_string {
        int len;
        int cap;
        char str[1];
}u_string;

typedef bool (*FUNC_PREM)(void);
/******************************************************************************
 *                                 STRUCT                                     *
 ******************************************************************************/



/******************************************************************************
 *                               FUNCTION                                     *
 ******************************************************************************/
void *mallocz(size_t size);
struct u_string* u_strnew(int cap);
struct u_string* u_strdup_raw(char *r);
void u_strfree(struct u_string *s);
struct u_string* u_strdup(struct u_string *s); 
/*******************************************************************************
 * Function:
 *    int get_ip_addr(char *if_name, char *buf)
 * Description:
 *    Get interface ip
 * Parameters:
 *    if_name  (IN) name of interface 
 *    buf      (OUT)result of ip like 192.168.123.234
 * Returns:
 *    0,success;others,err,see err code for datail.
 *******************************************************************************/
int get_ip_addr(char *if_name, char *buf);

/*******************************************************************************
 * Function:
 *    int get_mac_addr(char *if_name, char *buf)
 * Description:
 *    Get interface mac
 * Parameters:
 *    if_name  (IN) name of interface 
 *    buf      (OUT)result of mac, 6 bytes mac
 * Returns:
 *    0,success;others,err,see err code for datail.
 *******************************************************************************/
int get_mac_addr(char *if_name, char *buf);

/*******************************************************************************
 * Function:
 *    int get_netmask(char *if_name, char *buf)
 * Description:
 *    Get interface mac
 * Parameters:
 *    if_name  (IN) name of interface 
 *    buf      (OUT)result of netmask, like 192.168.1.1
 * Returns:
 *    0,success;others,err,see err code for datail.
 *******************************************************************************/
int get_netmask(char *if_name, char *buf);

/*******************************************************************************
 * Function:
 *    int get_wan_gateway(char *buf)
 * Description:
 *    Get interface mac
 * Parameters:
 *    buf      (OUT)result of default wan gateway, like 192.168.1.1
 * Returns:
 *    0,success;others,err,see err code for datail.
 *******************************************************************************/
int get_wan_gateway(char *buf);

/*******************************************************************************
 * Function:
 *    int safe_system(char *command, int print_flag)
 * Description:
 *    A rewrite of system
 * Parameters:
 *    command    (IN) cmd for execv 
 *    print_flag (IN) 0,do not dump command,1,dump
 * Returns:
 *    0,success;others,err,see err code for datail.
 *******************************************************************************/
int safe_system(char *command, int print_flag);

/*******************************************************************************
 * Function:
 *    int safe_system_value(char *command, int *value, int print_flag)
 * Description:
 *    A rewrite of system
 * Parameters:
 *    command    (IN) cmd for execv 
 *    value      (OUT) cmd result
 *    print_flag (IN) 0,do not dump command,1,dump
 * Returns:
 *    0,success;others,err,see err code for datail.
 *******************************************************************************/
int safe_system_value(char *command, int *value, int print_flag);

/*******************************************************************************
 * Function:
 *    int get_cmd_value(char *cmd, char *value, unsigned int size)
 * Description:
 *    Get value from command
 * Parameters:
 *    cmd    (IN) system command 
 *    value  (OUT)value of cmd
 *    size   (IN)size of value
 * Returns:
 *    0,success;others,err,see err code for datail.
 *******************************************************************************/
int get_cmd_value(char *cmd, char *value, unsigned int size);

/*******************************************************************************
 * Function:
 *    void delete_subchar(char *str, char c)
 * Description:
 *    Delete char from source string
 * Parameters:
 *    str    (IN) source string and result after detete 
 *    substr (IN) char to be deleted
 * Returns:
 *    void
 *******************************************************************************/
void delete_subchar(char *str, char c);

/*******************************************************************************
 * Function:
 *    int split_string(char *str, char *substr[], const char delimit, const int max_count, int *real_count)
 * Description:
 *    split string with delimit
 * Parameters:
 *    str       (IN) source string
 *    substr    (IN) result after split
 *    delimit   (IN) char for delimit
 *    max_count (IN) max count of element
 *    real_count(IN) number of element
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int split_string(char *str, char *substr[], const char delimit, const int max_count, int *real_count);

/*******************************************************************************
 * Function:
 *    int check_host_ip_or_domain(const char *pszValue)
 * Description:
 *    check host string is ip or domain name
 * Parameters:
 *    pszValue  (IN) source host string
 * Returns:
 *    0,domain;1,ip;others,err
 *******************************************************************************/
int check_host_ip_or_domain(const char *pszValue);

/*******************************************************************************
 * Function:
 *    int check_host_ip(const char *pszValue)
 * Description:
 *    check ip is invalid or not
 * Parameters:
 *    pszValue  (IN) source ip string
 * Returns:
 *    0,valid;others,err
 *******************************************************************************/
int check_host_ip(const char *pszValue);

/*******************************************************************************
 * Function:
 *    int check_host_domain(const char *pszValue)
 * Description:
 *    check domain name is invalid or not
 * Parameters:
 *    pszValue  (IN) source domain name string
 * Returns:
 *    0,valid;others,err
 *******************************************************************************/
int check_host_domain(const char *pszValue);

/*******************************************************************************
 * Function:
 *    int daemon_init(int iNoChdir, int iNoClose)
 * Description:
 *    init process as daemon
 * Parameters:
 *    iNoChdir  (IN) change directory,0,change,1,not change
 *    iNoClose  (IN) redirect the standard in/out/err 0,redirect to /dev/console,1,not redirect,2,redirect to /dev/null
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int daemon_init(int iNoChdir, int iNoClose);

/*******************************************************************************
 * Function:
 *    void time_to_string(time_t stWhen, SINT8 *pBuffer, UINT32 nSize)
 * Description:
 *    convert time to string
 * Parameters:
 *    stWhen      (IN)  The time
 *    pBuffer     (OUT) String buffer 
 *    nSize       (IN)  Size of string buffer
 * Returns:
 *    void
 *******************************************************************************/
void time_to_string(time_t stWhen, SINT8 *pBuffer, UINT32 nSize);

/*******************************************************************************
 * Function:
 *    int download_file(char *cmd, int time_out)
 * Description:
 *    download file according to cmd
 * Parameters:
 *    cmd      (IN)  download command
 *    time_out (IN)  timeout for download, unit,second
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int download_file(char *cmd, int time_out);

/*******************************************************************************
 * Function:
 *    int str_cmp_no_case(const char *p1, const char *p2)
 * Description:
 *    compile string with no case
 * Parameters:
 *    p1      (IN)  p1 string
 *    p2      (IN)  p2 string
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int str_cmp_no_case(const char *p1, const char *p2);

/*******************************************************************************
 * Function:
 *    unsigned char *base64_decode(const char *value, int *rlen)
 * Description:
 *    base64 decode
 * Parameters:
 *    value     (IN)  ori strings
 *    rlen      (IN)  rlen
 * Returns:
 *    decodebase64 strings
 *******************************************************************************/
unsigned char *base64_decode(const char *value, int *rlen);

/*******************************************************************************
 * Function:
 *    char *base64_encode(const unsigned char *value, int vlen)
 * Description:
 *    base64 encode
 * Parameters:
 *    value     (IN)  ori strings
 *    vlen      (IN)  vlen
 * Returns:
 *    encodebase64 strings
 *******************************************************************************/
char *base64_encode(const unsigned char *value, int vlen);

/*******************************************************************************
 * Function:
 *    BOOL check_ip(const char *pcip)
 * Description:
 *    check ip or not
 * Parameters:
 *    pcip     (IN)  ip strings
 * Returns:
 *    True ip, False not ip
 *******************************************************************************/
BOOL check_ip(const char *pcip);

/*******************************************************************************
 * Function:
 *    int mac_str_to_hex(char *str, unsigned char *mac)
 * Description:
 *    mac str to hex
 * Parameters:
 *    str     (IN)   mac in strings
 *    mac     (OUT)  mac in hex
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int mac_str_to_hex(char *str, unsigned char *mac);

/*******************************************************************************
 * Function:
 *    char *str2lwr(char *s)
 * Description:
 *    A-Za-z strings to a-za-z strings
 * Parameters:
 *    s     (IN)   A-Za-z strings
 * Returns:
 *    a-za-z strings
 *******************************************************************************/
char *str2lwr(char *s);

/*******************************************************************************
 * Function:
 *    int check_mac_format(char *pstr)
 * Description:
 *    check mac(string) format
 * Parameters:
 *    pstr     (IN)   mac strings
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int check_mac_format(char *pstr);

/*******************************************************************************
 * Function:
 *    int common_del_string_line_break(char *str)
 * Description:
 *    delete '\r' and '\n' in strings
 * Parameters:
 *    str     (IN)   ori strings
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int common_del_string_line_break(char *str);

/*******************************************************************************
 * Function:
 *    int r_file(const char *file, char *value)
 * Description:
 *    read file line, mapkey in line
 * Parameters:
 *    file      (IN)   input file 
 *    value     (OUT)  read line value 
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int r_file(const char *file, char *value);

/*******************************************************************************
 * Function:
 *    int r_file_b(const char *file, long offset, int whence, size_t length, char *value)
 * Description:
 *    read file line, mapkey in line
 * Parameters:
 *    file      (IN)   input file 
 *    offset    (IN)   offset 
 *    whence    (IN)   must be SEEK_SET or SEEK_CUR or SEEK_END
 *    length    (IN)   value length
 *    value     (OUT)  return value
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int r_file_b(const char *file, long offset, int whence, size_t length, char *value);
	
/*******************************************************************************
 * Function:
 *    int w_file(const char *file, char *mode, char *value)
 * Description:
 *    write file with value
 * Parameters:
 *    file      (IN)   input file 
 *    mode      (IN)   fopen with mode, eg: "w" "w+" 
 *    value     (IN)   write line value
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int w_file(const char *file, char *mode, char *value);

/*******************************************************************************
 * Function:
 *    int cmd_read(const char *command, const char *ifname, const char *pszPrefix, const char *itemname, const char *seperator, char *value, size_t size)
 * Description:
 *    read command result
 * Parameters:
 *    command      (IN)   command to exev 
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int cmd_read(const char *command, const char *ifname, const char *pszPrefix, const char *itemname, const char *seperator, char *value, size_t size);
/*******************************************************************************
 * Function:
 *    int move(const char *src, const char *dst, int mod)
 * Description:
 *    write file with value
 * Parameters:
 *    src      (IN)   src file 
 *    dst      (IN)   dst file 
 *    mod      (IN)   mode
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int move(const char *src, const char *dst, int mod);

/*******************************************************************************
 * Function:
 *    int copy(const char *src, const char *dst, int mod)
 * Description:
 *    write file with value
 * Parameters:
 *    src      (IN)   src file 
 *    dst      (IN)   dst file 
 *    mod      (IN)   mode
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int copy(const char *src, const char *dst, int mod);

/*******************************************************************************
 * Function:
 *    int string_match(const char *pszString, const char *pszPattern)
 * Description:
 *    macth string
 * Parameters:
 *    pszString      (IN)   String 
 *    pszPattern     (IN)   Pattern
 * Returns:
 *    0,success;others,err
 *******************************************************************************/
int string_match(const char *pszString, const char *pszPattern);
int safe_strcpy(char *dst, char *src);
int safe_strcmp(char *cp1, char *cp2);
int safe_strncmp(char *cp1, char *cp2, size_t sz);
int safe_strcasecmp(char *cp1, char *cp2);
char *str_strsep(char **stringp,  const char *delim, size_t delimsize,bool withtail);
char *str_strsep_prem(char **stringp,  const char *delim, size_t delimsize, bool withtail, FUNC_PREM prem);
char *str_strsep_ignsep(char **stringp, const char *dm, size_t dmsize, const char *igndm, size_t igndmsize, bool withtail);
char *strlower(char *string);
char *strupper(char *string);
long memtol(const char *nptr, int base, int len);
long long memtoll(const char *nptr, int base, int len);
char *memtostr(const char *mem, char *str, int len);
int hextostr(char *str, const uint8_t* hex, int len);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* __LOGIC_COMMON_H__ */
