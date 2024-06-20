#pragma hdrstop
#include "MitC.h"
#pragma package(smart_init)
char MitC::ENQ = (char)0x05;
char MitC::STX = (char)0x02;
char MitC::ETX = (char)0x03;
char MitC::ACK = (char)0x06;
char MitC::NAK = (char)0x15;
char MitC::CR = (char)0x0D;
char MitC::LF = (char)0x0A;
AnsiString MitC::CRC(AnsiString _packet)
{
	int crc = 0;
	for (int i = 0; i < _packet.Length(); i++)
		crc += _packet[i + 1];
	crc &= 0xFF;
	AnsiString ret = "";
	ret.cat_sprintf("%02X", crc);
	return (ret);
}
