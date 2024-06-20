//---------------------------------------------------------------------------
#pragma hdrstop
#include "Protocol.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TPr* TPr::Instance = NULL;

TPr::TPr()
{
	cs = new TCriticalSection();
	FProtocol = new TFProtocol(NULL, cs);
	//FProtocol = new TFProtocol(MainForm,cs);
}

TPr::~TPr()
{
	FProtocol->Save();
	delete FProtocol;
	delete cs;
}

void TPr::pr(AnsiString _msg)
{
	if (Instance == NULL)
		Instance = new TPr();
	Instance->cs->Enter();
	{
		Instance->FProtocol->Add(_msg);
	} Instance->cs->Leave();
}

void TPr::Clear(void)
{
	if (Instance != NULL)
	{
		Instance->cs->Enter();
		{
			Instance->FProtocol->mProtocol->Clear();
			Instance->FProtocol->mProtocol->Lines->Clear();
		} Instance->cs->Leave();
	}
}

void TPr::Dispose(void)
{
	if (Instance != NULL)
	{
		delete Instance;
		Instance = NULL;
	}
}

void TPr::Show(void)
{
	if (Instance == NULL)
		Instance = new TPr();
	Instance->cs->Enter();
	{
		Instance->FProtocol->Show();
	} Instance->cs->Leave();
}

void TPr::DateTimeMark(AnsiString _msg)
{
	if (Instance == NULL)
		Instance = new TPr();
	Instance->cs->Enter();
	{
		Instance->FProtocol->DateTimeMark(_msg);
	} Instance->cs->Leave();
}

void TPr::DateTimeMark(void)
{
	if (Instance == NULL)
		Instance = new TPr();
	Instance->cs->Enter();
	{
		Instance->FProtocol->DateTimeMark();
	} Instance->cs->Leave();
}
