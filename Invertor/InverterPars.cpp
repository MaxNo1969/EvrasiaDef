#pragma hdrstop
#include "InverterPars.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
InverterPars::InverterPars(void)
{
}

//---------------------------------------------------------------------------
void InverterPars::Load(bool _line)
{
	PA pac;
	PA pat;
	if(_line)
	{
		pac=PA("Defect.Line.Converter");
		pat=PA("TSSet.Current.TSDef.Line");
	}
	else
	{
		pac=PA("Thickness.Converter");
		pat=PA("TSSet.Current.TSThick");
	}
	Abonent=pac.Item("Abonent").Int();
	SpeedRegister=pac.Item("SpeedPar").Int();
	Frequency=pat.Item("Frequency").Int();
}

//---------------------------------------------------------------------------

