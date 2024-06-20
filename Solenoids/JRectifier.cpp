#pragma hdrstop
#include "JRectifier.h"
#include "PA.h"
#include "Math.h"
#include "Protocol.h"
#pragma package(smart_init)

// =====================================================================================================================
JRectifier::JRectifier() : Cross(&modBus, 'c'), Thick(&modBus, 't')
{
	CS1 = new TCriticalSection();
	CrossTh = NULL;
	ThickTh = NULL;
	modBus.OnProtocol = pr;
}

JRectifier::~JRectifier(void)
{
	Stop('c');
	Stop('t');
	delete CS1;
}

bool JRectifier::Start(char _tp)
{
	if (_tp == 'c')
	{
		if (Cross.state.started)
			return (true);
		if (!Cross.Start())
		{
			SetError(Cross.state.errorMsg);
			return (false);
		}
		if (CrossTh == NULL)
			CrossTh = new RectifierTh(this, _tp);
		return (true);
	}
	else
	{
		if (Thick.state.started)
			return (true);
		if (!Thick.Start())
		{
			SetError(Cross.state.errorMsg);
			return (false);
		}
		if (ThickTh == NULL)
			ThickTh = new RectifierTh(this, _tp);
		return (true);
	}
	return (true);
}

bool JRectifier::Stop(char _tp)
{
	if (_tp == 'c')
	{
		if (CrossTh != NULL)
			delete CrossTh;
		CrossTh = NULL;
		if (!Cross.state.started)
			return (true);
		return (Cross.Stop());
	}
	else
	{
		if (ThickTh != NULL)
			delete ThickTh;
		ThickTh = NULL;
		if (!Thick.state.started)
			return (true);
		return (Thick.Stop());
	}
	return (true);
}

char JRectifier::GetIU(char _tp)
{
	if (_tp == 'c')
		return (Cross.GetIU());
	else
		return (Thick.GetIU());
}


bool JRectifier::ExecTh(char _tp)
{
	bool ret;
	Rectifier::State lstate;

	if (_tp == 'c')
		lstate=Cross.Exec();
	else
		lstate=Thick.Exec();
	lstate.real=true;
	CS1->Enter();
	if (_tp == 'c')
		StateCross=lstate;
	else
		StateThick=lstate;
	ret=!lstate.error;
	CS1->Leave();
	return (ret);
}
Rectifier::State JRectifier::GetState(char _tp)
{
	Rectifier::State ret;
	CS1->Enter();
	if (_tp == 'c')
	{
		ret=StateCross;
		StateCross.real=false;
	}
	else
	{
		ret=StateThick;
		StateThick.real=false;
	}
	CS1->Leave();
	return(ret);
}
void JRectifier::Exec(void)
{
	Rectifier::State lstate=GetState('c');
	if(lstate.started)
	{
		if(lstate.real)
		{
//			pr(lstate.Tostring());
			lstate.real=false;
		}
		if(lstate.error)
			SetError(lstate.errorMsg);
		if(lstate.Overheat())
			SetError("Перегрев поперечного");
	}
	lstate=GetState('t');
	if(lstate.started)
	{
		if(lstate.real)
		{
//			pr(lstate.Tostring());
			lstate.real=false;
		}
		if(lstate.error)
			SetError(lstate.errorMsg);
		if(lstate.Overheat())
			SetError("Перегрев толщиномера");
	}
}

void JRectifier::pr(AnsiString _msg)
{
	TPr::pr(_msg);
}

// ================================================================================
__fastcall RectifierTh::RectifierTh(JRectifier* _jRectifier, char _tp)
{
	jRectifier = _jRectifier;
	tp = _tp;
}

void __fastcall RectifierTh::Execute()
{
	for (; ;)
	{
		if(!jRectifier->ExecTh(tp))
			break;
		if (Terminated)
			break;
		Sleep(500);
	}
}
