#pragma hdrstop
#include "CCross.h"
#include "PA.h"
#include <Math.hpp>
#include "uFunctions.h"
#include "Classer.h"
#pragma package(smart_init)

CCross::CCross(void)
{
	Tp = CMeas::TP::Cross;
}

void CCross::LoadSettings(void)
{
	CCrossLine::LoadSettings();
	PA pa("TSSet.Current.TSDef.Cross");
	borders[0] = pa.Item("Border1").Double();
	borders[1] = pa.Item("Border2").Double();
	dead_zone_start = pa.Item("DeadZoneStart").Int();
	dead_zone_finish = pa.Item("DeadZoneFinish").Int();

	PA pa1("Defect.Cross.Tails");
	MultStart = pa1.Item("MultStart").Double();
	LenghtStart = pa1.Item("LenghtStart").Int();
	MultEnd = pa1.Item("MultEnd").Double();
	LenghtEnd = pa1.Item("LenghtEnd").Int();

	int CSensors = PA("TSSet.Current.TSDef.Cross.L502Chs").GetCount();
	MSensor2.Capacity(CSensors);
	MSensor2.Clear();
	// int LSensors = PA("TSSet.Current.TSDef.Line.L502Chs").GetCount();
	PA pa2("TSSet.Current.TSDef.Cross.L502Chs");
	for (int s2 = 0; s2 < CSensors; s2++)
	{
		CSensor2* S2=MSensor2.Add();
		S2->Gain = pa2[s2].Item("Gain").Double();
		S2->Offset=pa2[s2].Item("Offset").Int();
	}
}

bool CCross::Load(FILE* _df)
{
	LoadSettings();
	CCrossLine::Load(_df);
	return (true);
}

void CCross::SaveGain(void)
{
	PA pa2("TSSet.Current.TSDef.Cross.L502Chs");
	int aaa=MSensor2.Count();
	for (int s2 = 0; s2 < MSensor2.Count(); s2++)
		pa2[s2].Item("Gain").Write(MSensor2[s2]->Gain);
}

void CCross::Calibrate(int _zone, int _sensor, bool* _mb)
{
	CZone* Z = MZone[_zone];
	double smax = Z->MSensor[_sensor]->GetMaxLevel();
	double sgain = MSensor2[_sensor]->Gain;
	double k = sgain * smax;
	for (int s = 0; s < Z->MSensor.Count(); s++)
	{
		if (s == _sensor)
			continue;
		if (!_mb[s])
			continue;
		MSensor2[s]->Gain = RoundTo(k / Z->MSensor[s]->GetMaxLevel(), -2);
	}
}

void CCross::AddZone(BankZoneData* _z)
{
	BankZoneData2* zone = (BankZoneData2*)_z;
	if (MZone.Count() >= MaxZones)
	{
		AnsiString a = "Result::AddBankZone:  оличество зон ";
		a += MZone.Count();
		a += " больше или равно максимума ";
		a += MaxZones;
		FATAL(a);
	}
	CZone* Z=MZone.Add(new CZone(ZoneLength));

	int packets = zone->size / MSensor2.Count();
	if (packets * MSensor2.Count() != zone->size)
		FATAL("Result::AddZone: packets*MSensor2.Count()!=zone.size");
	double* pbuf = zone->data;

	int packets2 = zone->size2 / MSensor2.Count();
	if (packets2 * MSensor2.Count() != zone->size2)
		FATAL("Result::AddZone: packets2*MSensor2.Count()!=zone2.size");
	double* pbuf2 = zone->data2;

	Z->MSensor.Capacity(MSensor2.Count());
	for (int s = 0; s < MSensor2.Count(); s++)
	{
		if(MSensor2[s]->Offset==0)
			Z->MSensor.Add()->MMeas.Capacity(packets);
		else
			Z->MSensor.Add()->MMeas.Capacity(packets2);
	}
	for (int packet = 0; packet < packets; packet++)
	{
		for (int s = 0; s < MSensor2.Count(); s++)
		{
			if(MSensor2[s]->Offset==0)
				Z->MSensor[s]->MMeas.Add()->Source = *pbuf;
			pbuf++;
		}
	}
	for (int packet = 0; packet < packets2; packet++)
	{
		for (int s = 0; s < MSensor2.Count(); s++)
		{
			if(MSensor2[s]->Offset==1)
				Z->MSensor[s]->MMeas.Add()->Source = *pbuf2;
			pbuf2++;
		}
	}

	CalcXStart(MZone.Count() - 1, false);
	CalcXStart(MZone.Count() - 1, true);

	int width = WidthMedianFilter;
	if (!isMedianFilter)
		width = 0;
	for (int s = 0; s < Z->MSensor.Count(); s++)
		Z->MSensor[s]->Calc(width, Tp, MSensor2[s]->Gain, borders);
	Z->Calc();
	if (zone->length >= 0)
		Z->VZoneLength = zone->length;

	AnsiString a = "Result: ";
	a.cat_printf("AddZone[%d]=%c length=%d~%d", MZone.Count() - 1, Classer::ClassChar(Z->DClass), Z->VZoneLength, zone->length);
	a += " Cross";
	pr(a);
}
