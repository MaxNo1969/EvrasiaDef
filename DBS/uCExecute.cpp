// ------------------------------------------------------------------------------
#pragma hdrstop
#include "uCExecute.h"
// ------------------------------------------------------------------------------
#pragma package(smart_init)
// ------------------------------------------------------------------------------
CExecute::CExecute(CDBS* _DBS,AnsiString _SQL)
{
	Init(_DBS,_SQL);
}
// ------------------------------------------------------------------------------
CExecute::CExecute(AnsiString _SQL)
{
	Init(DBS,_SQL);
}
// ------------------------------------------------------------------------------
void CExecute::Init(CDBS* _DBS,AnsiString _SQL)
{
	RetMsg="Ok";
	SP=new TADOStoredProc(NULL);
	SP->Connection=_DBS->Connection();
	SP->ProcedureName=_SQL;
	TParameter* P=SP->Parameters->AddParameter();
	WideString w="@RC";
	P->Name=w;
	P->DataType=ftInteger;
	P->Direction=pdReturnValue;
	P->Value=0;
}
// ------------------------------------------------------------------------------
CExecute::~CExecute(void)
{
	delete SP;
}
// ------------------------------------------------------------------------------
void CExecute::InputString(AnsiString _name,AnsiString _value)
{
	TParameter* P;
	WideString w;
	w=_name;
	P=SP->Parameters->FindParam(w);
	if(P==NULL)
	{
		P=SP->Parameters->AddParameter();
		P->Name=w;
	}
	P->DataType=ftString;
	P->Direction=pdInput;

	if(_value.Length()!=0)
	{
		w=_value;
		P->Value=w;
	}
	else
		P->Value=Null;
}
// ------------------------------------------------------------------------------
void CExecute::OutputString(AnsiString _name)
{
	TParameter* P;
	WideString w;
	w=_name;
	P=SP->Parameters->FindParam(w);
	if(P==NULL)
	{
		P=SP->Parameters->AddParameter();
		P->Name=w;
	}
	P->DataType=ftString;
	P->Direction=pdOutput;
	P->Value=Null;
}
// ------------------------------------------------------------------------------
void CExecute::InputInt(AnsiString _name,int _value)
{
	TParameter* P;
	WideString w;
	w=_name;
	P=SP->Parameters->FindParam(w);
	if(P==NULL)
	{
		P=SP->Parameters->AddParameter();
		P->Name=w;
	}
	P->DataType=ftInteger;
	P->Direction=pdInput;
	P->Value=_value;
}
// ------------------------------------------------------------------------------
void CExecute::OutputDouble(AnsiString _name)
{
	TParameter* P;
	WideString w;
	w=_name;
	P=SP->Parameters->FindParam(w);
	if(P==NULL)
	{
		P=SP->Parameters->AddParameter();
		P->Name=w;
	}
	P->DataType=ftFloat;
	P->Direction=pdOutput;
	P->Value=Null;
}
// ------------------------------------------------------------------------------
void CExecute::OutputInt(AnsiString _name)
{
	TParameter* P;
	WideString w;
	w=_name;
	P=SP->Parameters->FindParam(w);
	if(P==NULL)
	{
		P=SP->Parameters->AddParameter();
		P->Name=w;
	}
	P->DataType=ftInteger;
	P->Direction=pdOutput;
	P->Value=Null;
}
// ------------------------------------------------------------------------------
int CExecute::Exec(void)
{
	SP->ExecProc();
	WideString w="@RC";
	TParameter* P=SP->Parameters->FindParam(w);
	if(P->Value.IsNull())
		return(0);
	else
		return (P->Value);
}
// ------------------------------------------------------------------------------
long CExecute::AsLong(AnsiString _name)
{
	WideString w=_name;
	TParameter* P=SP->Parameters->FindParam(w);
	if(P==NULL)
	{
		RetMsg="CExecSQL::AsLong: Ошибка: параметр не найден";
		return (0);
	}
	if(P->Value.IsNull())
		return(0);
	else
		return (P->Value);
}
// ------------------------------------------------------------------------------
AnsiString CExecute::AsString(AnsiString _name)
{
	WideString w=_name;
	TParameter* P=SP->Parameters->FindParam(w);
	if(P==NULL)
	{
		RetMsg="CExecSQL::AsString: Ошибка: параметр не найден";
		return ("");
	}
	if(P->Value.IsNull())
		return("");
	else
		return (P->Value);
}
// ------------------------------------------------------------------------------
double CExecute::AsDouble(AnsiString _name)
{
	WideString w=_name;
	TParameter* P=SP->Parameters->FindParam(w);
	if(P==NULL)
	{
		RetMsg="CExecSQL::AsString: Ошибка: параметр не найден";
		return (0);
	}
	if(P->Value.IsNull())
		return(0);
	else
		return (P->Value);
}
// ------------------------------------------------------------------------------
int CExecute::AsInt(AnsiString _name)
{
	WideString w=_name;
	TParameter* P=SP->Parameters->FindParam(w);
	if(P==NULL)
	{
		RetMsg="CExecSQL::AsString: Ошибка: параметр не найден";
		return (0);
	}
	if(P->Value.IsNull())
		return(0);
	else
		return (P->Value);
}
// ------------------------------------------------------------------------------
void CExecute::InputLong(AnsiString _name,int _value)
{
	TParameter* P;
	WideString w;
	w=_name;
	P=SP->Parameters->FindParam(w);
	if(P==NULL)
	{
		P=SP->Parameters->AddParameter();
		P->Name=w;
	}
	P->DataType=ftLargeint;
	P->Direction=pdInput;
	P->Value=_value;
}
// ------------------------------------------------------------------------------
void CExecute::OutputLong(AnsiString _name)
{
	TParameter* P;
	WideString w;
	w=_name;
	P=SP->Parameters->FindParam(w);
	if(P==NULL)
	{
		P=SP->Parameters->AddParameter();
		P->Name=w;
	}
	P->DataType=ftLargeint;
	P->Direction=pdOutput;
	P->Value=Null;
}
// ------------------------------------------------------------------------------

