// ---------------------------------------------------------------------------
#pragma hdrstop
#include "uFunctions.h"
#include <stdio.h>
#ifndef NO_BANK
#include "SignalListDef.h"
#endif
// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
int ModuleInt(AnsiString _module)
{
	if (_module == "Поперечный")
		return (1);
	else if (_module == "Продольный")
		return (2);
	else if (_module == "Толщиномер")
		return (3);
	else
		return (0);
}

// ---------------------------------------------------------------------------
AnsiString IntModule(int _module)
{
	if (_module == 1)
		return ("Поперечный");
	else if (_module == 2)
		return ("Продольный");
	else if (_module == 3)
		return ("Толщиномер");
	else
		return ("NoName");
}

// ---------------------------------------------------------------------------
int DefTypeInt(AnsiString _module, AnsiString _DefType)
{
	if (_module == "Поперечный")
	{
		if (_DefType == "До 3 соседних")
			return (1);
		else if (_DefType == "Все датчики")
			return (2);
		else
			return (0);
	}
	else if (_module == "Продольный")
	{
		if (_DefType == "Все датчики")
			return (1);
		else if (_DefType == "1 и более")
			return (2);
		else
			return (0);
	}
	else if (_module == "Толщиномер")
		return (1);
	else
		return (0);
}

// ---------------------------------------------------------------------------
AnsiString IntDefType(int _module, int _DefType)
{
	if (_module == 1)
	{
		if (_DefType == 1)
			return ("До 3 соседних");
		else if (_DefType == 2)
			return ("Все датчики");
		else
			return ("NoType");
	}
	else if (_module == 2)
	{
		if (_DefType == 1)
			return ("Все датчики");
		else if (_DefType == 2)
			return ("1 и более");
		else
			return ("NoType");
	}
	else if (_module == 3)
		return ("Толщиномер");
	else
		return ("NoType");
}

// ---------------------------------------------------------------------------
void FATAL(AnsiString _msg)
{
#ifndef NO_BANK
	if(SLD!=NULL)
		SLD->ResetSignals();
#endif
	WideString w = _msg;
	Application->MessageBoxW(w.c_bstr(), L"Аварийное завершение",
		MB_ICONERROR | MB_OK);
	throw;
}
// ---------------------------------------------------------------------------
void Fread(void* _buf, int _size, int _n, FILE* _df)
{
	if (fread(_buf, _size, _n, _df) != _n)
	{
		if (feof(_df))
		{
			fpos_t pos;
			fgetpos(_df, &pos);
			AnsiString a = "Fread: Неожиданный конец файла: ";
			a += pos;
			throw(Exception(a));
		}
		else
			throw(Exception("Fread: Неизвестная ошибка"));
	}
}
// ---------------------------------------------------------------------------
AnsiString LastErrorMsg()
{
		DWORD dw = GetLastError();
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
	AnsiString a=(LPCTSTR)lpMsgBuf;
	return(a);
}
// ---------------------------------------------------------------------------

