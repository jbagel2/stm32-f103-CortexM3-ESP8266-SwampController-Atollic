/*
 * HTTPHelperFunctions.h
 *
 *  Created on: Jan 5, 2016
 *      Author: Jacob
 */

#ifndef HTTPHELPERFUNCTIONS_H_
#define HTTPHELPERFUNCTIONS_H_

//Extracts the enum for the HTTPRequest type of the request
Http_Method_Enum IsRequestType(IPD_Data request)
{
	uint16_t enumValue = IndexOf(HTTP_Method, sizeof(HTTP_Method),request.RequestType);
	if(enumValue != NULL)
	{
		Http_Method_Enum method = enumValue;
		return method;
	}
	return REQUEST_TYPE_ERROR;
}

#endif /* HTTPHELPERFUNCTIONS_H_ */
