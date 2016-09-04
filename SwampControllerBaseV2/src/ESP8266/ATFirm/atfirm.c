/*
 * atfirm.c
 *
 *  Created on: Dec 26, 2015
 *      Author: Jacob
 */
#include "atfirm.h"

const char *ESP_Responses[10] =
{
		"ready",
		"Link",
		"Unlink",
		"OK",
		"SEND OK",
		"+IPD",
		"ERROR",
		"wrong syntax",
		"busy p...",
		"busy inet..."
};

const char *ATCommandsArray[20] = {
	"AT",
	"AT+CIPSTATUS",
	"AT+CWLAP",
	"AT+GMR",
	"AT+CWMODE?",
	"AT+CWMODE=3",
	"AT+CWJAP=\"SSID\",\"PASSWORD\"",
	"AT+CWJAP?",
	"AT+RST",
	"AT+CIPMUX=1",
	"AT+CIOBAUD=115200",
	"AT+CIPSERVER=1,80",
	"AT+CIFSR",
	"AT+CIPSTART=?",
	"AT+CWLIF",
	"AT+CWQAP",
	"AT+CWSAP=",
	"ATE0",
	"AT+CIPCLOSE=",
	"AT+CWMODE=1"};
