#pragma hdrstop
#include "ThBase.h"
#include "uFunctions.h"
#include "protocol.h"
#include "SMSM.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall ThBase::ThBase(AnsiString _name)
{
	name = _name;
}
// ---------------------------------------------------------------------------
__fastcall ThBase::~ThBase(void)
{
	Terminate();
	WaitFor();
}

// ---------------------------------------------------------------------------
void ThBase::pr(AnsiString _msg)
{
	TPr::pr(name + ": " + _msg);
}

// ---------------------------------------------------------------------------
void ThBase::PostStatus1(AnsiString _msg)
{
	SMSM::SetPost("STATUS1",_msg);
}

// ---------------------------------------------------------------------------
void ThBase::PostStatus2(AnsiString _msg)
{
	SMSM::SetPost("STATUS2",_msg);
}
// ---------------------------------------------------------------------------
void ThBase::PPR(AnsiString _msg)
{
	pr(_msg);
	PostStatus2(_msg);
}


