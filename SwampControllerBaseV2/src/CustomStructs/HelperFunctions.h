/*
 * HelperFunctions.h
 *
 *  Created on: Dec 20, 2015
 *      Author: Jacob
 */

#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

#include "stdint.h"
#include "string.h"


void SetArray_Size(char buffer[], uint16_t size);

void ClearArray_Size(char buffer[], uint16_t size);

uint16_t IndexOf(char *arrayToSearch[], uint16_t arraySize,char *stringToFind);

#endif /* HELPERFUNCTIONS_H_ */
