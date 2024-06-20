//------------------------------------------------------------------------------
#ifndef uCDBSH
#define uCDBSH
//------------------------------------------------------------------------------
#include <system.hpp>
#include <ADODB.hpp>
//------------------------------------------------------------------------------
class CDBS
{
private:
		TADOConnection* ADOConnection;
		AnsiString ErrMsg;
		void Init(AnsiString _ConnectString);
		bool need_delete;
public:
		CDBS(AnsiString _ConnectString);
		CDBS();
		CDBS(TADOConnection* _ADOConnection);
		~CDBS(void);
		inline AnsiString IsOk(void){return(ErrMsg);};
        inline TADOConnection* Connection(void){return(ADOConnection);};
};
//------------------------------------------------------------------------------
extern CDBS* DBS;
#endif
