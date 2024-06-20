#ifndef ThWorkH
#define ThWorkH
#include "ThBase.h"
#include "Bank.h"

#include "JWork502.h"

// ---------------------------------------------------------------------------
class ThWork : public ThBase
{
private:
	IsWork IW;
	void __fastcall Execute();
	JWork502 jWork;

public:
	__fastcall ThWork(IsWork _IW, Bank* _bank);
};
// ---------------------------------------------------------------------------
#endif
