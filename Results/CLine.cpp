#pragma hdrstop
#include "CLine.h"
#include "PA.h"
#include "uFunctions.h"
#include "Classer.h"
#pragma package(smart_init)
CLine::CLine(void)
{
	Tp=CMeas::TP::Line;
}
void CLine::LoadSettings(void)
{
	CCrossLine::LoadSettings();
	PA pa("TSSet.Current.TSDef.Line");
	borders[0] = pa.Item("Border1").Double();
	borders[1] = pa.Item("Border2").Double();
	bordersIn[0] = pa.Item("Border1In").Double();
	bordersIn[1] = pa.Item("Border2In").Double();
	dead_zone_start = pa.Item("DeadZoneStart").Int();
	dead_zone_finish = pa.Item("DeadZoneFinish").Int();

	PA pa1("Defect.Line.Tails");
	MultStart=pa1.Item("MultStart").Double();
	LenghtStart=pa1.Item("LenghtStart").Int();
	MultEnd=pa1.Item("MultEnd").Double();
	LenghtEnd=pa1.Item("LenghtEnd").Int();

	int LSensors = PA("TSSet.Current.TSDef.Line.L502Chs").GetCount();
	MSensor2.Capacity(LSensors);
	PA pa2("TSSet.Current.TSDef.Line.L502Chs");
	MSensor2.Clear();
	for(int s2=0;s2<LSensors;s2++)
		MSensor2.Add()->Gain=pa2[s2].Item("Gain").Double();
}
bool CLine::Load(FILE* _df)
{
	LoadSettings();
	CCrossLine::Load(_df);
	return(true);
}
void CLine::SaveGain(void)
{
	PA pa2("TSSet.Current.TSDef.Line.L502Chs");
	for(int s2=0;s2<MSensor2.Count();s2++)
		pa2[s2].Item("Gain").Write(MSensor2[s2]->Gain);
}
void CLine::AddZone(BankZoneData* _zone)
{
	if (MZone.Count() >= MaxZones)
	{
		AnsiString a = "Result::AddBankZone:  оличество зон ";
		a += MZone.Count();
		a += " больше или равно максимума ";
		a += MaxZones;
		FATAL(a);
	}
	int packets = _zone->size / MSensor2.Count();
	if (packets * MSensor2.Count() != _zone->size)
		FATAL("Result::AddZone: packets*MSensor2.Count()!=_zone.size");
	CZone* Z = MZone.Add(new CZone(ZoneLength));
	Z->MSensor.Capacity(MSensor2.Count());
	for (int s = 0; s < MSensor2.Count(); s++)
		Z->MSensor.Add()->MMeas.Capacity(packets);
	double* pbuf = _zone->data;
	for (int packet = 0; packet < packets; packet++)
	{
		for (int s = 0; s < MSensor2.Count(); s++)
			Z->MSensor[s]->MMeas.Add()->Source = *(pbuf++);
	}
	CalcXStart(MZone.Count() - 1, false);
	CalcXStart(MZone.Count() - 1, true);

	int width = WidthMedianFilter;
	if (!isMedianFilter)
		width = 0;
	for (int s = 0; s < Z->MSensor.Count(); s++)
		Z->MSensor[s]->Calc(width, Tp, MSensor2[s]->Gain, borders);
	Z->Calc();
	if (_zone->length >= 0)
		Z->VZoneLength = _zone->length;

	AnsiString a = "Result: ";
	a.cat_printf("AddZone[%d]=%c length=%d~%d", MZone.Count() - 1, Classer::ClassChar(Z->DClass), Z->VZoneLength, _zone->length);
	a += " Line";
	pr(a);
}




