#pragma hdrstop
#include "JCollect502.h"
#include "Protocol.h"
#include "uFunctions.h"
#include "CatchTTL.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
JCollect502::JCollect502(Bank* _bank, IsWork _IW)
{
	Init(_bank, _IW);
}

// ---------------------------------------------------------------------------
JCollect502::JCollect502(void)
{
	Init(NULL, IsWork(IW));
}

// ---------------------------------------------------------------------------
JCollect502::~JCollect502(void)
{
}

// ---------------------------------------------------------------------------
void JCollect502::Init(Bank* _bank, IsWork _IW)
{
	bank = _bank;
	IW = _IW;
	started = false;
	error = false;
	LastExec = GetTickCount();
	LoadSettings();
}

// ---------------------------------------------------------------------------
void JCollect502::LoadSettings(void)
{
	TPr::pr("JCollect502::LoadSettings");
	ReadPeriod = (DWORD)PA("Defect.L502.ReadPeriod").Int();
	lcardPars.LoadSettings();
}

// ---------------------------------------------------------------------------
void JCollect502::Start(void)
{
	if (bank == NULL)
		return;
	if (started)
		Stop(GetTickCount());
	LCardChGroup current;
	if (IW.Cross)
		current.Add(lcardPars.Cross);
	if (IW.Line)
		current.Add(lcardPars.Line);
	if (IW.SG)
		current.Add(lcardPars.SG);
	DWORD tick = GetTickCount();
	lcard.Start(&(lcardPars.board), &current);
#ifdef TTL_SIGNALS
	CatchTTL::Start(tick, lcard.GetTTLFrequencyHz());
#endif
	bank->FirstTickGroup(GetTickCount());
	started = true;
}

// ---------------------------------------------------------------------------
void JCollect502::Stop(DWORD _tick)
{
	if (bank == NULL)
		return;
	if (!started)
		return;
	started = false;
	Exec(_tick);
	lcard.Stop();
}

// ---------------------------------------------------------------------------
bool JCollect502::Exec(DWORD _tick)
{
	if (bank == NULL)
		return (false);
	if (!started)
		return (false);
	if (_tick - LastExec < ReadPeriod)
		return (false);
	LastExec = _tick;
#ifdef TTL_SIGNALS
	LCard502::RBuf rbuf = lcard.Read();
	if (!rbuf.Ok)
	{
		error = true;
		return (false);
	}
	bank->AddGroup(_tick, rbuf.ADC_buf, rbuf.ADC_size);
	CatchTTL::Add(rbuf.TTL_buf, rbuf.TTL_size);
#else
	int size;
//	pr(AnsiString("ExecTick=")+_tick);
	double* buf = lcard.Read(&size);
	if (size < 0)
	{
		error = true;
		return (false);
	}
	bank->AddGroup(_tick, buf, size);
#endif
	return (true);
}

// ---------------------------------------------------------------------------
double JCollect502::GetValueV(RChannel_parameters* _channel, bool* _ret)
{
	if (started)
		FATAL("JCollect502::Init: Нельзя получать значения стартовавшего сборщика");
	return (lcard.GetValueV(_channel, &(lcardPars.board), _ret));
}

// ---------------------------------------------------------------------------
double JCollect502::GetValueP(RChannel_parameters* _channel, bool* _ret)
{
	if (started)
		FATAL("JCollect502::Init: Нельзя полчать значения стартовавшего сборщика");
	return (lcard.GetValueP(_channel, &(lcardPars.board), _ret));
}
// ---------------------------------------------------------------------------
void JCollect502::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("JCollect502: ") + _msg);
}

