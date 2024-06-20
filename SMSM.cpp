#pragma hdrstop
#include "SMSM.h"
#include "uFunctions.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
SMSM::SMSM(void)
{
	main_handle = (HWND)0;
	cs = new TCriticalSection();
	MsgId = RegisterWindowMessage(L"SMSM");
	if (MsgId == 0)
		FATAL("SMSM::SMSM: не могу зарегистрировать сообщение");
	Asc.reserve(100);
	Ans.reserve(100);
};

// ---------------------------------------------------------------------------
SMSM::~SMSM(void)
{
	delete cs;
};

// ---------------------------------------------------------------------------
void SMSM::Dispose(void)
{
	if (Instance != NULL)
		delete Instance;
}

// ---------------------------------------------------------------------------
void SMSM::Init(HWND _main_handle)
{
	if (Instance == NULL)
		Instance = new SMSM();
	Instance->cs->Enter();
	Instance->main_handle = _main_handle;
	Instance->cs->Leave();
}

// ---------------------------------------------------------------------------
UINT SMSM::GetMsgId(void)
{
	if (Instance == NULL)
		Instance = new SMSM();
	UINT ret;
	Instance->cs->Enter();
	ret = Instance->MsgId;
	Instance->cs->Leave();
	return (ret);
}

// ---------------------------------------------------------------------------
void SMSM::SetPost(AnsiString _msg, AnsiString _name)
{
	if (Instance == NULL)
		Instance = new SMSM();

	Instance->cs->Enter();

	Msg m;
	m.msg = _msg;
	m.name = _name;
	Instance->Asc.push_back(m);
	if (Instance->main_handle != (HWND)0)
	{
		if (PostMessage(Instance->main_handle, Instance->MsgId, 0, 0) == 0)
			FATAL("ThBase::Post: не могу послать сообщение");
	}

	Instance->cs->Leave();
}
// ---------------------------------------------------------------------------
void SMSM::SetPost(AnsiString _msg)
{
	SetPost(_msg, "?");
}

// ---------------------------------------------------------------------------
AnsiString SMSM::GetPost(AnsiString* _name, bool* _Ok)
{
	*_Ok = false;
	if (Instance == NULL)
		Instance = new SMSM();
	AnsiString ret;

	Instance->cs->Enter();

	for (vector<Msg>::iterator it = Instance->Asc.begin();
	it != Instance->Asc.end(); it++)
	{
		*_Ok = true;
		ret = it->msg;
		*_name = it->name;
		Instance->Asc.erase(it);
		break;
	}

	Instance->cs->Leave();
	return (ret);
}

// ---------------------------------------------------------------------------
void SMSM::SetAnswer(AnsiString _msg, AnsiString _name)
{
	if (Instance == NULL)
		Instance = new SMSM();
	Instance->cs->Enter();

	Msg m;
	m.msg = _msg;
	m.name = _name;
	Instance->Ans.push_back(m);

	Instance->cs->Leave();
}

// ---------------------------------------------------------------------------
AnsiString SMSM::GetAnswer(AnsiString _name, bool* _Ok)
{
	if (Instance == NULL)
		Instance = new SMSM();
	AnsiString ret;

	Instance->cs->Enter();

	*_Ok = false;
	for (vector<Msg>::iterator it = Instance->Ans.begin();
	it != Instance->Ans.end(); it++)
	{
		if (it->name == _name)
		{
			*_Ok = true;
			ret = it->msg;
			Instance->Ans.erase(it);
			break;
		}
	}

	Instance->cs->Leave();

	return (ret);
}

// ---------------------------------------------------------------------------
