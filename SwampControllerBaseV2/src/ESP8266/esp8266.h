/*
 * esp8266.h
 *
 *  Created on: Dec 20, 2015
 *      Author: Jacob
 *
 *      This small library is for the basic config and control that is irrelevent to the esp firmware
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "Time/time.h"
#include "USART/usart.h"
#include "Sys_Config/Sys_Config.h"
#include "CustomStructs/HelperFunctions.h"



//#define __ESP_AT__ //Uncomment if using AT Command Firmware
#define __ESP_NODE__ // Uncomment if using NodeMCU Firmware

#define ESP_ResponseTimeout_ms 3000
//#define RxBuffSize 500
volatile char USART_RxBuffer[RxBuffSize];

#ifdef __ESP_AT__



#include "ATFirm/atfirm.h"
extern const char *ATCommandsArray[20];
//char *ESPCommandsArray[20] = &ATCommandsArray;
#define ESP_COMMAND(commandEnum) (ATCommandsArray[(commandEnum)])
#endif

#ifdef __ESP_NODE__

#include "NODEFirm/nodefirm.h"
extern const char *NODECommandsArray[8];
#define ESP_COMMAND(commandEnum) (NODECommandsArray[(commandEnum)]) // ESP_Commands
#define ESP_APP_COMMAND(commandEnum) (APPCommandsArray[(commandEnum)]) // ESP_APP_Commands

#endif

//Defined in AT and Node libs depending on which is implimented
//#define ESP_APP_Commands_ ESP_Node_APP_Commands


/* ESP Config */
#define ESP_USART USART3
#define ESP_CHPD_PORT GPIOB
#define ESP_CHPD_PIN GPIO_Pin_7


/* ESP Public Functions */
void ESP_Init(USART_TypeDef *usart, uint32_t baud);
void ESP_Init_DMA_USART3(uint32_t baud);
//void ESP_GPIO_Init();
void ESP_On();
void ESP_Off();
//void ESP_SendCommand(ESP_Commands command );

void ESP_WaitForAnswer();
void ESP_WaitForAnswerCMD(const char *cmdToWaitFor, uint16_t cmdSize);
void ESP_CloseConnection(uint8_t connectionNum);
void ESP_SendCustomCommand(char *customMessage);
void ESP_SendCustomCommand_External_Wait(const char *customMessage);
void ESP_SendCommand(struct ESP_Commands command );

#endif /* ESP8266_H_ */
