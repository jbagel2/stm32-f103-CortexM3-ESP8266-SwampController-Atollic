/*
 * usart.c
 *
 *  Created on: Dec 20, 2015
 *      Author: Jacob
 */

#include "usart.h"
#include "stm32f10x_dma.h"

Current_USART Active_USART;
GPIO_InitTypeDef Config_USART;
NVIC_InitTypeDef Interrupt_Config_USART;
USART_InitTypeDef USART_Full_Config;



void usart_Config_CLK(USART_TypeDef *usart_num);
void usart_Config_GPIO(Current_USART *this_usart);
void usart_Config_Interrupt(Current_USART *this_usart);
void usart_Init_Periph(USART_TypeDef *this_usart, uint32_t baud);

Current_USART USART_StartInit(USART_TypeDef *usart_num, uint32_t baud)
{

	Active_USART.USART_Num = usart_num;

	if(usart_num == USART1)
	{
		Active_USART.USART_GPIO = USART1_PORT;
		Active_USART.Tx_Pin = USART1_TX;
		Active_USART.Rx_Pin = USART1_RX;
		Active_USART.USART_IRQn = USART1_IRQn;
	}
	else if (usart_num == USART2) {
		Active_USART.USART_GPIO = USART2_PORT;
		Active_USART.Tx_Pin = USART2_TX;
		Active_USART.Rx_Pin = USART2_RX;
		Active_USART.USART_IRQn = USART2_IRQn;
	}
	else if (usart_num == USART3) {
		Active_USART.USART_GPIO = USART3_PORT;
		Active_USART.Tx_Pin = USART3_TX;
		Active_USART.Rx_Pin = USART3_RX;
		Active_USART.USART_IRQn = USART3_IRQn;
	}

	usart_Config_CLK(usart_num);
	usart_Config_GPIO(&Active_USART);
	usart_Init_Periph(Active_USART.USART_Num,baud);
	USART_Cmd(usart_num,ENABLE);
	usart_Config_Interrupt(&Active_USART);

	return Active_USART;
}

void usart_Config_CLK(USART_TypeDef *usart_num)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

		if(usart_num == USART3)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		}
		else if (usart_num == USART2) {
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		}
		else if (usart_num == USART1){
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		}
}

void usart_Config_GPIO(Current_USART *this_usart)
{
	Config_USART.GPIO_Speed = GPIO_Speed_2MHz;
	Config_USART.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	Config_USART.GPIO_Pin = Active_USART.Rx_Pin;
	GPIO_Init(Active_USART.USART_GPIO, &Config_USART); // Saves above configuration to associated registers

	//--------------------------------------------

	//For TX Pin ---------------------------------
	Config_USART.GPIO_Mode = GPIO_Mode_AF_PP; // Alternate Function Push-Pull
	Config_USART.GPIO_Pin = Active_USART.Tx_Pin;
	GPIO_Init(Active_USART.USART_GPIO, &Config_USART);
}

void usart_Config_GPIO_static3()
{
	Config_USART.GPIO_Speed = GPIO_Speed_2MHz;
	Config_USART.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	Config_USART.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(USART3_PORT, &Config_USART); // Saves above configuration to associated registers

	//--------------------------------------------

	//For TX Pin ---------------------------------
	Config_USART.GPIO_Mode = GPIO_Mode_AF_PP; // Alternate Function Push-Pull
	Config_USART.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(USART3_PORT, &Config_USART);
}

void usart_Config_Interrupt(Current_USART *this_usart)
{
	Interrupt_Config_USART.NVIC_IRQChannel = this_usart->USART_IRQn;
	Interrupt_Config_USART.NVIC_IRQChannelPreemptionPriority = 0;
	Interrupt_Config_USART.NVIC_IRQChannelSubPriority = 0;
	Interrupt_Config_USART.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&Interrupt_Config_USART);

	//USART_ITConfig(this_usart->USART_Num,USART_IT_RXNE, ENABLE);

}

void usart_Init_Periph(USART_TypeDef *this_usart, uint32_t baud)
{
	USART_Full_Config.USART_BaudRate = baud;
	USART_Full_Config.USART_WordLength = USART_WordLength_8b;
	USART_Full_Config.USART_StopBits = USART_StopBits_1;
	USART_Full_Config.USART_Parity = USART_Parity_No;
	USART_Full_Config.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Full_Config.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(this_usart, &USART_Full_Config);
}

