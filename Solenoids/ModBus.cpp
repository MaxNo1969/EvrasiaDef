#pragma hdrstop
#include "ModBus.h"
#include "PA.h"
#ifndef NOCOMPORTS
#include "uCCOMPort_real.h"
#else
#include "uCCOMPort_pseudo.h"
#endif
#pragma package(smart_init)
#include "uFunctions.h"
#include "Crc16.h"

ModBus::ModBus(void)
{
	timeout = 1;
	comport = NULL;
	OnProtocolL = NULL;
	max_iters = 5;
	AnsiString error_msg;
#ifndef NOCOMPORTS
	comport = CCOMPort_real::Create(PA("Defect.ComPortMagnit"), &error_msg);
#else
	comport = CCOMPort_pseudo::Create();
#endif
	if (comport == NULL)
	{
		pr(-1, error_msg);
		AnsiString a = "Open: не могу открыть COM порт";
		pr(-1, a);
		FATAL(a);
	}
	comport->OnProtocol = OnProtocolL;
	timeout = PA("Defect.ComPortMagnit.Timeout").Int();
	CS=new TCriticalSection();
}

ModBus::~ModBus(void)
{
	delete CS;
	delete comport;
}
void ModBus::pr(AnsiString _msg)
{
	if(OnProtocolL!=NULL)
		OnProtocolL(AnsiString("ModBus: ")+_msg);
}

void ModBus::FOnProtocolWrite(OnProtocolDef _v)
{
	OnProtocolL = _v;
	if (comport != NULL)
		comport->OnProtocol = OnProtocolL;
}

void ModBus::pr(int _abonent, AnsiString _msg)
{
	if (OnProtocolL == NULL)
		return;
	AnsiString a = "ModBus[";
	a += _abonent;
	a += "]: ";
	a += _msg;

	OnProtocolL(a);
}
AnsiString ModBus::PresetSingleRegister0(int _abonent, int _pos, unsigned short _data)
{
	unsigned char query[] =
	{(unsigned char)_abonent, 6, 0, (unsigned char)_pos, (unsigned char)((_data >> 8) & 0xff), (unsigned char)(_data & 0xff), 0, 0
	};
	Crc16::Add(query, 8);
	if (!comport->write_s(query, 8))
		return ("Не смогли записать");
	// 0 - абонент
	// 1 - ошибки
	// 2 - код ошиибки
	// 3 - crc
	// 4 - crc
	unsigned char* packet = "1234567";
	if (!comport->read_s(packet, 8))
		return ("Не смогли прочитать");
	if (packet[0] != _abonent)
		return ("Не тот абонент");
	if ((packet[1] & 0x80) != 0)
		return (AnsiString("Ошибка в ответе: ") + packet[2]);
	if (packet[2] != 0)
		return ("Не тот регистр");
	if (packet[3] != (unsigned char)_pos)
		return ("Не тот регистр");
	if (!Crc16::Check(packet, 8))
		return ("Не верная контрольная сумма");
	return (NULL);
}
AnsiString ModBus::PresetSingleRegister(int _abonent, int _pos, unsigned short _data)
{
	AnsiString ret;
	CS->Enter();
	ret=PresetSingleRegister0(_abonent, _pos, _data);
	CS->Leave();
	return(ret);
}

AnsiString ModBus::ReadRegister0(char _cmd, int _abonent, int _pos, unsigned short* _result)
{
	unsigned char query[] =
	{(unsigned char)_abonent, (unsigned char)_cmd, 0, (unsigned char)_pos, 0, 1, 0, 0};
	Crc16::Add(query, 8);
	if (!comport->write_s(query, 8))
		return ("Не смогли записать");
	// 0 - абонент
	// 1 - ошибки
	// 2 - длина / код ошибки
	// 3 - данные
	// 4 - данные
	// 5 - crc
	// 6 - crc
	unsigned char* packet = "12345678";
	if (!comport->read_s(packet, 7))
		return ("Не смогли прочитать");
	if (packet[0] != _abonent)
		return ("Не тот абонент");
	if ((packet[1] & 0x80) != 0)
		return (AnsiString("Ошибка в ответе: ") + packet[2]);
	if (packet[2] != 2)
		return ("Не верная длина в ответе");
	if (!Crc16::Check(packet, 7))
		return ("Не верная контрольная сумма");
	unsigned char buf[2];
	buf[0]=packet[4];
	buf[1]=packet[3];
	*_result = ((unsigned short*)(buf))[0];
	return (NULL);
}
AnsiString ModBus::ReadRegister(char _cmd, int _abonent, int _pos, unsigned short* _result)
{
	AnsiString ret;
	CS->Enter();
	ret=ReadRegister0(_cmd, _abonent, _pos, _result);
	CS->Leave();
	return(ret);
}

