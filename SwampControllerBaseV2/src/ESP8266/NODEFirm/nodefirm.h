/*
 * nodefirm.h
 *
 *  Created on: Feb 6, 2016
 *      Author: Jacob
 */

#ifndef NODEFIRM_H_
#define NODEFIRM_H_

#include <stdint.h>
#include "ESP8266/ESP8266_Data_Types.h"
#include "CustomStructs/InstanceStructs.h"

//#include "ESP8266/esp8266_Config.h"
//#include "ESP8266/esp8266.h"

Change_State current_request;

typedef enum
{
	WIFI_CHECK_MODULE_CONNECTION = 0,
	WIFI_AP_LIST,
	WIFI_FIRMWARE_VERSION,
	WIFI_GET_CURRENT_MODE,
	WIFI_MODULE_RESET,
	WIFI_START_LOCAL_SERVER_PORT_80,
	WIFI_GET_CURRENT_IP,
	WIFI_QUIT_CURRENT_AP,

}ESP_Node_Commands;

typedef enum
{
	ESP_START_REST_SERVICE,
	ESP_SAVE_CURRENT_STATUS,
	ESP_SAVE_TEMP_HUMID

}ESP_Node_APP_Commands;

struct ESP_Commands { ESP_Node_Commands command; };
//struct ESP_APP_Commands { ESP_Node_APP_Commands command; };

//typedef enum
//{
//	ESP_START_REST_SERVICE,
//	ESP_SAVE_CURRENT_STATUS,
//	ESP_SAVE_TEMP_HUMID
//
//}ESP_Node_APP_Commands;

extern void ESP_SendCustomCommand_External_Wait(const char *customMessage);

const char *APPCommandsArray[3];
const char *NODECommandsArray[8];


void SaveTempHumid(float temp, float humid);
void SaveNodeStatus(uint16_t pump, uint16_t valve, float lineTemp1, float lineTemp2);

void ESP_SendAppCommand(ESP_Node_APP_Commands command);

//RX_FromESP_Command GetWaitingCommand();
void GetWaitingCommand();
void StartRestService(uint16_t port);
Change_State ESP_GetWaitingCommand_DMA();



#endif /* NODEFIRM_H_ */
