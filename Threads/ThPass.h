#ifndef ThPassH
#define ThPassH
#include "ThBase.h"
//---------------------------------------------------------------------------
class ThPass: public ThBase
{
private:
	void __fastcall Execute();
public:
	__fastcall ThPass(TIniFile* _ini);

};
//---------------------------------------------------------------------------
#endif
