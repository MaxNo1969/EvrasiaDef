#pragma hdrstop
#include "CZoneThick.h"
#include "Classer.h"
#include "uFunctions.h"
#pragma package(smart_init)
CZoneThick::CZoneThick(void)
{
	Level=10;
	DClass=-1;
}

void CZoneThick::Copy(CZoneThick* _src)
{
	Level=_src->Level;
	DClass=_src->DClass;
}
bool CZoneThick::Load(FILE* _df)
{
	Fread(&Level, sizeof(Level), 1, _df);
	return(true);
}
void CZoneThick::Save(FILE* _df)
{
	fwrite(&Level, sizeof(Level), 1, _df);
}
void CZoneThick::Calc(double* _borders)
{
	DClass = Classer::ClassThick(Level, _borders);
}

