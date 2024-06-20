// ---------------------------------------------------------------------------
#ifndef ACSH
#define ACSH
#include "Bank.h"
// #include<SyncObjs.hpp>
#include<Classes.hpp>
// ---------------------------------------------------------------------------
class ACS : private TThread
{
private:
	Bank* bank;
	int period;

	void __fastcall Execute();
	void pr(AnsiString _msg);
	void DoBank();

public:
	ACS(Bank* _bank, int _period);
	__fastcall ~ACS(void);
};
#endif
