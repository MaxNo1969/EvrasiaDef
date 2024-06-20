// ---------------------------------------------------------------------------
#pragma hdrstop
#include "uCInv.h"
#ifndef NOCOMPORTS
#include "uCCOMPort_real.h"
#else
#include "uCCOMPort_pseudo.h"
#endif
#include "uCExchange.h"
#include "uFunctions.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

CInv::State::State()
{
	oSTF = false;
	oSTR = false;
	oRL = false;
	oRM = false;
	oRH = false;
	oRT = false;
	oMRS = false;
	error = false;
	SetI(0);
}

void CInv::State::SetI(byte _v)
{
	iRUN = _v & (1 << 0);
	iSTF = _v & (1 << 1);
	iSTR = _v & (1 << 2);
	iSU = _v & (1 << 3);
	iOL = _v & (1 << 4);
	iFU = _v & (1 << 6);
	iABC = _v & (1 << 7);
}

byte CInv::State::Get(void)
{
	byte ret = 0;
	if (oSTF)
		ret |= (1 << 1);
	if (oSTR)
		ret |= (1 << 2);
	if (oRL)
		ret |= (1 << 3);
	if (oRM)
		ret |= (1 << 4);
	if (oRH)
		ret |= (1 << 5);
	if (oRT)
		ret |= (1 << 6);
	if (oMRS)
		ret |= (1 << 7);
	return (ret);
}

void CInv::State::CopyO(State* _src, State* _dst)
{
	_dst->oSTF = _src->oSTF;
	_dst->oSTR = _src->oSTR;
	_dst->oRL = _src->oRL;
	_dst->oRM = _src->oRM;
	_dst->oRH = _src->oRH;
	_dst->oRT = _src->oRT;
	_dst->oMRS = _src->oMRS;
}
AnsiString CInv::State::Tostring(void)
{
	AnsiString ret="";
	ret+=" RUN=";
	ret+=iRUN?"1":"0";
	ret+=" STF=";
	ret+=iSTF?"1":"0";
	ret+=" STR=";
	ret+=iSTR?"1":"0";
	ret+=" SU=";
	ret+=iSU?"1":"0";
	ret+=" OL=";
	ret+=iOL?"1":"0";
	ret+=" FU=";
	ret+=iFU?"1":"0";
	ret+=" ABC=";
	ret+=iABC?"1":"0";
	return(ret);
}


// ==============================================================================
CInv::CInv(PA _pa)
{
	timeout = 1;
	comport = NULL;
	OnProtocolL = NULL;

	// iRUN = false;
	// iSTF = false;
	// iSTR = false;
	// iSU = false;
	// iOL = false;
	// iFU = false;
	// iABC = false;
	//
	// oSTF = false;
	// oSTR = false;
	// oRL = false;
	// oRM = false;
	// oRH = false;
	// oRT = false;
	// oMRS = false;
	max_iters = 1;
	cs = new TCriticalSection();
	if (comport != NULL)
		delete comport;
	AnsiString error_msg;
#ifndef NOCOMPORTS
	comport = CCOMPort_real::Create(_pa, &error_msg);
#else
	comport = CCOMPort_pseudo::Create();
#endif
	if (comport == NULL)
	{
		pr(-1, error_msg);
		AnsiString a = "Open: не могу открыть COM порт";
		pr(-1, a);
		FATAL(a);
	}
	comport->OnProtocol = OnProtocolL;
	timeout = _pa.Item("Timeout").Int();
}

CInv::~CInv()
{
	delete comport;
	delete cs;
}

void CInv::FOnProtocolWrite(OnProtocolDef _v)
{
	OnProtocolL = _v;
	if (comport != NULL)
		comport->OnProtocol = OnProtocolL;
}

CInv::State CInv::StateRead0(int _abonent)
{
	AnsiString reply;
	AnsiString reply_data;
	AnsiString H0 = "0x";
	pr(_abonent, "StateRead");
	if (!Exec(_abonent, "7A", "B", "", "E1", 0, "D", 0, "", 0, &reply,
		&reply_data))
	{
		pr(_abonent, "StateRead: нет ответа");
		CurrentState.error = true;
		return (CurrentState);
	}
	if (reply != "E1")
	{
		error_msg += "Ответ ";
		error_msg += reply;
		error_msg += ": ";
		error_msg += reply_data;
		error_msg += " , а должен быть E1";
		pr(_abonent, error_msg);
		CurrentState.error = true;
		return (CurrentState);
	}
	CurrentState.error = false;
	CurrentState.SetI((byte)StrToInt(H0 + reply_data));
	return (CurrentState);
}

