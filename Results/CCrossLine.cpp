#pragma hdrstop
#include "CCrossLine.h"
#include<System.hpp>
#include <SysUtils.hpp>
#include "uFunctions.h"
#include "PA.h"
#include "Filters.h"
#include "Classer.h"
#include "Protocol.h"
#pragma package(smart_init)

CCrossLine::CCrossLine(void)
{
	FromFile = false;
	borders[0] = 0;
	borders[1] = 0;
	bordersIn[0] = 0;
	bordersIn[1] = 0;
	dead_zone_start = 0;
	dead_zone_finish = 0;
	MultStart = 1;
	LenghtStart = 0;
	MultEnd = 1;
	LenghtEnd = 0;
	ZoneLength = 0;
	WidthMedianFilter = 0;
	isMedianFilter = false;
	Tp = CMeas::TP::None;
	MaxZones = 0;
}

CCrossLine::~CCrossLine(void)
{
}

// void CCrossLine::ReSize(int _size)
// {
// if (_size < 0)
// throw(Exception("CCrossLine::ReSize: отрицательный размер"));
// if (_size == 0)
// {
// if (MZone != NULL)
// delete MZone;
// MZone = NULL;
// size = 0;
// return;
// }
// if (MZone == NULL)
// {
// size = _size;
// MZone = new CZone[size];
// return;
// }
// if (size == _size)
// return;
// CZone* M = new CZone[_size];
// int sz = size;
// if (sz > _size)
// sz = _size;
// for (int i = 0; i < sz; i++)
// (M + i)->Copy(MZone + i);
// delete MZone;
// MZone = M;
// size = _size;
// }
//
// void CCrossLine::ReSize2(int _size)
// {
// if (_size < 0)
// throw(Exception("CCrossLine::ReSize2: отрицательный размер"));
// if (_size == 0)
// {
// if (MSensor2 != NULL)
// delete MSensor2;
// MSensor2 = NULL;
// size2 = 0;
// return;
// }
// if (MSensor2 == NULL)
// {
// size2 = _size;
// MSensor2 = new CSensor2[size2];
// return;
// }
// if (size2 == _size)
// return;
// CSensor2* S2 = new CSensor2[_size];
// int sz = size2;
// if (sz > _size)
// sz = _size;
// for (int i = 0; i < sz; i++)
// S2[i].Copy(MSensor2 + i);
// delete MSensor2;
// MSensor2 = S2;
// size2 = _size;
// }
//
// void CCrossLine::Adjust2(void)
// {
// int sz = 0;
// if (MZone != NULL)
// sz = MZone->Size();
// ReSize2(sz);
// for (int s2 = 0; s2 < size2; s2++)
// {
// CSensor2* S2 = MSensor2 + s2;
// S2->ReSize(size);
// for (int z2 = 0; z2 < S2->Size(); z2++)
// S2->MZone2[z2].MMeas = MZone[z2].MSensor[s2].MMeas;
// }
// }

bool CCrossLine::Load(FILE* _df)
{
	short zones;
	Fread(&zones, sizeof(zones), 1, _df);
	MZone.Clear();
	MZone.Capacity(zones);
	short sensors_a;
	Fread(&sensors_a, sizeof(sensors_a), 1, _df);
	for (int z = 0; z < zones; z++)
		MZone.Add(new CZone(ZoneLength))->Load(_df, sensors_a);
	FromFile = true;
	return (true);
}

void CCrossLine::Save(FILE* _df)
{
	short sbuf = MZone.Count();
	fwrite(&sbuf, sizeof(sbuf), 1, _df);
	sbuf = MSensor2.Count();
	fwrite(&sbuf, sizeof(sbuf), 1, _df);
	for (int z = 0; z < MZone.Count(); z++)
		MZone[z]->Save(_df);
}

void CCrossLine::CalcXStart(bool _dead)
{
	for (int z = 0; z < MZone.Count(); z++)
	{
		if (!CalcXStart(z, _dead))
			break;
	}
}

void CCrossLine::CalcXEnd(bool _dead)
{
	int lLength = _dead ? dead_zone_finish : LenghtEnd;
	if (lLength == 0)
		return;
	if (!_dead && MultStart == 1)
		return;

	int pos_start = 0;
	for (int z = MZone.Count() - 1; z >= 0; z--)
	{
		CZone* Z = MZone[z];
		int pos_end = pos_start + Z->VZoneLength;
		if (pos_end <= lLength)
		{
			for (int s = 0; s < Z->MSensor.Count(); s++)
			{
				CSensor* S = Z->MSensor[s];
				for (int m = 0; m < S->MMeas.Count(); m++)
				{
					if (_dead)
						S->MMeas[m]->Dead = true;
					else
						S->MMeas[m]->Source *= MultStart;
				}
			}
		}
		else
		{
			for (int s = 0; s < Z->MSensor.Count(); s++)
			{
				CSensor* S = Z->MSensor[s];
				double delta = lLength - pos_start;
				double K = delta / Z->VZoneLength;
				double X = K * S->MMeas.Count();
				int x = (int)X;
				for (int m = S->MMeas.Count() - 1; m >= x; m--)
				{
					if (_dead)
						S->MMeas[m]->Dead = true;
					else
						S->MMeas[m]->Source *= MultStart;
				}
			}
			break;
		}
		pos_start += Z->VZoneLength;
	}
}

