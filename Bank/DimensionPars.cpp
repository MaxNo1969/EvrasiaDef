#pragma hdrstop
#include "DimensionPars.h"
#include "PA.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
DimensionPars::DimensionPars(void)
{
	PA pa("Dimensions");

	CIn=pa.Item("CIn").Int();
	CSensors1=pa.Item("CSensors1").Int();
	CSensors2=pa.Item("CSensors2").Int();
	COut=pa.Item("COut").Int();

	LIn=pa.Item("LIn").Int();
	LSensors=pa.Item("LSensors").Int();
	LOut=pa.Item("LOut").Int();

	TIn=pa.Item("TIn").Int();
	TSensors=pa.Item("TSensors").Int();
	TOut=pa.Item("TOut").Int();

//	SGSensors=pa.Item("SGSensors").Int();
}
//---------------------------------------------------------------------------