bool CInv::StateWrite0(int _abonent, State _state)
{
	pr(_abonent, "StateWrite");
	State::CopyO(&_state,&CurrentState);
	byte state = CurrentState.Get();
	AnsiString reply;
	AnsiString reply_data;
	AnsiString av;
	av = AnsiString::IntToHex(state, 2);
	if (!Exec(_abonent, "FA", "A1", av, "C", 0, "D", 0, "", 0, &reply,
		&reply_data))
	{
		pr(_abonent, "StateWrite: нет ответа");
		return (false);
	}
	if (reply != "C")
	{
		error_msg = "StateWrite: Ответ ";
		error_msg += reply;
		error_msg += " , а должен быть C, ";
		error_msg += reply_data;
		pr(_abonent, error_msg);
		return (false);
	}
	return (true);
}

bool CInv::Exec(int _abonent, AnsiString _code, AnsiString _request,
	AnsiString _request_data, AnsiString _reply0, int _reply0_size,
	AnsiString _reply1, int _reply1_size, AnsiString _reply2, int _reply2_size,
	AnsiString * _reply, AnsiString * _reply_data)
{
	if (comport == NULL)
	{
		error_msg = "CInv::Exec: Не открыт COM порт";
		return (false);
	}
	CExchange* ex = new CExchange(_abonent, timeout);
	CRequest* req = ex->SetRequest(_request, _code);
	req->Data(_request_data);
	if (_reply0.Length() != 0)
		ex->AddReply(_reply0)->SetDataSize(_reply0_size);
	if (_reply1.Length() != 0)
		ex->AddReply(_reply1)->SetDataSize(_reply1_size);
	if (_reply2.Length() != 0)
		ex->AddReply(_reply2)->SetDataSize(_reply2_size);
	bool ret = ex->Exec(comport, _reply, _reply_data, max_iters);
	error_msg = "";
	if (!ret)
		error_msg = *_reply_data;
	delete ex;
	return (ret);
}

bool CInv::SetFrequency0(int _abonent, AnsiString _cmd, int _frequency)
{
	pr(_abonent, "SetFrequency");
	AnsiString reply;
	AnsiString reply_data;
	AnsiString av = AnsiString::IntToHex(_frequency, 4);
	if (!Exec(_abonent, _cmd, "A", av, "C", 0, "D", 0, "", 0, &reply,
		&reply_data))
	{
		pr(_abonent, "SetFrequency: нет ответа");
		return (false);
	}
	if (reply != "C")
	{
		error_msg = "SetFrequency: Ответ ";
		error_msg += reply;
		error_msg += " , а должен быть C ;";
		error_msg += reply_data;
		pr(_abonent, error_msg);
		return (false);
	}
	return (true);
}

int CInv::GetFrequency0(int _abonent, AnsiString _cmd)
{
	pr(_abonent, "GetFrequency");
	AnsiString reply;
	AnsiString reply_data;
	if (!Exec(_abonent, _cmd, "B", "", "E", 0, "D", 0, "", 0, &reply,
		&reply_data))
	{
		pr(_abonent, "GetFrequency: нет ответа");
		return (-1);
	}
	if (reply != "E")
	{
		error_msg = "GetFrequency: Ответ ";
		error_msg += reply;
		error_msg += " , а должен быть E";
		pr(_abonent, error_msg);
		return (-1);
	}
	AnsiString H0 = "0x";
	return (StrToInt(H0 + reply_data));
}

bool CInv::SetMode0(int _abonent, int _mode)
{
	pr(_abonent, "SetMode");
	AnsiString reply;
	AnsiString reply_data;
	AnsiString av = AnsiString::IntToHex(_mode, 4);
	if (!Exec(_abonent, "FB", "A", av, "C", 0, "D", 0, "", 0, &reply,
		&reply_data))
	{
		pr(_abonent, "SetMode: нет ответа");
		return (false);
	}
	if (reply != "C")
	{
		error_msg = "SetMode: Ответ ";
		error_msg += reply;
		error_msg += ": ";
		error_msg += reply_data;
		error_msg += " , а должен быть C";
		pr(_abonent, error_msg);
		return (false);
	}
	return (true);
}

