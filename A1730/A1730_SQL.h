#ifndef A1730_SQLH
#define A1730_SQLH
#ifdef A1730_SQLR
#include<SyncObjs.hpp>
#include "uCDBS.h"
#include <IniFiles.hpp>

//---------------------------------------------------------------------------
class A1730_SQL
{
private:
	static bool first;
	void MakeDBS(void);
	void LoadSection(TIniFile* _ini,AnsiString _section, int _dev, bool _in,int _offset);
	int dev;
public:
	DWORD Read(void);
	DWORD ReadOut(void);
	void Write(DWORD _v);
	void WriteSignals(void);
	void ReadSignals(void);
	A1730_SQL(int _DevNum);
	__fastcall ~A1730_SQL(void);
};
//---------------------------------------------------------------------------
#endif
#endif

