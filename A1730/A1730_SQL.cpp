#pragma hdrstop
#ifdef A1730_SQLR
#include<IniFiles.hpp>
#include "A1730_SQL.h"
#include "uCDBS.h"
#include "Protocol.h"
#include "uCExecSQL.h"
#include "uCSelect.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
A1730_SQL::A1730_SQL(int _DevNum)
{
	if (first)
	{
		first = false;
		//MakeDBS();
	}
	dev = _DevNum;
}

//---------------------------------------------------------------------------
__fastcall A1730_SQL::~A1730_SQL(void)
{
}

//---------------------------------------------------------------------------
DWORD A1730_SQL::Read(void)
{
	DWORD ret = 0;
	AnsiString SQL = "";
	SQL.printf("Select digital,position,val from Uran.SignalsVirtual where board=%d and input='true'", dev);
	CSelect S = CSelect(SQL);
	for (int i = 0; i < S.Count(); i++)
	{
		if (S.AsBool("val"))
		{
			int index = S.AsInt("position");
			if (S.AsBool("digital"))
				index += 16;
			ret |= 1 << index;
		}
		S.Next();
	}
	return (ret);
}

//---------------------------------------------------------------------------
DWORD A1730_SQL::ReadOut(void)
{
	DWORD ret = 0;
	AnsiString SQL = "";
	SQL.printf("Select digital,position,val from Uran.SignalsVirtual where board=%d and input='false'", dev);
	CSelect S = CSelect(SQL);
	for (int i = 0; i < S.Count(); i++)
	{
		if (S.AsBool("val"))
		{
			int index = S.AsInt("position");
			if (S.AsBool("digital"))
				index += 16;
			ret |= 1 << index;
		}
		S.Next();
	}
	return (ret);
}

//---------------------------------------------------------------------------
void A1730_SQL::Write(DWORD _v)
{
	for (int i = 0; i < sizeof(DWORD) * 8; i++)
	{
		bool digital = (i >= 16);
		int index = i;
		if (index >= 16)
			index -= 16;
		AnsiString SQL = "";
		SQL.printf
			("update Uran.SignalsVirtual set val='%s' where board=%d and input='false' and digital='%s' and position=%d"
			, (_v&(1 << i)) ? "true" : "false", dev, digital ? "true" : "false", index);
		CExecSQL E = CExecSQL(SQL);
	}
}

//---------------------------------------------------------------------------
void A1730_SQL::MakeDBS(void)
{
	CExecSQL E = CExecSQL("delete from Uran.SignalsVirtual");
	TIniFile *ini = new TIniFile("..\\..\\Settings\\IO_Management.ini");
	LoadSection(ini, "ACard0_IN", 0, true, 0);
	LoadSection(ini, "ACard0_OUT", 0, false, 0);
	LoadSection(ini, "ACard0_IN_Digital", 0, true, 16);
	LoadSection(ini, "ACard0_OUT_Digital", 0, false, 16);
	LoadSection(ini, "ACard1_IN", 1, true, 0);
	LoadSection(ini, "ACard1_OUT", 1, false, 0);
	LoadSection(ini, "ACard1_IN_Digital", 1, true, 16);
	LoadSection(ini, "ACard1_OUT_Digital", 1, false, 16);
	delete ini;
}

//---------------------------------------------------------------------------
void A1730_SQL::LoadSection(TIniFile* _ini, AnsiString _section, int _dev, bool _in, int _offset)
{
	TStringList *keys = new TStringList();
	_ini->ReadSection(_section, keys);
	for (int i = 0; i < keys->Count; i++)
	{
		AnsiString Key = keys->Strings[i];
		AnsiString MapKey = _ini->ReadString(_section, Key, "");
		AnsiString a = "1730: ";
		a += _section;
		a += "[";
		a += Key;
		a += "] ";
		a += _dev;
		if (_in)
			a += "IN";
		else
			a += "OUT";
		a += ": ";
		a += MapKey;
		TPr::pr(a);
		AnsiString SQL = "";
		SQL.printf("insert into Uran.SignalsVirtual values(%d,'%s','%s',%d,'%s','false')", _dev, _in ? "true" : "false",
			(_offset == 0) ? "false" : "true", Key.ToInt(), MapKey.c_str());
		CExecSQL E = CExecSQL(SQL);
	}
	delete keys;

}

bool A1730_SQL::first = true;
#endif
