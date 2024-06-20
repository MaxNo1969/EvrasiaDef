#ifndef ThReturnH
#define ThReturnH
#include "ThBase.h"
#include "JReturn.h"

// ---------------------------------------------------------------------------
class ThReturn : public ThBase
{
private:
	void __fastcall Execute();

public:
	__fastcall ThReturn(TIniFile* _ini);

};
// ---------------------------------------------------------------------------
#endif
