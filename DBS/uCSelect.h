//------------------------------------------------------------------------------
#ifndef uCSelectH
#define uCSelectH
//------------------------------------------------------------------------------
#include "uCDBS.h"
//------------------------------------------------------------------------------
class CSelect
{
private:
        TADOQuery* Q;
        AnsiString RetMsg;
		void Init(CDBS* _DBS,AnsiString _SQL);
		bool no_par;
public:
		CSelect(CDBS* _DBS,AnsiString _SQL,bool _no_par=true);
		CSelect(AnsiString _SQL,bool _no_par=true);
		~CSelect(void);
		AnsiString Exec(void);
		inline AnsiString IsOk(void){return(RetMsg);};
		void InputString(AnsiString _name,AnsiString _value);

        int Count(void);
        AnsiString AsAnsiString(AnsiString _name);
        bool AsBool(AnsiString _name);
        int AsInt(AnsiString _name);
        double AsDouble(AnsiString _name);
        char AsChar(AnsiString _name);
        __int64 AsInt64(AnsiString _name);
        void Next(void);
		bool Eof(void);
};
//------------------------------------------------------------------------------
#endif
