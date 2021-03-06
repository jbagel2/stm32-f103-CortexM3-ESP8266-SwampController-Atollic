/*
 * SwampControls.h
 *
 *  Created on: Apr 26, 2016
 *      Author: Jacob
 */

#ifndef SWAMPCONTROLS_H_
#define SWAMPCONTROLS_H_

#include <stm32f10x_gpio.h>
#include "CustomStructs/InstanceStructs.h"



typedef enum
{
	Fan_OFF = 0,
	Fan_Low,
	Fan_High
}Fan_Mode;

typedef enum
{
	OFF =
			0,
	ON
}On_Off;

void SetSafeState();
void Init_InstanceControls();
void Set_PumpState(Change_State request);
void Set_Fan_State(Change_State request);


#endif /* RADIENTCONTROLS_H_ */
