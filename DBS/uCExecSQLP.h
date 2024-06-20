//---------------------------------------------------------------------------
#ifndef uCExecSQLPH
#define uCExecSQLPH
//---------------------------------------------------------------------------
#include "uCDBS.h"
//---------------------------------------------------------------------------
//	Пример:
//	CExecSQLP P = CExecSQLP("update Uran.SGTubes set img=:@img where position=0");
//	P.InputString("@img", data);
//---------------------------------------------------------------------------
class CExecSQLP
{
private:
		TADOQuery* Q;
		void Init(CDBS* _DBS,AnsiString _SQL);
		AnsiString SQL;
public:
		CExecSQLP(CDBS* _DBS,AnsiString _SQL);
		CExecSQLP(AnsiString _SQL);
		~CExecSQLP(void);
		AnsiString Exec(void);
		inline int RowsAffected(void){return(Q->RowsAffected);};
		void InputString(AnsiString _name,AnsiString _value);
};
//---------------------------------------------------------------------------
#endif
