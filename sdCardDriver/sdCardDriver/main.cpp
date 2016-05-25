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
	unsigned char inData[512];
	unsigned char dataOut[512];
	for ( int x = 0; x < 512; x++){
		dataOut[x] = 0xEF;
	}
	SendChar(dataOut[7]);
	//SendChar(SD_obj.writeBlock(0x00000001, dataOut));
	if(SD_obj.writeBlock(0xFFFFFFFF, dataOut)){
		SendChar(0xCC);
	} else {
		SendChar(0xAB);
	}
	//SD_obj.writeByte(0xFF);
	//SD_obj.writeByte(0x58);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0xFF);
	//SendChar(SD_obj.getResponeByte());
	//SendChar(SD_obj.getResponeByte());
	//
	//SD_obj.writeByte(0xFF);
	//SD_obj.writeByte(0xFE);
	//for(int z = 0; z < 512; z++){
		//SD_obj.writeByte(dataOut[z]);
	//}
	//SD_obj.writeByte(0xFF);
	//SD_obj.writeByte(0xFF);
	//unsigned char result;
	//do 
	//{
		//result = SD_obj.getResponeByte();
	//} while (result == 0x00);
	//SendChar(result);
	//SD_obj.getResponeByte();
	//do
	//{
		//result = SD_obj.getResponeByte();
		//SendChar(0xAA);
		//SendChar(result);
	//} while (result != 0xFF);
	//
	//SD_obj.writeByte(0xFF);
	//SD_obj.writeByte(0x4D);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0x00);
	//SD_obj.writeByte(0xFF);
	//
	//SD_obj.getResponeByte();
	//unsigned char R2[2];
	//R2[0] = SD_obj.getResponeByte();
	//R2[1] = SD_obj.getResponeByte();
	//SendChar(R2[0]);
	//SendChar(R2[1]);
	
	//// test med 4096;
	//SD_obj.readBlock(0x00000003, inData); 
	SendChar(0xBB);
	SendChar(0xBB);
	//SendChar(SD_obj.readBlock(0xFFFFFFFF, inData));
	if(SD_obj.readBlock(0xFFFFFFFF, inData)){
		for( int j = 0; j < 512; j++){
			SendChar(inData[j]);
		}
	} else {
		SendChar(0xE9);
	}
}