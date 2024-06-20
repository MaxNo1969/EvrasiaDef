#pragma hdrstop
#include "ReplyFX.h"
#include "MitC.h"
#pragma package(smart_init)

ReplyFX::ReplyFX(int _Abonent, int _PLC)
{
	Abonent = _Abonent;
	PLC = _PLC;
	Head="";
	Head.cat_sprintf("%02X%02X", Abonent,PLC);
}

bool ReplyFX_NAK::Parse(AnsiString _l)
{
	if(_l[1]!=MitC::NAK)
		return (false);
	if (_l.Length() < 7)
		return (false);
	if (_l.SubString(2, 4) != Head)
		return (false);
	AnsiString result = _l.SubString(6, 2);
	if(result=="02")
		Error="02 Sum check error";
	else if(result=="03")
		Error="03 Protocol check error";
	else if(result=="06")
		Error="06 Character area error";
	else if(result=="07")
		Error="07 Character error";
	else if(result=="0A")
		Error="0A PLC number error";
	else if(result=="10")
		Error="10 PLC number error";
	else if(result=="18")
		Error="18 Remote control error";
	else
	{
		Error=result;
		Error+=" неизвестая ошибка";
	}
	return (true);
}

bool ReplyFX_ACK::Parse(AnsiString _l)
{
	if(_l[1]!=MitC::ACK)
		return (false);
	if (_l.Length() < 5)
		return (false);
	if (_l.SubString(2, 4) != Head)
		return (false);
	return (true);
}

bool ReplyFX_STX::Parse(AnsiString _l)
{
	if(_l[1]!=MitC::STX)
		return (false);
	if (_l.Length() < 8)
		return (false);
	if (_l.SubString(2, 4) != Head)
		return (false);
	int posETX=_l.Pos(MitC::ETX);
	if(posETX<6)
		return (false);
//	if(_l.Length()<posETX+2)
	if(_l.Length()<posETX)
		return (false);
//	if (MitC::CRC(_l.SubString(2,posETX-1)) != _l.SubString(posETX+1, 2))
//		return (false);
	result = _l.SubString(6,posETX-6);
	return (true);
}