AnsiString ModBus::PresetSingleRegisterE(int _abonent, int _pos, unsigned short _data)
{
	AnsiString ret = NULL;
	for (int i = 0; i < max_iters; i++)
	{
		ret = PresetSingleRegister(_abonent, _pos, _data);
		if (ret == NULL)
			break;
		pr(_abonent,ret);
		Sleep(timeout);
	}
	return (ret);
}
AnsiString ModBus::ReadRegisterE(char _cmd, int _abonent, int _pos, unsigned short* _result)
{
	AnsiString ret = NULL;
	for (int i = 0; i < max_iters; i++)
	{
		ret = ReadRegister(_cmd, _abonent, _pos, _result);
		if (ret == NULL)
			break;
		pr(_abonent,ret);
		Sleep(timeout);
	}
	return (ret);
}

AnsiString ModBus::WriteReadE(int _abonent, int _pos, unsigned short _data)
{
	AnsiString sret=PresetSingleRegisterE(_abonent, _pos, _data);
	if(sret!=NULL)
		return(sret);
	unsigned short new_data=0;
	sret = ReadRegisterE(3, _abonent, _pos, &new_data);
	if(sret!=NULL)
		return(sret);
	if(_data!=new_data)
	{
		pr(_abonent,"Чтение после записи не совпадает");
		return("Чтение после записи не совпадает");
	}
	return(NULL);
}
AnsiString ModBus::ReadWriteReadE(int _abonent, int _pos, unsigned short _data)
{
	unsigned short new_data=0;
	AnsiString sret = ReadRegisterE(3, _abonent, _pos, &new_data);
	if(sret!=NULL)
		return(sret);
	if(_data==new_data)
		return(NULL);

	sret=PresetSingleRegisterE(_abonent, _pos, _data);
	if(sret!=NULL)
		return(sret);

	sret = ReadRegisterE(3, _abonent, _pos, &new_data);
	if(sret!=NULL)
		return(sret);
	if(_data!=new_data)
		return("Чтение после записи не совпадает");
	return(NULL);
}

AnsiString ModBus::Write(int _abonent, int _pos, int _data)
{
	return (PresetSingleRegisterE(_abonent, _pos, (unsigned short)_data));
}

AnsiString ModBus::Write(int _abonent, int _pos, double _data)
{
	return (PresetSingleRegisterE(_abonent, _pos, (unsigned short)(_data * 10)));
}

AnsiString ModBus::Write(int _abonent, int _pos, bool _data)
{
	return (PresetSingleRegisterE(_abonent, _pos, (unsigned short)(_data != 0 ? 1 : 0)));
}


AnsiString ModBus::ReadInput(int _abonent, int _pos, int* _result)
{
	unsigned short ret;
	AnsiString sret = ReadRegisterE(4, _abonent, _pos, &ret);
	*_result = ret;
	return (sret);
}

AnsiString ModBus::ReadInput(int _abonent, int _pos, double* _result)
{
	unsigned short ret;
	AnsiString sret = ReadRegisterE(4, _abonent, _pos, &ret);
	*_result = ((double)ret) / 10;
	return (sret);
}

AnsiString ModBus::ReadHolding(int _abonent, int _pos, int* _result)
{
	unsigned short ret;
	AnsiString sret = ReadRegisterE(3, _abonent, _pos, &ret);
	*_result = ret;
	return (sret);
}

AnsiString ModBus::ReadHolding(int _abonent, int _pos, double* _result)
{
	unsigned short ret;
	AnsiString sret = ReadRegisterE(3, _abonent, _pos, &ret);
	*_result = ((double)ret) / 10;
	return (sret);
}

AnsiString ModBus::ReadHolding(int _abonent, int _pos, bool* _result)
{
	unsigned short ret;
	AnsiString sret = ReadRegisterE(3, _abonent, _pos, &ret);
	*_result = ret != 0 ? true : false;
	return (sret);
}

AnsiString ModBus::WriteCheck(int _abonent, int _pos, int _data)
{
	return (ReadWriteReadE(_abonent, _pos, (unsigned short)_data));
}

AnsiString ModBus::WriteCheck(int _abonent, int _pos, double _data)
{
	return (ReadWriteReadE(_abonent, _pos, (unsigned short)(_data*10)));
}

AnsiString ModBus::WriteCheck(int _abonent, int _pos, bool _data)
{
	return (ReadWriteReadE(_abonent, _pos, (unsigned short)(_data != 0 ? 1 : 0)));
}
