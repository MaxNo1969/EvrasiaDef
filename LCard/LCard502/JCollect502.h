#ifndef JCollect502H
#define JCollect502H
#include "LCard502.h"
#include "Bank.h"

// ---------------------------------------------------------------------------
class JCollect502
{
private:
	Bank* bank;
	DWORD LastExec;
	IsWork IW;
	bool started;
	DWORD ReadPeriod;
	bool error;

	LCard502Pars lcardPars;
	LCard502 lcard;

	void Init(Bank* _bank, IsWork _IW);
	void pr(AnsiString _msg);

public:
	JCollect502(Bank* _bank, IsWork _IW);
	JCollect502();
	~JCollect502(void);
	void LoadSettings(void);

	void Start(void);
	void Stop(DWORD _tick);
	bool Exec(DWORD _tick);

	double GetValueV(RChannel_parameters* _channel, bool* _ret);
	double GetValueP(RChannel_parameters* _channel, bool* _ret);

	inline bool IsStarted(void)
	{
		return (started);
	}

	inline bool IsError(void)
	{
		return (error);
	}

	inline AnsiString GetErrorMsg()
	{
		return (AnsiString("lcard: ") + lcard.LastError);
	}
};
// ---------------------------------------------------------------------------
#endif
