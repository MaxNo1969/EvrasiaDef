//------------------------------------------------------------------------------
#ifndef uCExecuteH
#define uCExecuteH
//------------------------------------------------------------------------------
#include "uCDBS.h"

//------------------------------------------------------------------------------
class CExecute
{
private:
	TADOStoredProc* SP;
	AnsiString RetMsg;
	void Init(CDBS* _DBS, AnsiString _SQL);
public:
	CExecute(CDBS* _DBS, AnsiString _SQL);
	CExecute(AnsiString _SQL);
	~CExecute(void);
	void InputString(AnsiString _name, AnsiString _value);
	void OutputString(AnsiString _name);
	void InputInt(AnsiString _name, int _value);
	void OutputDouble(AnsiString _name);
	void OutputInt(AnsiString _name);
	void OutputLong(AnsiString _name);
	void InputLong(AnsiString _name, int _value);
	long AsLong(AnsiString _name);
	int Exec(void);
	AnsiString AsString(AnsiString _name);
	double AsDouble(AnsiString _name);
	int AsInt(AnsiString _name);
};
//------------------------------------------------------------------------------
#endif
