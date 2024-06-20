#pragma hdrstop
#include "MitFX.h"
#pragma package(smart_init)
#include "Protocol.h"
#ifndef NOCOMPORTS_FX
#include "uCCOMPort_real.h"
#else
#include "uCCOMPort_pseudo.h"
#endif
#include "uFunctions.h"
#include "MitC.h"

MitFX::MitFX(void)
{
	pr("Конструктор");
	AnsiString error_msg;
#ifndef NOCOMPORTS_FX
	comport = CCOMPort_real::Create(PA("Defect.MitFX.ComPort"), &error_msg);
#else
	comport = CCOMPort_pseudo::Create();
#endif
	if (comport == NULL)
	{
		pr(error_msg);
		AnsiString a = "Open: не могу открыть COM порт";
		pr(a);
		FATAL(a);
	}
//	comport->OnProtocol = pr;
	Abonent = PA("Defect.MitFX.Abonent").Int();
	PLC = PA("Defect.MitFX.PLC").Int();
	Timeout = PA("Defect.MitFX.Timeout").Int();
}

MitFX::~MitFX(void)
{
	pr("Деструктор");
	delete comport;
}

void MitFX::pr(AnsiString _msg)
{
	TPr::pr("MitFX: " + _msg);
}

int MitFX::ReadRegI(int _register, AnsiString* _result)
{
	*_result = "Ok";
	AnsiString req = Request(_register);
	comport->ClearBuffer();
	if (!comport->write_s(req.c_str(), req.Length()))
	{
		*_result = "Не смогли послать запрос";
		return (0);
	}
	char* s = "12345";
	AnsiString packet;
	ReplyFX_NAK rNAK = ReplyFX_NAK(Abonent, PLC);
	ReplyFX_ACK rACK = ReplyFX_ACK(Abonent, PLC);
	ReplyFX_STX rSTX = ReplyFX_STX(Abonent, PLC);
	for (; ;)
	{
		if (!comport->read_s(s, 1))
		{
			if (packet.Length() == 0)
				* _result = "Нет ответа";
			else
				*_result = "Ответ не разобран - короткий";
			return (0);
		}
		else
			packet += s[0];
		if (rNAK.Parse(packet))
		{
			*_result = "NAK: rNAK.Error";
			return (0);
		}
		if (rACK.Parse(packet))
		{
			*_result = "Неожиданно пришел ACK";
			return (0);
		}
		if (rSTX.Parse(packet))
		{
			AnsiString result = rSTX.result;
			if (result.Length() != 4)
			{
				*_result = "Не верная длина данных";
				return (0);
			}
			AnsiString aACK = GetACK();
			if (!comport->write_s(aACK.c_str(), aACK.Length()))
			{
				*_result = "Не смогли подтвердить ACK";
				return (0);
			}
			AnsiString H0 = "0x";
			return (StrToInt(H0 + result));
		}
	}
}

AnsiString MitFX::WriteRegI(int _register, int _val)
{
	AnsiString req = Request(_register,_val);
	comport->ClearBuffer();
	if (!comport->write_s(req.c_str(), req.Length()))
		return ("Не смогли послать запрос");
	char* s = "12345";
	AnsiString packet;
	ReplyFX_NAK rNAK = ReplyFX_NAK(Abonent, PLC);
	ReplyFX_ACK rACK = ReplyFX_ACK(Abonent, PLC);
	for (; ;)
	{
		if (!comport->read_s(s, 1))
		{
			if (packet.Length() == 0)
				return ("Нет ответа");
			else
				return ("Ответ не разобран - короткий");
		}
		else
			packet += s[0];
		if (rNAK.Parse(packet))
			return (rNAK.Error);
		if (rACK.Parse(packet))
			return ("Ok");
	}
}

AnsiString MitFX::Request(int _register)
{
	AnsiString ret = "";

	ret.cat_sprintf("%c%02X%02XWR%0XD%04d%02X", MitC::ENQ, Abonent, PLC, Timeout,
		_register, 1);
//	ret += MitC::CRC(ret.SubString(2, ret.Length() - 1));
	return (ret);
}

AnsiString MitFX::Request(int _register, int _val)
{
	AnsiString ret = "";

	ret.cat_sprintf("%c%02X%02XWW%0XD%04d%02X%04X", MitC::ENQ, Abonent, PLC, Timeout,
		_register, 1,_val);
//	ret += MitC::CRC(ret.SubString(2, ret.Length() - 1));
	return (ret);
}

AnsiString MitFX::GetACK()
{
	AnsiString ret = "";
	ret += MitC::ACK;
	ret.cat_sprintf("%02X", Abonent);
	ret.cat_sprintf("%02X", PLC);
	return (ret);

}
int MitFX::GetTubeLength(AnsiString* _result)
{
	return(ReadRegI(PA("Defect.MitFX.Registers.TubeLength").Int(), _result));
}
AnsiString MitFX::SetSG(AnsiString _SG)
{
// ' 0-(-), 1-D, 2-K, 3-E, 4-N80, 5-P (P110), 6-Q (Q125),
 // 7-L, 8-M, 9-P, 10-J55 (J-55), 11-K55 (K-55), 12-C90, 13-T95, 14-H40, 15-L80, 16-C95, 17-M65, 18-NQ(N80Q)'
	int isg=0;
	if(_SG=="D")
		isg=1;
	else if(_SG=="K")
		isg=2;
	else if(_SG=="E")
		isg=3;
	else if(_SG=="N80")
		isg=4;
	else if(_SG=="P")
		isg=5;
	else if(_SG=="P110")
		isg=5;
	else if(_SG=="Q")
		isg=6;
	else if(_SG=="Q125")
		isg=6;
	else if(_SG=="L")
		isg=7;
	else if(_SG=="M")
		isg=8;
	else if(_SG=="P")
		isg=9;
	else if(_SG=="J55")
		isg=10;
	else if(_SG=="J-55")
		isg=10;
	else if(_SG=="K55")
		isg=11;
	else if(_SG=="K-55")
		isg=11;
	else if(_SG=="C90")
		isg=12;
	else if(_SG=="T95")
		isg=13;
	else if(_SG=="H40")
		isg=14;
	else if(_SG=="L80")
		isg=15;
	else if(_SG=="C95")
		isg=16;
	else if(_SG=="M65")
		isg=17;
	else if(_SG=="NQ")
		isg=18;
	else if(_SG=="N80Q")
		isg=18;
	else
		isg=0;
	return(WriteRegI(PA("Defect.MitFX.Registers.SG").Int(), isg));
}



