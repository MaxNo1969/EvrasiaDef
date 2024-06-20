#ifndef uCCOMPort_realH
#define uCCOMPort_realH
//---------------------------------------------------------------------------
#include<system.hpp>
#include "PA.h"
#include "uCCOMPort.h"

//---------------------------------------------------------------------------
class CCOMPort_real : public CCOMPort
{
private:
	AnsiString COM;
	HANDLE handleCom;
	bool verbal;

	CCOMPort_real(PA _pa, AnsiString* _error_msg);

public:
	static CCOMPort_real* Create(PA _pa ,AnsiString* _error_msg);
	~CCOMPort_real(void);
	bool read_s(unsigned char* _s, int _n);
	bool write_s(unsigned char* _s, int _n);
	void ClearBuffer(void);
};

#endif
