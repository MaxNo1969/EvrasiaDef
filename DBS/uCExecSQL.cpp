//------------------------------------------------------------------------------
#pragma hdrstop
#include "uCExecSQL.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)
//------------------------------------------------------------------------------
CExecSQL::CExecSQL(CDBS* _DBS,AnsiString _SQL)
{
        Init(_DBS,_SQL);
}
//------------------------------------------------------------------------------
CExecSQL::CExecSQL(AnsiString _SQL)
{
        Init(DBS,_SQL);
}
//------------------------------------------------------------------------------
CExecSQL::~CExecSQL()
{
        Q->Active=false;
        delete Q;
}
//------------------------------------------------------------------------------
void CExecSQL::Init(CDBS* _DBS,AnsiString _SQL)
{
        RetMsg="Ok";
        Q=new TADOQuery(NULL);
        Q->Connection=_DBS->Connection();
        Q->SQL->Add(_SQL);
        try
        {
                Q->ExecSQL();
        }
        catch(Exception &ex)
        {
                RetMsg="Ошибка: ";
                RetMsg+=_SQL;
                RetMsg+=" ";
                RetMsg+=ex.Message;
        }
        catch(...)
        {
                RetMsg="Ошибка: ";
                RetMsg+=_SQL;
        }
}
//------------------------------------------------------------------------------