bool CCrossLine::CalcXStart(int _zone, bool _dead)
{
	int lLength = _dead ? dead_zone_start : LenghtStart;
	if (lLength == 0)
		return (false);
	if (!_dead && MultStart == 1)
		return (false);
	CZone* Z = MZone[_zone];

	int pos_start = _zone * ZoneLength;
	int pos_end = pos_start + ZoneLength;
	if (pos_start > lLength)
		return (false);
	if (pos_end <= lLength)
	{
		for (int s = 0; s < Z->MSensor.Count(); s++)
		{
			CSensor* S = Z->MSensor[s];
			for (int m = 0; m < S->MMeas.Count(); m++)
			{
				if (_dead)
					S->MMeas[m]->Dead = true;
				else
					S->MMeas[m]->Source *= MultStart;
			}
		}
		return (true);
	}
	for (int s = 0; s < Z->MSensor.Count(); s++)
	{
		CSensor* S = Z->MSensor[s];
		double delta = lLength - pos_start;
		double K = delta / ZoneLength;
		double X = K * S->MMeas.Count();
		int x = (int)X;
		for (int m = 0; m < x; m++)
		{
			if (_dead)
				S->MMeas[m]->Dead = true;
			else
				S->MMeas[m]->Source *= MultStart;
		}
	}
	return (true);
}

void CCrossLine::LoadSettings(void)
{
	MaxZones = PA("MaxZones").Int();
	ZoneLength = PA("ZoneSize").Int();
	isMedianFilter = PA("Defect.Some.IsMedianFilter").Bool();
	WidthMedianFilter = PA("Defect.Some.WidthMedianFilter").Int();
	if (WidthMedianFilter < 3)
		isMedianFilter = false;
	else
	{
		if (WidthMedianFilter % 2 == 0)
			WidthMedianFilter++;
	}
}

void CCrossLine::Calc(void)
{
	CalcXStart(false);
	CalcXEnd(false);
	CalcXStart(true);
	CalcXEnd(true);
	int width = WidthMedianFilter;
	if (!isMedianFilter)
		width = 0;
	for (int z = 0; z < MZone.Count(); z++)
	{
		CZone* Z = MZone[z];
		for (int s = 0; s < Z->MSensor.Count(); s++)
			Z->MSensor[s]->Calc(width, Tp, MSensor2[s]->Gain, borders);
		Z->Calc();
	}
}

void CCrossLine::CalcClass(void)
{
	for (int z = 0; z < MZone.Count(); z++)
	{
		CZone* Z = MZone[z];
		for (int s = 0; s < Z->MSensor.Count(); s++)
			Z->MSensor[s]->CalcClass(MSensor2[s]->Gain, borders);
		Z->Calc();
	}
}

int CCrossLine::GetSensorsCount(void)
{
	return (MZone.Count() == 0 ? 0 : MZone[0]->MSensor.Count());
}

bool CCrossLine::IsInner(void)
{
	return (Tp == CMeas::TP::Line && LinearFilterIn->IsFilter());
}

void CCrossLine::PushGains(void)
{
	for (int s2 = 0; s2 < MSensor2.Count(); s2++)
		MSensor2[s2]->GainBuf = MSensor2[s2]->Gain;
}

void CCrossLine::PopGains(void)
{
	for (int s2 = 0; s2 < MSensor2.Count(); s2++)
		MSensor2[s2]->Gain = MSensor2[s2]->GainBuf;
}

//void CCrossLine::AddZone(BankZoneData* _zone)
//{
//	if (MZone.Count() >= MaxZones)
//	{
//		AnsiString a = "Result::AddBankZone: Количество зон ";
//		a += MZone.Count();
//		a += " больше или равно максимума ";
//		a += MaxZones;
//		FATAL(a);
//	}
//	int packets = _zone->size / MSensor2.Count();
//	if (packets * MSensor2.Count() != _zone->size)
//		FATAL("Result::AddZone: packets*MSensor2.Count()!=_zone.size");
//	CZone* Z = MZone.Add();
//	Z->MSensor.Capacity(MSensor2.Count());
//	for (int s = 0; s < MSensor2.Count(); s++)
//		Z->MSensor.Add()->MMeas.Capacity(packets);
//	double* pbuf = _zone->data;
//	for (int packet = 0; packet < packets; packet++)
//	{
//		for (int s = 0; s < size2; s++)
//			Z->MSensor[s]->MMeas.Add()->SourceSource = *(pbuf++);
//	}
//	CalcXStart(size - 1, false);
//	CalcXStart(size - 1, true);
//
//	int width = WidthMedianFilter;
//	if (!isMedianFilter)
//		width = 0;
//	for (int s = 0; s < Z->Size(); s++)
//		Z->MSensor[s].Calc(width, Tp, MSensor2[s].Gain, borders);
//	Z->Calc();
//	if (_zone->length >= 0)
//		Z->VZoneLength = _zone->length;
//
//	AnsiString a = "Result: ";
//	a.cat_printf("AddZone[%d]=%c length=%d~%d", size - 1, Classer::ClassChar(Z->DClass), Z->VZoneLength, _zone->length);
//	if (Tp == CMeas::TP::Line)
//		a += " Line";
//	else
//		a += " Cross";
//	pr(a);
//}

void CCrossLine::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("CCrossLine: ") + _msg);
}
