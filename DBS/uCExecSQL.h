//------------------------------------------------------------------------------
#ifndef uCExecSQLH
#define uCExecSQLH
//------------------------------------------------------------------------------
#include "uCDBS.h"
//------------------------------------------------------------------------------
class CExecSQL
{
private:
        TADOQuery* Q;
        AnsiString RetMsg;
        void Init(CDBS* _DBS,AnsiString _SQL);
public:
        CExecSQL(CDBS* _DBS,AnsiString _SQL);
        CExecSQL(AnsiString _SQL);
        ~CExecSQL(void);
        inline AnsiString IsOk(void){return(RetMsg);};
        inline int RowsAffected(void){return(Q->RowsAffected);};
};
//------------------------------------------------------------------------------
#endif
