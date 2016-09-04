/*
 * ESP8266_Data_Types.c
 *
 *  Created on: Mar 31, 2016
 *      Author: Jacob
 */

#include "ESP8266_Data_Types.h"
#include <string.h>

RX_FromESP_Command To_ESP_RXData_Struct(char *RX_String){
	RX_FromESP_Command new_data;
	if (strlen(RX_String) > 5)
	{

	}
	return new_data;
}


TX_ToESP_Command To_ESP_TXData_Struct(char *TX_String){
	TX_ToESP_Command new_data;
	if (strlen(TX_String) > 5)
	{

	}
	return new_data;
}
