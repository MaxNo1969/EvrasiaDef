//---------------------------------------------------------------------------
#pragma hdrstop
#include "PA.h"
#include "PipeClient.h"
#include "uFunctions.h"
#include <ComObj.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

PA::PA()
{
	path = "";
}

PA::PA(AnsiString _path)
{
	path = _path;
}

PA PA::Item(AnsiString _path)
{
	AnsiString ipath = path;
	ipath += ".";
	ipath += _path;
	return (PA(ipath));
}

void PA::CheckError(AnsiString _cmd, AnsiString _result)
{
	if (_result.Pos("Ok") != 1)
		FATAL(AnsiString("PA::CheckError: не верная команда: ") + _cmd);
}
AnsiString PA::Val(AnsiString _cmd, AnsiString _result)
{
	CheckError(_cmd, _result);
	return(_result.Delete(1, 3));
}

bool PA::Bool()
{
	AnsiString cmd = AnsiString("Read;")+path;
	AnsiString result = Val(cmd,PipeClient::Command(cmd));
	return (result == "True");
}

int PA::Int()
{
	AnsiString cmd = AnsiString("Read;")+path;
	AnsiString result = Val(cmd,PipeClient::Command(cmd));
	int ret=0;
	try
	{
		ret=result.ToInt();
	}
	catch(Exception &e)
	{
		e.Message=cmd+" "+e.Message;
		throw(e);
	}
	return (ret);
}

float PA::Float()
{
	AnsiString cmd = AnsiString("Read;")+path;
	AnsiString result = Val(cmd,PipeClient::Command(cmd));
	return ((float)result.ToDouble());
}

double PA::Double()
{
	AnsiString cmd = AnsiString("Read;")+path;
	AnsiString result = Val(cmd,PipeClient::Command(cmd));
	return (result.ToDouble());
}

AnsiString PA::String()
{
	AnsiString cmd = AnsiString("Read;")+path;
	return (Val(cmd,PipeClient::Command(cmd)));
}

void PA::Write(Variant _val)
{
	AnsiString cmd = AnsiString("Write;")+path+";"+_val;
	CheckError(cmd, PipeClient::Command(cmd));
}
bool PA::Exist()
{
	AnsiString cmd = AnsiString("Exist;")+path;
	AnsiString result = Val(cmd,PipeClient::Command(cmd));
	return (result == "True");
}


AnsiString PA::ToString()
{
	return (path);
}

void PA::LoadFormPos(TForm * _form)
{
	AnsiString cmd = AnsiString("GetFormPos;")+path+";"+_form->Name;
	TStringList* L = new TStringList();
	L->StrictDelimiter = true;
	L->Delimiter = ',';
	L->DelimitedText = Val(cmd,PipeClient::Command(cmd));
//	int xxx=L->Count;
//	AnsiString a1=L->Strings[0];
//	AnsiString a2=L->Strings[1];
//	AnsiString a3=L->Strings[2];
//	AnsiString a4=L->Strings[3];
//	int _Left = L->Strings[0].ToInt();
//	int _Top = L->Strings[1].ToInt();
//	int _Width = L->Strings[2].ToInt();
//	int _Height = L->Strings[3].ToInt();

	_form->Left = L->Strings[0].ToInt();
	_form->Top = L->Strings[1].ToInt();
	_form->Width = L->Strings[2].ToInt();
	_form->Height = L->Strings[3].ToInt();
	delete L;
}

void PA::SaveFormPos(TForm * _form)
{
	AnsiString cmd = AnsiString("SetFormPos;")+path+";"+_form->Name+";";
	cmd+=_form->Left;
	cmd+=",";
	cmd+=_form->Top;
	cmd+=",";
	cmd+=_form->Width;
	cmd+=",";
	cmd+=_form->Height;
	CheckError(cmd, PipeClient::Command(cmd));
}

int PA::GetCount(void)
{
	AnsiString cmd = AnsiString("GetCount;")+path;
	return(Val(cmd,PipeClient::Command(cmd)).ToInt());
}

//bool PA::IsNull(void)
//{
//	Variant E = Val();
//	return (E.VDispatch == NULL);
//}

PA PA:: operator[](int _index)
{
	AnsiString pindex = path;
	pindex += "[";
	pindex += _index;
	pindex += "]";
	return (pindex);
}

PA PA:: operator[](AnsiString _name)
{
	AnsiString pindex = path;
	pindex += "[\"";
	pindex += _name;
	pindex += "\"]";
	return (pindex);
}

//bool PA::Exist(void)
//{
//	WideString w = path;
//	Variant var_path = w;
//	Variant E = ParametersCOM::Function("Exist", var_path);
//	if (varBoolean != E.Type())
//		throw(Exception("PA::Exist: некорректный тип"));
//	return (E.VBoolean != 0);
//}
void PA::Dispose(void)
{
	PipeClient::Dispose();
}
bool PA::GetSignal(AnsiString _name)
{
	AnsiString cmd = AnsiString("GetSignal;")+_name;
	AnsiString result = Val(cmd,PipeClient::Command(cmd));
	return (result == "True");
}
void PA::SetSignal(AnsiString _name,bool _val)
{
	AnsiString cmd = AnsiString("SetSignal;")+_name+";"+(_val?"True":"False");
	Val(cmd,PipeClient::Command(cmd));
}
DWORD PA::RemoteGetTickCount(void)
{
	AnsiString cmd = "GetTickCount";
	AnsiString result = Val(cmd,PipeClient::Command(cmd));
	DWORD ret=result.ToInt();
	return (ret);
}





