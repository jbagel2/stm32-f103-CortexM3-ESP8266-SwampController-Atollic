
/********************************************************
 * Author: Jacob Pagel
 * Date: 03/05/2015
 * Custom key value pair types variable types
 ********************************************************/

#ifndef _KEYVALUEPAIRS_H_
#define _KEYVALUEPAIRS_H_


#include <stdint-gcc.h>

typedef struct
{
	char *key;
	char *value;

}KeyValuePair_String_String;

typedef struct
{
	char *key;
	uint16_t value;

}KeyValuePair_String_Uint16_t;

typedef struct
{
	char *key;
	uint32_t value;

}KeyValuePair_String_Uint32_t;

typedef struct
{
	uint16_t key;
	uint16_t value;

}KeyValuePair_Uint16_tUint16_t;



#endif // _KEYVALUEPAIRS_H_
