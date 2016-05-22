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


//=============================================================
// METHOD : sendCommand
// DESCR. : takes a cmd index, an argument and a CRC and creates
// and sends the command to the sd card.
//=============================================================
unsigned char sdCard::sendCommand( unsigned char cmdindex, unsigned long argument, unsigned char CRC )
{
	unsigned char *argument_byte_pointer = (unsigned char*)&argument; // creating a pointer to extract bytes to be send.
	spi_obj.writeByte(0b01000000 | cmdindex);
	spi_obj.writeByte(argument_byte_pointer[0]);
	spi_obj.writeByte(argument_byte_pointer[1]);
	spi_obj.writeByte(argument_byte_pointer[3]);
	spi_obj.writeByte(argument_byte_pointer[4]);
	spi_obj.writeByte(CRC);
	unsigned char response;
	do 
	{
		response = spi_obj.recieveByte();
	} while (response = 0xFF);
	return response;
}

