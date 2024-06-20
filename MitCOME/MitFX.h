#ifndef MitFXH
#define MitFXH
#include<System.hpp>
#include "uCCOMPort.h"
#include "ReplyFX.h"

class MitFX
{
private:
	CCOMPort* comport;

	void pr(AnsiString _msg);

	int Abonent;
	int PLC;
	int Timeout;

	AnsiString Request(int _register);
	AnsiString Request(int _register, int _val);
	AnsiString GetACK();
public:
	MitFX(void);
	~MitFX(void);
	int ReadRegI(int _register,AnsiString* _result);
	AnsiString WriteRegI(int _register,int _val);
	int GetTubeLength(AnsiString* _result);
	AnsiString SetSG(AnsiString _SG);
};
#endif