void USART_Init_DMA3(uint32_t baud, volatile char DMA_RxBuffer[], uint16_t BufSize)
{
	NVIC_InitTypeDef USART3_DMA_Interrupt_Config;
	//Clock Start
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	//GPIO Config
	usart_Config_GPIO_static3();

	DMA_ClearFlag(DMA1_FLAG_GL3 | DMA1_FLAG_HT3 | DMA1_FLAG_TC3 | DMA1_FLAG_TE3);

	//USART Config
	usart_Init_Periph(USART3, baud);
//	USART3_Config.USART_BaudRate = baud;
//	USART3_Config.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART3_Config.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART3_Config.USART_Parity = USART_Parity_No;
//	USART3_Config.USART_StopBits = USART_StopBits_1;
//	USART3_Config.USART_WordLength = USART_WordLength_8b;
//	USART_Init(USART3, &USART3_Config);



	//DMA Config
	DMA_DeInit(DMA1_Channel3);

	//USART3 DMA1 (RX Ch 3 | TX Ch 2 )
	DMA_InitTypeDef USART3_DMA_Config;
	USART3_DMA_Config.DMA_PeripheralBaseAddr = 0x40004804;
	USART3_DMA_Config.DMA_MemoryBaseAddr = (uint32_t)DMA_RxBuffer;
	USART3_DMA_Config.DMA_DIR = DMA_DIR_PeripheralSRC;
	USART3_DMA_Config.DMA_BufferSize = BufSize;
	USART3_DMA_Config.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	USART3_DMA_Config.DMA_MemoryInc = DMA_MemoryInc_Enable;
	USART3_DMA_Config.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	USART3_DMA_Config.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	USART3_DMA_Config.DMA_Mode = DMA_Mode_Circular;
	USART3_DMA_Config.DMA_Priority = DMA_Priority_VeryHigh;
	USART3_DMA_Config.DMA_M2M = DMA_M2M_Disable;

	DMA_Init(DMA1_Channel3, &USART3_DMA_Config);


	USART3_DMA_Interrupt_Config.NVIC_IRQChannel = DMA1_Channel3_IRQn;
	USART3_DMA_Interrupt_Config.NVIC_IRQChannelCmd = ENABLE;
	USART3_DMA_Interrupt_Config.NVIC_IRQChannelPreemptionPriority = 0;
	USART3_DMA_Interrupt_Config.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&USART3_DMA_Interrupt_Config);
	//NVIC_EnableIRQ(DMA1_Channel3_IRQn);


	DMA_Cmd(DMA1_Channel3,ENABLE);

	USART_Cmd(USART3,ENABLE);
	//DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);

	//Init_USART3_Interrupt();



USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
}

void DMA_Initialize(volatile char DMA_RxBuffer[], uint16_t BufSize)
{
		NVIC_InitTypeDef USART3_DMA_Interrupt_Config;

		DMA_ClearFlag(DMA1_FLAG_GL3 | DMA1_FLAG_HT3 | DMA1_FLAG_TC3 | DMA1_FLAG_TE3);

		DMA_DeInit(DMA1_Channel3);

		//USART3 DMA1 (RX Ch 3 | TX Ch 2 )
		DMA_InitTypeDef USART3_DMA_Config;
		USART3_DMA_Config.DMA_PeripheralBaseAddr = 0x40004804;
		USART3_DMA_Config.DMA_MemoryBaseAddr = (uint32_t)DMA_RxBuffer;
		USART3_DMA_Config.DMA_DIR = DMA_DIR_PeripheralSRC;
		USART3_DMA_Config.DMA_BufferSize = BufSize;
		USART3_DMA_Config.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		USART3_DMA_Config.DMA_MemoryInc = DMA_MemoryInc_Enable;
		USART3_DMA_Config.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		USART3_DMA_Config.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		USART3_DMA_Config.DMA_Mode = DMA_Mode_Circular;
		USART3_DMA_Config.DMA_Priority = DMA_Priority_VeryHigh;
		USART3_DMA_Config.DMA_M2M = DMA_M2M_Disable;

		DMA_Init(DMA1_Channel3, &USART3_DMA_Config);


		USART3_DMA_Interrupt_Config.NVIC_IRQChannel = DMA1_Channel3_IRQn;
		USART3_DMA_Interrupt_Config.NVIC_IRQChannelCmd = ENABLE;
		USART3_DMA_Interrupt_Config.NVIC_IRQChannelPreemptionPriority = 0;
		USART3_DMA_Interrupt_Config.NVIC_IRQChannelSubPriority = 0;

		NVIC_Init(&USART3_DMA_Interrupt_Config);
		//NVIC_EnableIRQ(DMA1_Channel3_IRQn);


		DMA_Cmd(DMA1_Channel3,ENABLE);
}


void USART3_IRQHandler(void)
{
	//static int tx_index = 0;

//	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
//	   {
//		while (TX_Buffer[tx_index])
//		USART_SendData(USART3, TX_Buffer[tx_index++]);
//		//if (tx_index >= (sizeof(TX_Buffer) - 1))
//		      //tx_index = 0;
//
//		USART_ClearFlag(USART3, USART_FLAG_TXE);
//		USART_ITConfig(USART3,USART_IT_TXE, DISABLE);
//		TX_Buffer[0] = "\0";
//	   }

//	if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
//	   {
//		USART_ClearFlag(USART3, USART_FLAG_TC);
//	   }
	USART_ITConfig(USART3,USART_IT_TXE, DISABLE);

}
