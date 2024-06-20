#pragma hdrstop
#include "COMPortPars.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
COMPortPars::COMPortPars(void)
{
	Port = NULL;
	BaudRate = 0;
	ByteSize = 0;
	Parity = 0;
	StopBits = 0;
	ReadIntervalTimeout = 0;
	ReadTotalTimeoutConstant = 0;
	ReadTotalTimeoutMultiplier = 0;
	IsProtocol=true;
}

//---------------------------------------------------------------------------
void COMPortPars::Load(PA _pa)
{
	Port = _pa.Item("Port").String();
	BaudRate = _pa.Item("BaudRate").Int();
	ByteSize = _pa.Item("ByteSize").Int();
	Parity = _pa.Item("Parity").Int();
	StopBits = _pa.Item("StopBits").Int();
	ReadIntervalTimeout = _pa.Item("ReadIntervalTimeout").Int();
	ReadTotalTimeoutConstant = _pa.Item("ReadTotalTimeoutConstant").Int();
	ReadTotalTimeoutMultiplier = _pa.Item("ReadTotalTimeoutMultiplier").Int();
	IsProtocol=_pa.Item("IsProtocol").Bool();
}
//---------------------------------------------------------------------------
