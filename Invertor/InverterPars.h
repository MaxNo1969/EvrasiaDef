#ifndef InverterParsH
#define InverterParsH
#include "PA.h"
//---------------------------------------------------------------------------
class InverterPars
{
private:
public:
	InverterPars(void);
	void Load(bool _line);
	int Abonent;
	int SpeedRegister;
	int Frequency;
};
//---------------------------------------------------------------------------
#endif
