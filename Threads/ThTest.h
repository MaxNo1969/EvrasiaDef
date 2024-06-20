#ifndef ThTestH
#define ThTestH
#include "ThBase.h"
#include "Bank.h"
#include "JCollect502.h"

// ---------------------------------------------------------------------------
class ThTest : public ThBase
{
private:
	void __fastcall Execute();
	IsWork IW;
	Bank* bank;
	JCollect502 jCollect502;
public:
	__fastcall ThTest(Bank* _bank);

};
// ---------------------------------------------------------------------------
#endif
