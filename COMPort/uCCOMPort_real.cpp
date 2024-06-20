#pragma hdrstop
#include "uCCOMPort_real.h"
#pragma package(smart_init)
#include "uCCOMPort.h"
#pragma package(smart_init)
#include "COMPortPars.h"

// ---------------------------------------------------------------------------
CCOMPort_real::CCOMPort_real(PA _pa, AnsiString* _error_msg)
{
	COMPortPars Pars;
	Pars.Load(_pa);
	*_error_msg = "";
	WideString w = "\\\\.\\";
	w += Pars.Port;
	handleCom = CreateFile(w.c_bstr(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, 0, 0);
	if (handleCom == INVALID_HANDLE_VALUE)
	{
		*_error_msg = "CCOMPort::Create: Не могу открыть порт: ";
		*_error_msg += Pars.Port;
		return;
	}
	DCB dcb;
	GetCommState(handleCom, &dcb);
	dcb.BaudRate = Pars.BaudRate;
	dcb.Parity = (BYTE)Pars.Parity;
	dcb.StopBits = (BYTE)Pars.StopBits;
	dcb.ByteSize = (BYTE)Pars.ByteSize;
	if (SetCommState(handleCom, &dcb) == 0)
	{
		*_error_msg = "CCOMPort::Create: ";
		*_error_msg += Pars.Port;
		*_error_msg += ": не могу выставить состояние";
		return;
	}
	COMMTIMEOUTS t;
	GetCommTimeouts(handleCom, &t);
	t.ReadIntervalTimeout = Pars.ReadIntervalTimeout;
	t.ReadTotalTimeoutMultiplier = Pars.ReadTotalTimeoutMultiplier;
	t.ReadTotalTimeoutConstant = Pars.ReadTotalTimeoutConstant;
	if (SetCommTimeouts(handleCom, &t) == 0)
	{
		*_error_msg = "CCOMPort::Create: ";
		*_error_msg += Pars.Port;
		*_error_msg += ": не могу выставить задержки";
		return;
	}
	if (SetCommMask(handleCom, 0) == 0)
	{
		*_error_msg = "CCOMPort::Create: ";
		*_error_msg += Pars.Port;
		*_error_msg += ": не могу выставить маску событий";
		return;
	}
	OnProtocol = NULL;
	verbal = Pars.IsProtocol;
}

CCOMPort_real* CCOMPort_real::Create(PA _pa, AnsiString* _error_msg)
{
	*_error_msg = "";
	CCOMPort_real* P = new CCOMPort_real(_pa, _error_msg);
	if ((*_error_msg).Length() != 0)
	{
		delete P;
		return (NULL);
	}
	return (P);
}

// ---------------------------------------------------------------------------
CCOMPort_real::~CCOMPort_real(void)
{
	CloseHandle(handleCom);
}

// ---------------------------------------------------------------------------
bool CCOMPort_real::read_s(unsigned char* _s, int _n)
{
	unsigned long ln = _n;
	ReadFile(handleCom, _s, _n, &ln, NULL);
	if (OnProtocol != NULL)
	{
		if (verbal)
		{
			AnsiString a;
			for (unsigned long i = 0; i < ln; i++)
			{
				a.printf("r[%d]: %X", (int)i, _s[i]);
				OnProtocol(a);
			}
		}
	}
	if (ln < (unsigned long)_n)
		return (false);
	return (true);
}

// ------------------------------------------------------------------------------
bool CCOMPort_real::write_s(unsigned char* _s, int _n)
{
	unsigned long ln = _n;
	WriteFile(handleCom, _s, _n, &ln, NULL);
	if (OnProtocol != NULL)
	{
		if (verbal)
		{
			AnsiString a;
			for (unsigned long i = 0; i < ln; i++)
			{
				a.printf("w[%d]: %d %X |%c|", (int)i, _s[i], _s[i], _s[i]);
				OnProtocol(a);
			}
		}
	}
	if (ln < (unsigned long)_n)
		return (false);
	return (true);
}

// ------------------------------------------------------------------------------
void CCOMPort_real::ClearBuffer(void)
{
	PurgeComm(handleCom, PURGE_RXCLEAR);
}
