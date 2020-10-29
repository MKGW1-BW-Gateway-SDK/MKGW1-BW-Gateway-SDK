#ifndef __UCI_CMD_H__
#define __UCI_CMD_H__

#include "common.h"

#define MAX_UCI_BUF   		2048


int uci_set_value(char *name, char *value, bool commit); 
int uci_get_value(char *name, char *value);
int uci_del_value(char *name, bool commit);
int uci_del_list_value(char *name,char *value, bool commit);
int uci_set_list_value(char *name,char *value, char *tok, bool commit);
int uci_del_sect(char *name, bool commit);
int uci_add_sect(char *config, char *section, char *name, bool commit);
int uci_commit_config(char *config);


/*******************************************************************************
 * Function:
 *    int set_option_value(const char *pConfig, const char *pSection, const char *pOption, char *pValue)
 * Description:
 *    set option value with uci 
 * Parameters:
 *    pConfig  (IN) config file name 
 *    pSection (IN) section name in config file.
 *    pOption  (IN) option name
 *    pValue   (IN) value to set 
 * Returns:
 *    0,success;others,err.
 *******************************************************************************/
int set_option_value(const char *pConfig, const char *pSection, const char *pOption, char *pValue);

/*******************************************************************************
 * Function:
 *    int set_option_value_no_commit(const char *pConfig, const char *pSection, const char *pOption, char *pValue)
 * Description:
 *    set option value but not commit with uci 
 * Parameters:
 *    pConfig  (IN) config file name 
 *    pSection (IN) section name in config file.
 *    pOption  (IN) option name
 *    pValue   (IN) value to set 
 * Returns:
 *    0,success;others,err.
 *******************************************************************************/
int set_option_value_no_commit(const char *pConfig, const char *pSection, const char *pOption, char *pValue);


/*******************************************************************************
 * Function:
 *    int get_option_value(const char *pConfig, const char *pSection, const char *pOption, char *pValue, unsigned int nSize)
 * Description:
 *    get option value with uci 
 * Parameters:
 *    pConfig  (IN) config file name 
 *    pSection (IN) section name in config file.
 *    pValue   (OUT)value of option
 *    nSize    (IN) size of value 
 * Returns:
 *    0,success;others,err.
 *******************************************************************************/
int get_option_value(const char *pConfig, const char *pSection, const char *pOption, char *pValue, unsigned int nSize);


#endif
