//---------------------------------------------------------------------------
#ifndef JWork502H
#define JWork502H
#include "Job.h"
#include "JCollect.h"
#include "JZoner.h"
#include "Bank.h"
#include "JSpeed502.h"
#include "Solenoid.h"
#include "JCollect502.h"
#include "JTransport502.h"
#include "ModBus.h"
#include "JRectifier.h"

//---------------------------------------------------------------------------
class JWork502 : public Job
{
private:
	int step;
	DWORD startTick;
	IsWork IW;
	JZoner jZoner;
	Bank* bank;
	CInv Inv;
//	JSpeed502 lineSpeed;
	JSpeed502 thickSpeed;
	JCollect502 collect;
//	Solenoid crossSolenoid;
//	Solenoid lineSolenoid;
//	Solenoid thickSolenoid;
	JTransport502 jTransport;
	void Finish(void);
	JRectifier jRectifier;

public:
	JWork502(IsWork _IW, Bank* _bank);
	~JWork502(void);
	void Exec();
	bool Interrupt;
};
#endif
