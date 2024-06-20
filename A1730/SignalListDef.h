//---------------------------------------------------------------------------
#ifndef SignalListDefH
#define SignalListDefH
//---------------------------------------------------------------------------
#include "SignalList.h"
#include "Save1730.h"
#include "CatchSignals.h"

class SignalListDef : public SignalList
{
private:
	virtual bool CheckAlarm(void);

	bool CrossCycle;
	bool LinearCycle;
	bool InvA;

	void Drop(DWORD _tick);
	Save1730 save1730;
	virtual void Save(DWORD _in,DWORD _out);
	virtual void Catch(void);
	CatchSignals catchSignals;
public:
	SignalListDef(void);
	virtual __fastcall ~SignalListDef(void);
	void SetCrossCycle(bool _v);
	void SetLinearCycle(bool _v);
	void SetInvA(bool _v);
	void SetAlarm(bool _on);
	void CatchClear(void);
	void CatchStart(void);
	void CatchStop(void);
	void CatchReport(void);
	SignalEvent* CatchGetNext(void);

	CSignal* iCC;
	CSignal* iTCYCLE;
	CSignal* iCCYCLE;
	CSignal* iSTROBE;
	CSignal* iREADY;
	CSignal* iTCONTROL;
	CSignal* iCCONTROL;
	CSignal* oTPCHPOW;
	CSignal* oTSCANPOW;
	CSignal* oTWORK;
	CSignal* oCWORK;
	CSignal* oSHIFT;
	CSignal* oSTROBE;
	CSignal* oRESULT;
};

extern SignalListDef* SLD;
#endif
