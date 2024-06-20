#pragma hdrstop
#include "CZoneSum.h"
#pragma package(smart_init)

CZoneSum::CZoneSum(void)
{
	DClass = -1;
}

void CZoneSum::Copy(CZoneSum* _src)
{
	DClass = _src->DClass;
}
