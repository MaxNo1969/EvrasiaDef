#pragma hdrstop
#include "JCollectTTL.h"
#include "Protocol.h"
#include "uFunctions.h"
#include "CatchTTL.h"
#pragma package(smart_init)
// ---------------------------------------------------------------------------
JCollectTTL::JCollectTTL(void)
{
	Init();
}

// ---------------------------------------------------------------------------
JCollectTTL::~JCollectTTL(void)
{
}

// ---------------------------------------------------------------------------
void JCollectTTL::Init(void)
{
	started = false;
	error = false;
	LastExec = GetTickCount();
	LoadSettings();
}

// ---------------------------------------------------------------------------
void JCollectTTL::LoadSettings(void)
{
	TPr::pr("JCollectTTL::LoadSettings");
	ReadPeriod = (DWORD)PA("Defect.L502.ReadPeriod").Int();
	lcardPars.LoadSettings();
}

// ---------------------------------------------------------------------------
void JCollectTTL::Start(void)
{
	if (started)
		Stop(GetTickCount());
	LCardChGroup current;
	current.Add(lcardPars.Cross);
	DWORD tick = GetTickCount();
	lcard.Start(&(lcardPars.board), &current);
	CatchTTL::Start(tick, lcard.GetTTLFrequencyHz());
	started = true;
}

// ---------------------------------------------------------------------------
void JCollectTTL::Stop(DWORD _tick)
{
	if (!started)
		return;
	started = false;
	Exec(_tick);
	lcard.Stop();
}

// ---------------------------------------------------------------------------
bool JCollectTTL::Exec(DWORD _tick)
{
	if (!started)
		return (false);
	if (_tick - LastExec < ReadPeriod)
		return (false);
	LastExec = _tick;
	LCard502::RBuf rbuf = lcard.Read();
	if (!rbuf.Ok)
	{
		error = true;
		return (false);
	}
	CatchTTL::Add(rbuf.TTL_buf, rbuf.TTL_size);
	return (true);
}

void JCollectTTL::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("JCollectTTL: ") + _msg);
}

