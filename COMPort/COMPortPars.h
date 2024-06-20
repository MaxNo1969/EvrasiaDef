#ifndef COMPortParsH
#define COMPortParsH
#include "PA.h"
//---------------------------------------------------------------------------
class COMPortPars
{
private:
public:
	COMPortPars(void);
	void Load(PA _pa);
	AnsiString Port;
	int BaudRate;
	int ByteSize;
	int Parity;
	int StopBits;
	int ReadIntervalTimeout;
	int ReadTotalTimeoutConstant;
	int ReadTotalTimeoutMultiplier;
	bool IsProtocol;
};
//---------------------------------------------------------------------------
#endif
