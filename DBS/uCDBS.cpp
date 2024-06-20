// ------------------------------------------------------------------------------
#pragma hdrstop
#include "uCDBS.h"
#include <Forms.hpp>
// ------------------------------------------------------------------------------
#pragma package(smart_init)

// ------------------------------------------------------------------------------
CDBS::CDBS(void)
{
	need_delete = true;
	Init(ChangeFileExt(Application->ExeName, ".udl"));
}

// ------------------------------------------------------------------------------
CDBS::CDBS(AnsiString _ConnectString)
{
	need_delete = true;
	Init(_ConnectString);
}

CDBS::CDBS(TADOConnection* _ADOConnection)
{
	ADOConnection = _ADOConnection;
	need_delete = false;
}

// ------------------------------------------------------------------------------
CDBS::~CDBS(void)
{
	if(need_delete)
		delete ADOConnection;
}

// ------------------------------------------------------------------------------
void CDBS::Init(AnsiString _ConnectString)
{
	ADOConnection = new TADOConnection(NULL);
	ADOConnection->CommandTimeout = 30;
	ADOConnection->Connected = false;
	ADOConnection->ConnectionTimeout = 15;
	ADOConnection->ConnectOptions = coConnectUnspecified;
	ADOConnection->CursorLocation = clUseClient;
	ADOConnection->IsolationLevel = ilCursorStability;
	ADOConnection->KeepConnection = true;
	ADOConnection->LoginPrompt = false;
	ADOConnection->Mode = cmUnknown;
	ADOConnection->Tag = 0;
	AnsiString a = "FILE NAME=";
	a += _ConnectString;
	ADOConnection->ConnectionString = a;
	try
	{
		ADOConnection->Open();

	}
	catch (...)
	{
		ErrMsg = "Нет соединения с СУБД, файл: ";
		ErrMsg += _ConnectString;
		return;
	}
	if (ADOConnection->Connected == true)
		ErrMsg = "Ok";
	else
	{
		ErrMsg = "Нет соединения с СУБД, файл: ";
		ErrMsg += _ConnectString;
	}
}
// ------------------------------------------------------------------------------
CDBS* DBS = NULL;
