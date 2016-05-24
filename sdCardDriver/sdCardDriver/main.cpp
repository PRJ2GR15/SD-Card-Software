/*
 * sdCard.cpp
 *
 * Created: 22-05-2016 11:08:25
 *  Author: Tonni
 */ 
#define F_CPU 16000000

#include <avr/io.h>


#include "UART/uart.h"
//#include "sd/sdCard.h"
#include <util/delay.h>
#include "SPI/SPI.h"
int main(void)
{
	//_delay_ms(2);
InitUART(9600, 8, 0);
	//_delay_ms(200);
	//_delay_ms(200);
	//_delay_ms(200);
	//_delay_ms(200);
	//_delay_ms(200);
	//SendChar(0xAA);
	//sdCard SD_obj(4000);
	//SD_obj.setSlaveSelect(1);
	//SD_obj.setSlaveSelect(1);
	//SD_obj.dummyCycles();
	//SD_obj.setSlaveSelect(0);
	//SD_obj.sendCmd0();
	//SendChar(SD_obj.getResponeByte());
	//SendChar(SD_obj.getResponeByte());
	//SendChar(SD_obj.getResponeByte());
	//SendChar(SD_obj.getResponeByte());
	//SendChar(SD_obj.getResponeByte());
	
	SPI spi_obj(125);
	//spi_obj.recieveByte();
    //sdCard SD_obj(4000);
	_delay_ms(2);
	PORTB = PINB | 0b00000001;
	spi_obj.setFreq(125);
	_delay_ms(2);
	// dummy cycles need to be moved to sdCard class.
	spi_obj.writeByte(0xFF);
	spi_obj.writeByte(0xFF);
	spi_obj.writeByte(0xFF);
	spi_obj.writeByte(0xFF);
	spi_obj.writeByte(0xFF);
	spi_obj.writeByte(0xFF);
	spi_obj.writeByte(0xFF);
	spi_obj.writeByte(0xFF);
	spi_obj.writeByte(0xFF);
	spi_obj.writeByte(0xFF); 
	//SendChar(0xAA);
	//_delay_ms(500);
	unsigned char result = 0x00;
	do 
	{
	PORTB = PINB & 0b11111110;
	// CMD0 needs to be moved to SD card class
	spi_obj.writeByte(0xFF);
	spi_obj.writeByte(0x40);
	spi_obj.writeByte(0x00);
	spi_obj.writeByte(0x00);
	spi_obj.writeByte(0x00);
	spi_obj.writeByte(0x00);
	spi_obj.writeByte(0x95);
	spi_obj.recieveByte();
	result = spi_obj.recieveByte();
	} while (result == 0xFF);
	    ////TODO:: Please write your application code 
	//_delay_ms(500);
    //SendChar(result);
	if(result == 0x01){
	// CMD8 needs to be moved to SD card class
		spi_obj.writeByte(0xFF);
		spi_obj.writeByte(0x48);
		spi_obj.writeByte(0x00);
		spi_obj.writeByte(0x00);
		spi_obj.writeByte(0x01);
		spi_obj.writeByte(0xAA);
		spi_obj.writeByte(0x87);
		//0x48 00 00 01 AA 87
	}else{
		SendChar(0xBB);
	}
	unsigned char cmd8result[5];
	spi_obj.recieveByte();
	for(int i = 0; i < 5; i++){
		cmd8result[i] = spi_obj.recieveByte();
	}
	for(int i = 0; i < 5; i++){
		SendChar(cmd8result[i]);
	}
	if( cmd8result[0] == 0x01 && cmd8result[1] == 0x00 && cmd8result[2] == 0x00 && cmd8result[3] == 0x01 && cmd8result[4] == 0xAA ){
		// if cmd8 successfull start initiating the card
		do{ // loop fra ACMD41 untill card goes busy.
		
			//do {
			// CMD55 part of ACMD41
		
			spi_obj.writeByte(0xFF); // sync byte
			spi_obj.writeByte(0x77);
			spi_obj.writeByte(0x00);
			spi_obj.writeByte(0x00);
			spi_obj.writeByte(0x00);
			spi_obj.writeByte(0x00);
			spi_obj.writeByte(0xFF); // dummy CRC since CRC should be off now;
			spi_obj.recieveByte();
		
			result = spi_obj.recieveByte();
			SendChar(result);
			//} while(result != 0x01);
		
		//rest of ACMD41
		spi_obj.writeByte(0xFF);
		spi_obj.writeByte(0x69); // acmd41
		spi_obj.writeByte(0x40); // HCS bit set high.
		spi_obj.writeByte(0x00);
		spi_obj.writeByte(0x00);
		spi_obj.writeByte(0x00);
		spi_obj.writeByte(0xFF); // dummy CRC
		
		result = spi_obj.recieveByte();
		SendChar(result);
		result = spi_obj.recieveByte();
		
		SendChar(result);
		} while(result != 0x00);
		
		
	}
	
	
	
	//SD_obj.setSlaveSelect(0);
	//_delay_ms(200);
	//SD_obj.dummyCycles();
	//SD_obj.writeByte(0x0F);
	//_delay_ms(200);
	//SD_obj.setSlaveSelect(1);
	//PORTB = 0b11111111;
	//_delay_ms(1000);

}