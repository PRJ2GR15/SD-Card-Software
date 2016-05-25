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
	unsigned char Data[512];
	//SD_obj.writeByte(0xFF); // clock sync
	//SD_obj.writeByte(0x51);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0xFF); // dummy CRC;
		//
	//SendChar(SD_obj.getResponeByte()); // getting empty response out of the way.
		//unsigned char result;
		//int a = 0;
		//do
		//{
			//result = SD_obj.getResponeByte();
			//SendChar(result);
		//} while (result != 0xFE);
		//
		//for( a = 0 ; a < 512; a++ ){
			//Data[a] = SD_obj.getResponeByte();
		//}
		//SD_obj.getResponeByte();
		//SD_obj.getResponeByte();
		//
		//
	//
	//
	//SendChar(0xBB);
	//SendChar(0xBB);
	//SendChar(0xBB);
	SD_obj.readBlock(0x00000200, Data);
	SendChar(0xBB);
	SendChar(0xBB);
	for( int j = 0; j < 512; j++){
		SendChar(Data[j]);
	}
}