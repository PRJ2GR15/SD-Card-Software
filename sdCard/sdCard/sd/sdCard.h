//========================================================================
// FILENAME : sdCard.h
// CREATED : 22-05-2016
// AUTHOR : Tonni Follmann
// DESCR. : Header file for the arduino SD Card driver.
//
//------------------------------------------------------------------------
//
// REV. DATE/AUTHOR CHANGE DESCRIPTION
// 1.0 22-05-2016/Tonni Nybo Follmann created the initial header file.
//========================================================================
#include <avr/io.h>
#include "../SPI/SPI.h"

#ifndef SDCARD_H_
#define SDCARD_H_

#define SS 0 // using Port B pin 0 as SS ; pin 53 on arduino board.

// helper type to make it easier to handle commands.
struct SD_Card_command{
	union{
		unsigned char command;
		unsigned int 
		};
	};

//=====================================
// CLASS : sdCard
// DESCR. : represends the SD card controlled using SPI in master mode
// on arduino mega2560, the sd card i used in raw block access mode.
//=====================================

class sdCard{
	public:
		sdCard(int speed);
		bool init(); // initializes the SD card.
		bool writeBlock(unsigned char adress, const unsigned char data[], int data_length); // data_length must be less than 512.
		bool readBlock(unsigned char adress, unsigned char data[], int data_length); // will fill the supplied array with the content of the block on the sd card.
	private:
		SPI spi_obj;
		int speed;
		unsigned char sendCommand(unsigned char cmdindex, unsigned long argument, unsigned char CRC); // used internally to send a sd command.
};



#endif /* SDCARD_H_ */