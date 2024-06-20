#ifndef JTransport502H
#define JTransport502H
#include "Bank.h"
#include "Signal.h"
#include "IsWork.h"
#include "TransportEvent.h"
#include "JSpeed502.h"
#include "DimensionPars.h"

//---------------------------------------------------------------------------
class JTransport502
{
private:
	TESignal* teOn;
	TESignal* teOff0;
	TESignal* teOff1;
	TEStrobe* teStrobe;
	TESignal* teSGOn;
	TESignal* teSGOff;
	TList* L;

	TESignal* teTC_On;
	TESignal* teLC_On;
	TESignal* teTC_Off;
	TESignal* teLC_Off;



	bool started;
	IsWork IW;
	bool error;
	AnsiString errorMsg;
	DWORD startTick;
	int ZoneLength;
	int testLastZone;
	double TubeLengthTest;
	double TubeSpeed_mm_ms;
	Bank* bank;
	int step;
	void pr(AnsiString _msg);

	int CalcDelta(DWORD _tick);
	JSpeed502* lineSpeed;
	JSpeed502* thickSpeed;
	int TimeoutSG;
	void SetA1730(DimensionPars* _pars);
	void SetL502(DimensionPars* _pars);

public:
	JTransport502(Bank* _bank, IsWork _IW,JSpeed502* _lineSpeed,JSpeed502* _thickSpeed);
	~JTransport502(void);
	void Start(void);
	bool Exec(DWORD _tick);
	bool ExecTest(DWORD _tick);
	void Report(void);

	inline bool IsError(void)
	{
		return (error);
	};

	inline AnsiString GetErrorMsg()
	{
		return (errorMsg);
	}
};
//---------------------------------------------------------------------------
#endif
