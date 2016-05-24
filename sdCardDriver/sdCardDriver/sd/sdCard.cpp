//========================================================================
// FILENAME : sdCard.cpp
// CREATED : 22-05-2016
// AUTHOR : Tonni Follmann
// DESCR. : Implementation file for the ardiono SD Card driver.
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 22-05-2016/Tonni Nybo Follmann created the initial header file.
//========================================================================
 #include "sdCard.h"
 
 //=============================================================
 // METHOD : sdCard Constructor
 // DESCR. : runs the initiation sequence of the sd card and sets 
 // SPI to the supplied speed
 //=============================================================
 
 sdCard::sdCard( int speed ) : spi_obj(125)
 {
	 
	 DDRB = DDRB| (1 << SS);
	 this->speed = speed;
	  
 }


//=============================================================
// METHOD : sendCommand
// DESCR. : takes a cmd index, an argument and a CRC and creates
// and sends the command to the sd card.
//=============================================================
void sdCard::sendCommand( unsigned char cmdindex, unsigned long argument, unsigned char CRC )
{
	unsigned char *argument_byte_pointer = (unsigned char*)&argument; // creating a pointer to extract bytes to be send.
	spi_obj.writeByte(0b01000000 | cmdindex);
	spi_obj.writeByte(argument_byte_pointer[0]);
	spi_obj.writeByte(argument_byte_pointer[1]);
	spi_obj.writeByte(argument_byte_pointer[3]);
	spi_obj.writeByte(argument_byte_pointer[4]);
	spi_obj.writeByte(CRC);
}

void sdCard::dummyCycles()
{
	for(int i = 0; i < 11; i++)
	{ // generate 80 clock cycles to sync before starting the initiation sequence at lower than 400 kHz as per sd spec
		spi_obj.writeByte(0xFF);
	}	
}

bool sdCard::setSlaveSelect( int sspin )
{
	unsigned char mask;
	switch(sspin)
	{
		case 0: 
			mask = 0b11111110;
			PORTB = (PINB & mask); // sets SS pin low
			break;
		case 1:
		default:
			mask = 0b00000001;
			PORTB = (PINB | mask);
			break;
	}	
}

void sdCard::sendCmd0()
{
	sendCommand(0,0x00000000, 0x95);
}

unsigned char sdCard::getResponeByte()
{
	return spi_obj.recieveByte();
}

void sdCard::writeByte( unsigned char bla)
{
	spi_obj.writeByte(bla);
}








