/*
 * ESP8266_Data_Types.h
 *
 *  Created on: Mar 31, 2016
 *      Author: Jacob
 */

#ifndef ESP8266_DATA_TYPES_H_
#define ESP8266_DATA_TYPES_H_

#ifndef uint8_t
#include <stdint.h>
#endif

// Received Data Types ("1:PUMP:ZONE:ROOM:AUTOTEMP:HASH")

typedef struct
{
	uint8_t command_int;
	uint16_t pump_value;
	uint8_t zone_num;
	uint8_t room_num;
	int8_t auto_temp;
	char *hash_value;

}RX_FromESP_Command;



// Sent Data Types ("2:PUMP:ACTIVEZONES:ACTIVEROOMS:LINETEMPS:AMBIENTTEMP:AMBIENTHUMID:HASH")

typedef struct
{
	uint8_t command_int;
	float amb_temp;
	float amb_humid;
	char *hash_value;
	uint8_t active_zones[20];
	uint8_t acitve_zone_rooms[20][20];
	float line_temps[];

}TX_ToESP_Command;

// Private Data Types

RX_FromESP_Command To_ESP_RXData_Struct(char *RX_String);
TX_ToESP_Command To_ESP_TXData_Struct(char *TX_String);



#endif /* ESP8266_DATA_TYPES_H_ */
