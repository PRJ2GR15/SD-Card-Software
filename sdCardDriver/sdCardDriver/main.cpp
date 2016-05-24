/*
 * sdCard.cpp
 *
 * Created: 22-05-2016 11:08:25
 *  Author: Tonni
 */ 
#define F_CPU 16000000

#include <avr/io.h>

#include "UART/uart.h"
#include "sd/sdCard.h"
#include <util/delay.h>
int main(void)
{

	InitUART(9600, 8, 0);
	sdCard SD_obj(4000);
	_delay_ms(10);
	SendChar(SD_obj.init());

}