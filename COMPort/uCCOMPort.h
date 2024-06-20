// ---------------------------------------------------------------------------
#ifndef uCCOMPortH
#define uCCOMPortH
// ---------------------------------------------------------------------------
#include<system.hpp>
// ---------------------------------------------------------------------------
typedef void (__closure *OnProtocolDef)(AnsiString _msg);
class CCOMPort
{
protected:
	CCOMPort(void){};

public:
	virtual ~CCOMPort(void){};
	virtual bool read_s(unsigned char* _s,int _n)=0;
	virtual bool write_s(unsigned char* _s,int _n)=0;
	OnProtocolDef OnProtocol;
	virtual void ClearBuffer(void)=0;
};
// ---------------------------------------------------------------------------
#endif
