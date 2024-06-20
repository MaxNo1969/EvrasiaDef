#ifndef RChannel_parametersH
#define RChannel_parametersH
#include "PA.h"

//---------------------------------------------------------------------------
class RChannel_parameters
{
private:
public:
	AnsiString name;
	unsigned int range;
	unsigned int phisicalChannel;
	unsigned int collectedMode;
	RChannel_parameters(void);
	RChannel_parameters(PA _pa);
	RChannel_parameters(PA _pa, AnsiString _name);
	RChannel_parameters(const RChannel_parameters& _p);
	AnsiString ToString(void);
};
//---------------------------------------------------------------------------
#endif
