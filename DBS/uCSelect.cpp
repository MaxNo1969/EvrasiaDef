//------------------------------------------------------------------------------
#pragma hdrstop
#include "uCSelect.h"
#include "uFunctions.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
CSelect::CSelect(CDBS* _DBS, AnsiString _SQL, bool _no_par)
{
	no_par = _no_par;
	Init(_DBS, _SQL);
	if(no_par)
		Exec();
}

//------------------------------------------------------------------------------
CSelect::CSelect(AnsiString _SQL, bool _no_par)
{
	no_par = _no_par;
	Init(DBS, _SQL);
	if(no_par)
		Exec();
}

//------------------------------------------------------------------------------
void CSelect::Init(CDBS* _DBS, AnsiString _SQL)
{
	Q = new TADOQuery(NULL);
	Q->Connection = _DBS->Connection();
	Q->SQL->Add(_SQL);
}

//------------------------------------------------------------------------------
AnsiString CSelect::Exec(void)
{
	RetMsg = "Ok";
	try
	{
		Q->Active = true;
		Q->First();
	}
	catch (Exception &ex)
	{
		RetMsg = "Îøèáêà: ";
		RetMsg += Q->SQL->Text;
		RetMsg += " ";
		RetMsg += ex.Message;
	}
	catch (...)
	{
		RetMsg = "Îøèáêà: ";
		RetMsg += Q->SQL->Text;
	}
	return(RetMsg);
}
//------------------------------------------------------------------------------
void CSelect::InputString(AnsiString _name, AnsiString _value)
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

//------------------------------------------------------------------------------
CSelect::~CSelect()
{
	delete Q;
}

//------------------------------------------------------------------------------
int CSelect::Count(void)
{
	if (RetMsg != "Ok")
		return (0);
	return (Q->RecordCount);
};

//------------------------------------------------------------------------------
AnsiString CSelect::AsAnsiString(AnsiString _name)
{
	if (RetMsg != "Ok")
		return (NULL);
	return (Q->FieldByName(_name)->AsString);
};

//------------------------------------------------------------------------------
bool CSelect::AsBool(AnsiString _name)
{
	if (RetMsg != "Ok")
		return (false);
	return (Q->FieldByName(_name)->AsBoolean);
};

//------------------------------------------------------------------------------
int CSelect::AsInt(AnsiString _name)
{
	if (RetMsg != "Ok")
		return (0);
	return (Q->FieldByName(_name)->AsInteger);
};

//------------------------------------------------------------------------------
double CSelect::AsDouble(AnsiString _name)
{
	if (RetMsg != "Ok")
		return (0);
	return ((Q->FieldByName(_name)->AsFloat));
};

//------------------------------------------------------------------------------
char CSelect::AsChar(AnsiString _name)
{
	AnsiString ret = AsAnsiString(_name);
	if (ret.Length() == 0)
		return ('-');
	return (*(ret.c_str()));
}

//------------------------------------------------------------------------------
__int64 CSelect::AsInt64(AnsiString _name)
{
	if (RetMsg != "Ok")
		return (0);
	return (((TLargeintField*)Q->FieldByName(_name))->AsLargeInt);
};

//------------------------------------------------------------------------------
void CSelect::Next(void)
{
	if (RetMsg != "Ok")
		return;
	Q->Next();
};

//------------------------------------------------------------------------------
bool CSelect::Eof(void)
{
	if (RetMsg != "Ok")
		return (true);
	return (Q->Eof);
}
//------------------------------------------------------------------------------
