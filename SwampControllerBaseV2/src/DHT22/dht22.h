/*
 * dht22.h
 *
 *  Created on: Dec 16, 2015
 *      Author: Jacob
 */

#ifndef DHT22_H_
#define DHT22_H_

#include "Time/time.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

typedef struct
{
	uint8_t Response;
	float Temp;
	float Humid;
	uint16_t CheckSumErrors;
	uint16_t CheckSumPass;
	uint8_t CurrentPass;
}DHT22_Data;



void DHT22_Init();
void DHT22_Start_Read(DHT22_Data *tempAndHumid, DHT22_Data *previous_tempAndHumid);
void DHT22_Config_CLK();
void DHT22_Config_GPIO_INPUT();
void DHT22_Config_GPIO_OUTPUT();
void DHT22_Config_EXTInterrupt_Enable();
void DHT22_Config_EXTInterrupt_Disable();
void DHT22_Config_NVIC();
void DHT22_Times_To_Bits16(volatile uint8_t bitTimesArray[], uint8_t arraySize);
void DHT22_Times_To_Bits(volatile uint8_t bitTimesArray[], uint8_t arraySize);
void DHT_Value_Checksum();

#endif /* DHT22_H_ */
