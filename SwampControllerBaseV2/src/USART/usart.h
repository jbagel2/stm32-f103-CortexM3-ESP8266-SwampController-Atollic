/*
 * usart.h
 *
 *  Created on: Dec 20, 2015
 *      Author: Jacob
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

volatile const char *TX_Buffer;

#define USART3_PORT GPIOB
#define USART3_TX GPIO_Pin_10
#define USART3_RX GPIO_Pin_11

#define USART2_PORT GPIOA
#define USART2_TX GPIO_Pin_2
#define USART2_RX GPIO_Pin_3

#define USART1_PORT GPIOA
#define USART1_TX GPIO_Pin_9
#define USART1_RX GPIO_Pin_10

typedef struct{
	GPIO_TypeDef* USART_GPIO;
	USART_TypeDef* USART_Num;
	uint16_t Tx_Pin;
	uint16_t Rx_Pin;
	uint8_t USART_IRQn;
}Current_USART;

Current_USART USART_StartInit(USART_TypeDef *usart_num, uint32_t baud);
void USART_Init_DMA3(uint32_t baud, volatile char DMA_RxBuffer[], uint16_t BufSize);
void DMA_Initialize(volatile char DMA_RxBuffer[], uint16_t BufSize);

#endif /* USART_H_ */