int CInv::GetMode(int _abonent)
{
	pr(_abonent, "GetMode");
	AnsiString reply;
	AnsiString reply_data;
	if (!Exec(_abonent, "7B", "B", "", "E", 0, "D", 0, "", 0, &reply,
		&reply_data))
	{
		pr(_abonent, "GetMode: нет ответа");
		return (false);
	}
	if (reply != "E")
	{
		error_msg = "GetMode: Ответ ";
		error_msg += reply;
		error_msg += ": ";
		error_msg += reply_data;
		error_msg += " , а должен быть E";
		pr(_abonent, error_msg);
		return (-1);
	}
	AnsiString H0 = "0x";
	return (StrToInt(H0 + reply_data));
}

bool CInv::Reset9696(int _abonent)
{
	pr(_abonent, "Reset9696");
	AnsiString reply;
	AnsiString reply_data;
	if (!Exec(_abonent, "FD", "A", "9696", "C", 0, "D", 0, "", 0, &reply,
		&reply_data))
	{
		pr(_abonent, "Reset9696: нет ответа");
		return (false);
	}
	if (reply != "C")
	{
		error_msg = "Reset9696: Ответ ";
		error_msg += reply;
		error_msg += ": ";
		error_msg += reply_data;
		error_msg += " , а должен быть C";
		pr(_abonent, error_msg);
		return (false);
	}
	return (true);
}

bool CInv::Reset99660(int _abonent)
{
	pr(_abonent, "Reset9966");
	AnsiString reply;
	AnsiString reply_data;
	if (!Exec(_abonent, "FD", "A", "9966", "C", 0, "D", 0, "", 0, &reply,
		&reply_data))
	{
		pr(_abonent, "Reset9966: нет ответа");
		return (false);
	}
	if (reply != "C")
	{
		error_msg = "Reset9966: Ответ ";
		error_msg += reply;
		error_msg += ": ";
		error_msg += reply_data;
		error_msg += " , а должен быть C";
		pr(_abonent, error_msg);
		return (false);
	}
	return (true);
}

void CInv::pr(int _abonent, AnsiString _msg)
{
	if (OnProtocolL == NULL)
		return;
	AnsiString a = "CInv[";
	a += _abonent;
	a += "]: ";
	a += _msg;

	OnProtocolL(a);
}

CInv::State CInv::StateRead(int _abonent)
{
	State ret;
	cs->Enter();
	ret = StateRead0(_abonent);
	cs->Leave();
	return (ret);
}

bool CInv::StateWrite(int _abonent, State _state)
{
	bool ret;
	cs->Enter();
	ret = StateWrite0(_abonent, _state);
	cs->Leave();
	return (ret);
}

int CInv::GetFrequency(int _abonent, AnsiString _cmd)
{
	int ret;
	cs->Enter();
	ret = GetFrequency0(_abonent, _cmd);
	cs->Leave();
	return (ret);

}

bool CInv::SetFrequency(int _abonent, AnsiString _cmd, int _frequency)
{
	bool ret;
	cs->Enter();
	ret = SetFrequency0(_abonent, _cmd, _frequency);
	cs->Leave();
	return (ret);
}

bool CInv::SetMode(int _abonent, int _mode)
{
	bool ret;
	cs->Enter();
	ret = SetMode0(_abonent, _mode);
	cs->Leave();
	return (ret);
}

bool CInv::Reset9966(int _abonent)
{
	bool ret;
	cs->Enter();
	ret = Reset99660(_abonent);
	cs->Leave();
	return (ret);

}

AnsiString CInv::GetErrorMsg(void)
{
	AnsiString ret;
	cs->Enter();
	ret = error_msg;
	ret.Unique();
	cs->Leave();
	return (ret);
}

CInv::State CInv::GetCurrentState(void)
{
	State ret;
	cs->Enter();
	ret = CurrentState;
	cs->Leave();
	return (ret);
}
