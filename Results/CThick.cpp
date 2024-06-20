#pragma hdrstop
#include "CThick.h"
#include<System.hpp>
#include <SysUtils.hpp>
#include "uFunctions.h"
#include "PA.h"
#include "Classer.h"
#pragma package(smart_init)

CThick::CThick(void)
{
	borders[0] = 0;
	borders[1] = 0;
	MinThick = 0;
	posMinThick = -1;
	MaxZones = 0;
}

CThick::~CThick(void)
{
}

bool CThick::Load(FILE* _df)
{
	short zones;
	Fread(&zones, sizeof(zones), 1, _df);
	MZone.Clear();
	MZone.Capacity(zones);
	for (int z = 0; z < zones; z++)
		MZone.Add()->Load(_df);
	return (true);
}

void CThick::Save(FILE* _df)
{
	short zones = MZone.Count();
	fwrite(&zones, sizeof(zones), 1, _df);
	for (int z = 0; z < MZone.Count(); z++)
		MZone[z]->Save(_df);
}

void CThick::LoadSettings(void)
{
	MaxZones = PA("MaxZones").Int();
	PA pa("TSSet.Current.TSThick");
	borders[0] = pa.Item("Border1").Double();
	borders[1] = pa.Item("Border2").Double();
}

void CThick::Calc(void)
{
	for (int z = 0; z < Size(); z++)
		MZone[z]->Calc(borders);
}

void CThick::CalcMinThick(int _cut0, int _cut1)
{
	posMinThick = -1;
	int start = 0;
	int stop = MZone.Count();
	if (_cut0 > 0)
		start = _cut0;
	if (_cut1 > 0)
		stop = _cut1 - 1;
	bool first = true;
	for (int z = start; z < stop; z++)
	{
		if (first)
		{
			MinThick = MZone[z]->Level;
			first = false;
		}
		else
		{
			if (MinThick > MZone[z]->Level)
				MinThick = MZone[z]->Level;
		}
		posMinThick = z;
	}
}

void CThick::AddZone(BankZoneVal* _z)
{
	if (_z->index != Size())
		FATAL("CThick::AddZone: не корректный индекс зоны");
	if (Size() >= MaxZones)
	{
		AnsiString a = "CThick::AddZone:  оличество зон ";
		a += Size();
		a += " больше или равно максимума ";
		a += MaxZones;
		FATAL(a);
	}
	MZone.Capacity(MZone.Count()+1);
	CZoneThick* Z=MZone.Add();
	if (_z->Ok)
		Z->Level=_z->Val;
	else
		Z->Level=10.0;
	Z->Calc(borders);
}
