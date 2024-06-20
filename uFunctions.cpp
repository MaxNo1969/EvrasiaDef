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
	if (_module == "����������")
		return (1);
	else if (_module == "����������")
		return (2);
	else if (_module == "����������")
		return (3);
	else
		return (0);
}

// ---------------------------------------------------------------------------
AnsiString IntModule(int _module)
{
	if (_module == 1)
		return ("����������");
	else if (_module == 2)
		return ("����������");
	else if (_module == 3)
		return ("����������");
	else
		return ("NoName");
}

// ---------------------------------------------------------------------------
int DefTypeInt(AnsiString _module, AnsiString _DefType)
{
	if (_module == "����������")
	{
		if (_DefType == "�� 3 ��������")
			return (1);
		else if (_DefType == "��� �������")
			return (2);
		else
			return (0);
	}
	else if (_module == "����������")
	{
		if (_DefType == "��� �������")
			return (1);
		else if (_DefType == "1 � �����")
			return (2);
		else
			return (0);
	}
	else if (_module == "����������")
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
			return ("�� 3 ��������");
		else if (_DefType == 2)
			return ("��� �������");
		else
			return ("NoType");
	}
	else if (_module == 2)
	{
		if (_DefType == 1)
			return ("��� �������");
		else if (_DefType == 2)
			return ("1 � �����");
		else
			return ("NoType");
	}
	else if (_module == 3)
		return ("����������");
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
	Application->MessageBoxW(w.c_bstr(), L"��������� ����������",
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
			AnsiString a = "Fread: ����������� ����� �����: ";
			a += pos;
			throw(Exception(a));
		}
		else
			throw(Exception("Fread: ����������� ������"));
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

