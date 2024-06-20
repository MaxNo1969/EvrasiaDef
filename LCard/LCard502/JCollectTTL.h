#ifndef JCollectTTLH
#define JCollectTTLH
#include "LCard502.h"
class JCollectTTL
{
private:
	DWORD LastExec;
	bool started;
	DWORD ReadPeriod;
	bool error;

	LCard502Pars lcardPars;
	LCard502 lcard;

	void Init(void);
	void pr(AnsiString _msg);
	void LoadSettings(void);

public:
	JCollectTTL(void);
	~JCollectTTL(void);

	void Start(void);
	void Stop(DWORD _tick);
	bool Exec(DWORD _tick);

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

#endif
