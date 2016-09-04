/*
 * HelperFunctions.c
 *
 *  Created on: Jan 24, 2016
 *      Author: Jacob
 */


#include "HelperFunctions.h"

void SetArray_Size(char buffer[], uint16_t size)
{
	memset(buffer, '1', size);
}

void ClearArray_Size(char buffer[], uint16_t size)
{
	memset(buffer, '\0', size);
}

uint16_t IndexOf(char *arrayToSearch[], uint16_t arraySize,char *stringToFind)
{
	uint16_t correctedSize = arraySize / sizeof(int); //NEED TO EVALUATE IF sizeof(int) evaluates as expected
	uint16_t i;
	for(i = 0; i < correctedSize; i++)
	{
		if(strstr(arrayToSearch[i],stringToFind))
		{
			return i;
		}
	}
	return 0;
}

