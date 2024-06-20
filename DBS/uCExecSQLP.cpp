// ---------------------------------------------------------------------------
#pragma hdrstop
#include "uCExecSQLP.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ------------------------------------------------------------------------------
CExecSQLP::CExecSQLP(CDBS* _DBS, AnsiString _SQL)
{
	Init(_DBS, _SQL);
}

// ------------------------------------------------------------------------------
CExecSQLP::CExecSQLP(AnsiString _SQL)
{
	Init(DBS, _SQL);
}

// ------------------------------------------------------------------------------
CExecSQLP::~CExecSQLP()
{
	Q->Active = false;
	delete Q;
}

// ------------------------------------------------------------------------------
void CExecSQLP::Init(CDBS* _DBS, AnsiString _SQL)
{
	SQL=_SQL;
	Q = new TADOQuery(NULL);
	Q->Connection = _DBS->Connection();
	Q->SQL->Add(SQL);
	WideString w=SQL;
	Q->Parameters->Clear();
	Q->Parameters->ParseSQL(w,true);
}

// ------------------------------------------------------------------------------
void CExecSQLP::InputString(AnsiString _name, AnsiString _value)
{
	WideString w;
	w = _name;
	TParameter* P=Q->Parameters->ParamByName(w);
	P->DataType = ftString;
	P->Direction = pdInput;
	if (_value.Length() != 0)
	{
		w = _value;
		P->Value = w;
	}
	else
		P->Value = Null;
}

// ------------------------------------------------------------------------------
AnsiString CExecSQLP::Exec(void)
{
	AnsiString RetMsg = "Ok";
	try
	{
		Q->ExecSQL();
	}
	catch (Exception &ex)
	{
		RetMsg = "Ошибка: ";
		RetMsg += SQL;
		RetMsg += " ";
		RetMsg += ex.Message;
	}
	catch (...)
	{
		RetMsg = "Ошибка: ";
		RetMsg += SQL;
	}
	return(RetMsg);
}
// ------------------------------------------------------------------------------
