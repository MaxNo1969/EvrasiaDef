// ---------------------------------------------------------------------------
#pragma hdrstop
#include "uCRequest.h"
#include <stdio.h>
#include "MitC.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
CRequest::CRequest(int _abonent,int _timeout,AnsiString _type,AnsiString _cmd)
{
	abonent=_abonent;
	timeout=_timeout;
	cmd=_cmd;
	if(_type=="B")
		data_size=0;
	else if(_type=="A")
		data_size=4;
	else if(_type=="A1")
		data_size=2;
	else
		data_size=0;
	data="";
}
AnsiString CRequest::IntToHex2(int _v)
{
	char* s="00";
	sprintf(s,"%02X",_v);
	AnsiString ret=s;
	return(ret);
}
AnsiString CRequest::IntToHex(int _v)
{
	char* s="00";
	sprintf(s,"%X",_v);
	AnsiString ret=s;
	return(ret);
}

AnsiString CRequest::Get()
{
	AnsiString packet;
	packet+=MitC::ENQ;
	packet+=IntToHex2(abonent);
	packet+=cmd;
	packet+=IntToHex(timeout);
	if(data_size!=0)
		packet+=data;
	packet+=MitC::CRC(packet.SubString(2,packet.Length()-1));
	packet+=MitC::CR;
	return (packet);
}

