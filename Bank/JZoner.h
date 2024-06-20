#ifndef JZonerH
#define JZonerH
#include "Bank.h"
#include "IsWork.h"
#include "uCRListT.h"
#include "ACS.h"

// ---------------------------------------------------------------------------
class JZoner
{
private:
	Bank* bank;
	bool started;
	DWORD LastExec;
	DWORD ReadPeriod;
	IsWork IW;
	void pr(AnsiString _msg);
	ACS* acs;
public:
	JZoner(Bank* _bank, IsWork _IW);
	~JZoner(void);
	void Start(void);
	void Exec(DWORD _tick);
	void Exec(void);
};
// ---------------------------------------------------------------------------
#endif
