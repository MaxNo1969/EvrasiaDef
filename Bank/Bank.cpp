#pragma hdrstop
#include "Bank.h"
#include "uFunctions.h"
#include "uCExecSQL.h"
#include "protocol.h"
#include "DimensionPars.h"
#include "PA.h"
#include "CMin.h"
#pragma package(smart_init)

AnsiString Bank::TickPosition::ToString(void)
{
	AnsiString a;
	a = "TickPosition: ";
	a += position;
	a += " ";
	a += tick;
	return (a);
}

Bank::Bank(void) : MCross(BankZone::EType::CROSS), MLine(BankZone::EType::LINE)
{
	WaitResultZones = 0;
	CompleteGetResultZones = false;
	DoneCompleteGetResultZones = false;
	CompleteResult = false;
	CompleteGiveResultZones = false;
	cs = new TCriticalSection();
	MTP.reserve(100);
	LoadSettings();
}

Bank::~Bank(void)
{
	delete cs;
}

void Bank::Clear0(void)
{
	MTP.clear();
	MCross.Clear();
	MLine.Clear();
	MSG.Clear();
	MThick.Clear();
	TubeLength = -1;
	resultzone_count = 0;
	MZR.clear();
	pr("=== CLEAR ===");
}

void Bank::LoadSettings(void)
{
	DimensionPars DPars;

	MThick.SensorsPosition = DPars.TSensors;
	MCross.SensorsPosition = DPars.CSensors1;
	MCross.SensorsPosition2 = DPars.CSensors2;
	// MSG.SensorsPosition = DPars.SGSensors;
	MLine.SensorsPosition = DPars.LSensors;

	MCross.Sensors = PA("TSSet.Current.TSDef.Cross.L502Chs").GetCount();
	MLine.Sensors = PA("TSSet.Current.TSDef.Line.L502Chs").GetCount();
	MSG.Sensors = 2;

	MCross.ReSize(PA("Defect.Cross.Buffer").Int()*1024*1024 / sizeof(double));
	MLine.ReSize(PA("Defect.Line.Buffer").Int()*1024*1024 / sizeof(double));
	MSG.ReSize(PA("Defect.SolidGroup.Buffer").Int()*1024*1024 / sizeof(double));

	int zl = PA("ZoneSize").Int();
	MCross.ZoneLength = zl;
	MLine.ZoneLength = zl;
	MThick.ZoneLength = zl;

	MCross.SetDeadEnd(zl, PA("TSSet.Current.TSDef.Cross.DeadZoneFinish").Int());
	MLine.SetDeadEnd(zl, PA("TSSet.Current.TSDef.Line.DeadZoneFinish").Int());
	MThick.SetDeadEnd(zl, PA("TSSet.Current.TSThick.DeadZoneEnd").Int());

	MCross.SetDeadEnd(zl, PA("Defect.Cross.Tails.MultEnd").Double());
	MLine.SetDeadEnd(zl, PA("Defect.Line.Tails.MultEnd").Double());

	Clear0();
}

// private ---------------------------------------------------------------------------
double Bank::TickByPosition(double _position)
{
	TickPosition* p0 = NULL;
	TickPosition* p1 = NULL;
	for (unsigned int i = 0; i < MTP.size(); i++)
	{
		TickPosition* p = &MTP[i];
		if (p->position < _position)
			p0 = p;
		if (_position <= p->position)
		{
			p1 = p;
			break;
		}
	}
	if (p0 == NULL || p1 == NULL)
		return (-1);
	double ret = p0->tick + (_position - p0->position) * (p1->tick - p0->tick) /
		(p1->position - p0->position);
	return (ret);
}

double* Bank::Get(BankLUnit* _LCUnit, double _position)
{
	double tick = TickByPosition(_position);
	if (tick < 0)
		return (NULL);
	double dindex = _LCUnit->GetCount();
	dindex *= (tick - _LCUnit->firstTick);
	dindex /= _LCUnit->lastTick - _LCUnit->firstTick;
	int index = (int)(dindex) - 1;
	index /= _LCUnit->Sensors;
	index *= _LCUnit->Sensors;
	if (index < 0)
		return (NULL);
	if (index >= _LCUnit->GetCount())
		return (NULL);
	// AnsiString a = "Get: ";
	// a += _dataUnit->ToString();
	// a += " pos=";
	// a += _position;
	// a += " index=";
	// a += index;
	// a += " tick=";
	// a += tick;
	// a += " firstTick=";
	// a += _dataUnit->firstTick;
	// a += " lastTick=";
	// a += _dataUnit->lastTick;
	// pr(a);
	return (_LCUnit->data + index);
}

double* Bank::Get2(BankCUnit* _CUnit, double _position)
{
	double tick = TickByPosition(_position);
	if (tick < 0)
		return (NULL);
	double dindex = _CUnit->GetCount();
	dindex *= (tick - _CUnit->firstTick);
	dindex /= _CUnit->lastTick - _CUnit->firstTick;
	int index = (int)(dindex) - 1;
	index /= _CUnit->Sensors;
	index *= _CUnit->Sensors;
	if (index < 0)
		return (NULL);
	if (index >= _CUnit->GetCount())
		return (NULL);
	// AnsiString a = "Get: ";
	// a += _dataUnit->ToString();
	// a += " pos=";
	// a += _position;
	// a += " index=";
	// a += index;
	// a += " tick=";
	// a += tick;
	// a += " firstTick=";
	// a += _dataUnit->firstTick;
	// a += " lastTick=";
	// a += _dataUnit->lastTick;
	// pr(a);
	return (_CUnit->data + index);
}

BankZoneData Bank::GetNextZone0(BankLUnit* _dataUnit, int _SensorsPosition)
{
	BankZoneData z = BankZoneData(_dataUnit->type);

	double *data0;
	double *data1;
	if (!_dataUnit->prevZone.Ok)
	{
		data0 = Get(_dataUnit, _SensorsPosition);
		if (data0 == NULL)
			return (z);
		int pos = (int)_SensorsPosition;
		if (_dataUnit->ZoneLength > 0)
			pos += (int)_dataUnit->ZoneLength;
		else
		{
			if (TubeLength > 0)
			{
				pos += (int)TubeLength;
				z.last = true;
			}
			else
				return (z);
		}
		data1 = Get(_dataUnit, pos);
		if (data1 == NULL)
			return (z);
		z.index = 0;
		z.data = data0;
		z.size = data1 - z.data;
		z.size /= _dataUnit->Sensors;
		z.size *= _dataUnit->Sensors;
		if (z.size <= 0)
			return (z);
		z.Ok = true;
		pr(z.ToString());
		return (z);
	}
	else
	{
		if (_dataUnit->prevZone.last)
			return (z);
		z.index = _dataUnit->prevZone.index + 1;
		z.data = _dataUnit->prevZone.data + _dataUnit->prevZone.size;

		double pos = _dataUnit->ZoneLength * (z.index + 1);
		if (TubeLength > 0)
		{
			if (pos >= TubeLength)
			{
				z.last = true;
				z.length = _dataUnit->ZoneLength - (pos - TubeLength);
				pos = TubeLength;
			}
		}
		data1 = Get(_dataUnit, _SensorsPosition + pos);
		if (data1 == NULL)
			return (z);
		z.size = data1 - z.data;
		if (z.size <= 0)
			return (z);
		z.size /= _dataUnit->Sensors;
		z.size *= _dataUnit->Sensors;
		if (z.size <= 0)
			return (z);
		z.Ok = true;
		return (z);
	}
}

BankZoneData Bank::GetNextZone02(BankCUnit* _dataUnit, int _SensorsPosition,
	bool _second)
{
	BankZoneData z = BankZoneData(_dataUnit->type);

	double *data0;
	double *data1;
	if (!_dataUnit->prevZone.Ok)
	{
		data0 = Get2(_dataUnit, _SensorsPosition);
		if (data0 == NULL)
			return (z);
		int pos = (int)_SensorsPosition;
		if (_dataUnit->ZoneLength > 0)
			pos += (int)_dataUnit->ZoneLength;
		else
		{
			if (TubeLength > 0)
			{
				pos += (int)TubeLength;
				z.last = true;
			}
			else
				return (z);
		}
		data1 = Get2(_dataUnit, pos);
		if (data1 == NULL)
			return (z);
		z.index = 0;
		z.data = data0;
		z.size = data1 - z.data;
		z.size /= _dataUnit->Sensors;
		z.size *= _dataUnit->Sensors;
		if (z.size <= 0)
			return (z);
		z.Ok = true;
		pr(z.ToString());
		return (z);
	}
	else
	{
		if (_dataUnit->prevZone.last)
			return (z);
		z.index = _dataUnit->prevZone.index + 1;
		if (_second)
			z.data = _dataUnit->prevZone.data2 + _dataUnit->prevZone.size2;
		else
			z.data = _dataUnit->prevZone.data + _dataUnit->prevZone.size;

		double pos = _dataUnit->ZoneLength * (z.index + 1);
		if (TubeLength > 0)
		{
			if (pos >= TubeLength)
			{
				z.last = true;
				z.length = _dataUnit->ZoneLength - (pos - TubeLength);
				pos = TubeLength;
			}
		}
		data1 = Get2(_dataUnit, _SensorsPosition + pos);
		if (data1 == NULL)
			return (z);
		z.size = data1 - z.data;
		if (z.size <= 0)
			return (z);
		z.size /= _dataUnit->Sensors;
		z.size *= _dataUnit->Sensors;
		if (z.size <= 0)
			return (z);
		z.Ok = true;
		return (z);
	}
}

BankZoneData Bank::GetNextDataUnitZone(BankLUnit* _dataUnit, bool _check)
{
	BankZoneData z = BankZoneData(_dataUnit->type);
	if (!_dataUnit->IsComplete())
	{
		z = GetNextZone0(_dataUnit, _dataUnit->SensorsPosition);
		if (!_check)
		{
			if (z.Ok)
			{
				_dataUnit->prevZone = z;
				if (z.last)
					_dataUnit->complete = true;
			}
		}
	}
	return (z);
}

BankZoneData2 Bank::GetNextDataUnitZone2(BankCUnit* _dataUnit, bool _check)
{
	BankZoneData2 z = BankZoneData2(_dataUnit->type);
	if (!_dataUnit->IsComplete())
	{
		BankZoneData z1 = GetNextZone02(_dataUnit,
			_dataUnit->SensorsPosition, false);
		BankZoneData z2 = GetNextZone02(_dataUnit,
			_dataUnit->SensorsPosition2, true);
		z = BankZoneData2(z1, z2);
		if (!_check)
		{
			if (z.Ok)
			{
//				pr(AnsiString("z.index=") + z.index);
//				pr(AnsiString("z1.data=") + (unsigned long)(z1.data));
//				pr(AnsiString("z1.data2=") + (unsigned long)
//					(z1.data + z1.size));
//				pr(AnsiString("z2.data=") + (unsigned long)(z2.data));
//				pr(AnsiString("z2.data2=") + (unsigned long)
//					(z2.data + z2.size));
//				pr(AnsiString("deltaZ2Z1=") + ((int)(z2.data - z1.data)));
//				pr(AnsiString("SensorsPosition=") + _dataUnit->SensorsPosition);
//				pr(AnsiString("SensorsPosition2=") +
//					_dataUnit->SensorsPosition2);
//				pr(z.ToString());
				_dataUnit->prevZone = z;
				if (z.last)
					_dataUnit->complete = true;
			}
		}
	}
	return (z);
}

void Bank::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("Bank: ") + _msg);
}

void Bank::prf(AnsiString _format, ...)
{
	va_list paramList;
	va_start(paramList, _format);
	AnsiString a;
	a.vprintf(_format.c_str(), paramList);
	va_end(paramList);
	TPr::pr(AnsiString("Bank: ") + a);
}

void Bank::ReportDataUnit(BankLUnit* _dataUnit, AnsiString _head)
{
	prf("%s count=%d", _head.c_str(), _dataUnit->GetCount());
	prf("%s firstTick=%0.3f", _head.c_str(), _dataUnit->firstTick);
	prf("%s lastTick=%0.3f", _head.c_str(), _dataUnit->lastTick);
	double* prev_dt = _dataUnit->data;
	double prev_tick = 0;
	for (int i = 0; ; i++)
	{
		double pos0 = i * _dataUnit->ZoneLength;
		if (pos0 > TubeLength)
			pos0 = TubeLength;
		double pos = _dataUnit->SensorsPosition + pos0;
		double tick = TickByPosition(pos);
		if (tick < 0)
			break;
		double* dt = Get(_dataUnit, pos);
		prf("%s Zone[%d] pos=%0.3f tick=%0.3f dtick=%0.3f end=%d size=%d",
			_head.c_str(), i - 1, pos, tick, tick - prev_tick,
			dt - _dataUnit->data, dt - prev_dt);
		prev_dt = dt;
		prev_tick = tick;
		if (pos0 >= TubeLength)
			break;

	}
}

void Bank::ReportThick(void)
{
	double prev_tick = 0;
	for (int i = 0; ; i++)
	{
		double pos0 = i * MThick.ZoneLength;
		if (pos0 > TubeLength)
			pos0 = TubeLength;
		double pos = MThick.SensorsPosition + pos0;
		double tick = TickByPosition(pos);
		if (tick < 0)
			break;
		prf("Thick Zone[%d] pos=%0.3f tick=%0.3f dtick=%0.3f", i - 1, pos, tick,
			tick - prev_tick);
		prev_tick = tick;
		if (pos0 >= TubeLength)
			break;
	}
	// for (int i = 0; MThick.MTV.size(); i++)
	// pr(MThick.MTV[i].ToString());
}

void Bank::ReportSG(void)
{
	prf("SG: count=%d", MSG.GetCount());
	prf("SG: firstTick=%d", MSG.firstTick);
	prf("SG: firstSGTick=%d", MSG.firstSGTick);
	prf("SG: lastSGTick=%d", MSG.lastSGTick);
	prf("SG: lastTick=%d", MSG.lastTick);
	prf(AnsiString("SG: complete=") + (MSG.complete ? "true" : "false"));
}

void Bank::ReportResult(void)
{
	for (int i = 0; i < (int)MZR.size(); i++)
		pr(MZR[i].ToString());
}

// public ---------------------------------------------------------------------------
void Bank::Start(IsWork _IW)
{
	cs->Enter();
	{
		Clear0();
		MCross.isStarted = _IW.Cross;
		MLine.isStarted = _IW.Line;
		MSG.isStarted = _IW.SG;
		MThick.isStarted = _IW.Thick;
		startTick = GetTickCount();
		WaitResultZones = 0;
		if (MCross.isStarted && WaitResultZones < MCross.deadEnd)
			WaitResultZones = MCross.deadEnd;
		if (MLine.isStarted && WaitResultZones < MLine.deadEnd)
			WaitResultZones = MLine.deadEnd;
		if (MThick.isStarted && WaitResultZones < MThick.deadEnd)
			WaitResultZones = MThick.deadEnd;
		CompleteGetResultZones = false;
		DoneCompleteGetResultZones = false;
		CompleteResult = false;
		CompleteGiveResultZones = false;
	} cs->Leave();
}

void Bank::AddTickPosition(DWORD _tick, double _position)
{
	cs->Enter();
	{
		TickPosition tp;
		DWORD a1 = _tick - startTick;
		double a2 = _tick - startTick;
		tp.tick = _tick - startTick;
		tp.position = _position;
		MTP.push_back(tp);
		pr(AnsiString("AddTickPosition: ") + tp.ToString());
	} cs->Leave();
}

void Bank::FirstTickCross(DWORD _tick)
{
	cs->Enter();
	{
		if (MCross.isStarted)
			MCross.firstTick = _tick - startTick;
	} cs->Leave();
}

void Bank::FirstTickLine(DWORD _tick)
{
	cs->Enter();
	{
		if (MLine.isStarted)
			MLine.firstTick = _tick - startTick;
	} cs->Leave();
}

void Bank::FirstTickSG(DWORD _tick)
{
	cs->Enter();
	{
		if (MSG.isStarted)
			MSG.firstTick = _tick - startTick;
	} cs->Leave();
}

void Bank::AddCross(DWORD _tick, double* _data, int _size)
{
	cs->Enter();
	{
		if (MCross.isStarted)
			MCross.Add(_data, _size, _tick - startTick);
	} cs->Leave();
}

void Bank::AddLine(DWORD _tick, double* _data, int _size)
{
	cs->Enter();
	{
		if (MLine.isStarted)
			MLine.Add(_data, _size, _tick - startTick);
	} cs->Leave();
}

void Bank::AddSG(DWORD _tick, double* _data, int _size)
{
	cs->Enter();
	{
		if (MSG.isStarted)
			MSG.Add(_data, _size, _tick - startTick);
	} cs->Leave();
}

void Bank::FirstTickSG1(DWORD _tick)
{
	cs->Enter();
	{
		if (MSG.isStarted)
			MSG.firstSGTick = _tick - startTick;
	} cs->Leave();
}

void Bank::LastTickSG1(DWORD _tick)
{
	cs->Enter();
	{
		if (MSG.isStarted)
			MSG.lastSGTick = _tick - startTick;
	} cs->Leave();
}

void Bank::AddThickZone(int _zone, bool _Ok, double _val, bool _last)
{
	cs->Enter();
	{
		if (MThick.isStarted)
		{
			if (MThick.MTV.size() > 0)
			{
				if (MThick.MTV[MThick.MTV.size() - 1].last)
				{
					cs->Leave();
					return;
				}
			}
			BankZoneVal z = BankZoneVal();
			z.Val = _val;
			z.OkVal = _Ok;
			z.Ok = true;
			z.index = _zone;
			z.last = _last;
			MThick.MTV.push_back(z);
		}
	} cs->Leave();
}

void Bank::AddGroup(DWORD _tick, double* _data, int _size)
{
	// pr("AddGroup: tick=%d, size=%d",_tick,_size);
	cs->Enter();
	{
		if (_data == NULL || _size == 0)
		{
			cs->Leave();
			return;
		}
		int sensors = 0;
		if (MCross.isStarted)
		{
			MCross.packet_offset = sensors;
			sensors += MCross.Sensors;
		}
		if (MLine.isStarted)
		{
			MLine.packet_offset = sensors;
			sensors += MLine.Sensors;
		}
		if (MSG.isStarted)
		{
			MSG.packet_offset = sensors;
			sensors += MSG.Sensors;
		}
		if (sensors == 0)
		{
			cs->Leave();
			return;
		}
		int packets = _size / sensors;
		if (packets * sensors != _size)
		{
			AnsiString a =
				"Bank::AddGroup: Размер пакета не кратен количеству датчиков";
			a += " Cross=";
			a += MCross.Sensors;
			a += " Line=";
			a += MLine.Sensors;
			a += " SG=";
			a += MSG.Sensors;
			a += " _size=";
			a += _size;
			FATAL(a);
		}
		for (int i = 0; i < packets; i++)
		{
			if (MCross.isStarted)
				MCross.Add(_data + i * sensors + MCross.packet_offset,
				MCross.Sensors, _tick - startTick);
			if (MLine.isStarted)
				MLine.Add(_data + i * sensors + MLine.packet_offset,
				MLine.Sensors, _tick - startTick);
			if (MSG.isStarted)
			{
				MSG.Add(_data + i * sensors + MSG.packet_offset, MSG.Sensors,
					_tick - startTick);
				// pr(AnsiString("AddGroup: MSG.lastTick=") + MSG.lastTick);
			}
		}
	} cs->Leave();
}

int Bank::GetMinZones(void)
{
	CMin mi;
	if (MThick.isStarted && MThick.prevZone.Ok)
		mi.Add(MThick.prevZone.index);
	if (MCross.isStarted && MCross.prevZone.Ok)
		mi.Add(MCross.prevZone.index);
	if (MLine.isStarted && MLine.prevZone.Ok)
		mi.Add(MLine.prevZone.index);
	return (mi.Val()+1);
}

bool Bank::IsComplete()
{
	bool ret;
	cs->Enter();
	{
		bool lcomplete = MCross.IsComplete() && MLine.IsComplete()
			&& MSG.IsComplete() && MThick.IsComplete();
		if (!lcomplete)
		{
			AnsiString aaa = "Еще не завершены: ";
			if (!MCross.IsComplete())
				aaa += "Cross ";
			if (!MLine.IsComplete())
				aaa += "Line ";
			if (!MSG.IsComplete())
				aaa += "SG ";
			if (!MThick.IsComplete())
				aaa += "Thick ";
//			pr(aaa);
		}
		else if (!CompleteGetResultZones)
			pr("Еще не получены все результирующие зоны");
		else if (!DoneCompleteGetResultZones)
			pr("Еще не	сообщено о получении всех результирующих зон");
		else if (!CompleteResult)
			pr("Еще не пересчитаны все результирующие зоны");
		else if (!CompleteGiveResultZones)
			pr("Еще не отданы все результирующие зоны");
		ret = CompleteGiveResultZones;
	} cs->Leave();
	return (ret);
}

void Bank::SetTubeLength(int _length)
{
	cs->Enter();
	{
		TubeLength = _length;
	} cs->Leave();
}

BankZoneData2 Bank::GetNextCrossZone(bool _check)
{
	BankZoneData2 z = BankZoneData2(BankZone::EType::BASE);
	cs->Enter();
	{
		z = GetNextDataUnitZone2(&MCross, _check);
		if (z.Ok)
			pr(AnsiString("!!!GetNextCrossZone2: ") + z.ToString());
	} cs->Leave();
	return (z);
}

BankZoneData Bank::GetNextLineZone(bool _check)
{
	BankZoneData z = BankZoneData(BankZone::EType::BASE);
	cs->Enter();
	{
		z = GetNextDataUnitZone(&MLine, _check);
		if (z.Ok)
			pr(AnsiString("GetNextLineZone: ") + z.ToString());
	} cs->Leave();
	return (z);
}

BankZoneData Bank::GetNextSGZone(bool _check)
{
	BankZoneData z = BankZoneData(BankZone::EType::BASE);
	cs->Enter();
	{
		if (!MSG.done)
		{
			z = MSG.Get();
			if (z.Ok)
			{
				if (!_check)
					MSG.done = true;
				pr(z.ToString());
			}
		}
	} cs->Leave();
	return (z);
}

BankZoneTicks Bank::GetNextZoneThick(void)
{
	BankZoneTicks z;
	double fTick;
	double lTick;
	if (!MThick.prevTicks.Ok)
	{
		z.index = 0;
		z.last = false;
		fTick = TickByPosition(MThick.SensorsPosition);
		if (fTick < 0)
			return (z);
		lTick = TickByPosition(MThick.SensorsPosition + MThick.ZoneLength);
		if (lTick < 0)
			return (z);
	}
	else
	{
		if (MThick.prevTicks.last)
			return (z);
		z.index = MThick.prevTicks.index + 1;
		fTick = MThick.prevTicks.LastTick - startTick;
		z.last = false;
		double pos = MThick.ZoneLength * (z.index + 1);
		if (TubeLength > 0)
		{
			if (pos >= TubeLength)
			{
				pos = TubeLength;
				z.last = true;
			}
		}
		lTick = TickByPosition(MThick.SensorsPosition + pos);
		if (lTick < 0)
			return (z);
	}
	z.FirstTick = startTick + (DWORD)fTick;
	z.LastTick = startTick + (DWORD)lTick;
	z.Ok = true;
	return (z);
}

BankZoneTicks Bank::GetNextThickTicks(bool _check)
{
	BankZoneTicks z;
	cs->Enter();
	{
		if (!MThick.IsComplete())
		{
			z = GetNextZoneThick();
			if (!_check)
			{
				if (z.Ok)
				{
					MThick.prevTicks = z;
					pr(AnsiString("GetNextThickTicks: ") + z.ToString());
				}
			}
		}
	} cs->Leave();
	return (z);
}

BankZoneVal Bank::GetNextThickZone(bool _check)
{
	BankZoneVal z;
	cs->Enter();
	{
		if (!MThick.IsComplete())
		{
			if (!MThick.prevZone.Ok)
			{
				if (MThick.MTV.size() <= 0)
				{
					cs->Leave();
					return (z);
				}
				z = MThick.MTV[0];
			}
			else
			{
				if ((int)MThick.MTV.size() <= MThick.prevZone.index + 1)
				{
					cs->Leave();
					return (z);
				}
				z = MThick.MTV[MThick.prevZone.index + 1];
			}
			if (!_check)
			{
				if (z.Ok)
				{
					MThick.prevZone = z;
					if (z.last)
					{
						pr("GetNextThickZone: MThick.complete = true");
						MThick.complete = true;
					}
				}
			}
		}
	} cs->Leave();
	if (z.Ok)
		pr(AnsiString("GetNextThickZone: ") + z.ToString());
	return (z);
}

void Bank::FirstTickGroup(DWORD _tick)
{
	cs->Enter();
	{
		DWORD tick = _tick - startTick;
		if (MCross.isStarted)
			MCross.firstTick = tick;
		if (MLine.isStarted)
			MLine.firstTick = tick;
		if (MSG.isStarted)
			MSG.firstTick = tick;
	} cs->Leave();
}

void Bank::AddResultZone(int _index, bool _result)
{
	cs->Enter();
	{
		if (_index < MZR.size())
			MZR[_index].OkResult = _result;
		else
		{
			BankZoneResult z = BankZoneResult(_result, _index);
			pr(AnsiString("AddResultZone: ") + z.ToString());
			MZR.push_back(z);
			if (!CompleteGetResultZones)
			{
				if (MCross.IsComplete() && MLine.IsComplete() && MSG.IsComplete
					() && MThick.IsComplete())
				{
					pr(AnsiString("GetMinZones()=")+GetMinZones());
					pr(AnsiString("MZR.size()=")+MZR.size());
					if (GetMinZones() == MZR.size())
						CompleteGetResultZones = true;
				}
			}
		}
	} cs->Leave();
}

bool Bank::CheckCompleteGetResultZones(void)
{
	bool ret = false;
	cs->Enter();
	{
		if (!DoneCompleteGetResultZones)
		{
			if (CompleteGetResultZones)
			{
				DoneCompleteGetResultZones = true;
				ret = true;
			}
		}
	} cs->Leave();
	return (ret);
}

BankZoneResult Bank::GetNextResultZone(void)
{
	BankZoneResult ret;
	cs->Enter();
	{
		if (CompleteResult)
		{
			if (resultzone_count < MZR.size())
			{
				ret = MZR[resultzone_count];
				resultzone_count++;
				if (resultzone_count == MZR.size())
					CompleteGiveResultZones = true;
				pr(AnsiString("resultzone_count=") + resultzone_count);
			}
		}
		else
		{
			int sz = MZR.size();
			sz -= WaitResultZones;
			if (resultzone_count < sz)
			{
				ret = MZR[resultzone_count];
				resultzone_count++;
				pr(AnsiString("resultzone_countW=") + resultzone_count);
			}
		}
	} cs->Leave();
	return (ret);
}

void Bank::Report(void)
{
	cs->Enter();
	{
		prf("startTick=%ld", startTick);
		// pr("ZoneLength=%0.3f", ZoneLength);
		prf("TubeLength=%0.3f", TubeLength);
		for (vector<TickPosition>::iterator it = MTP.begin();
		it != MTP.end(); it++)
			pr(it->ToString());
		// ReportDataUnit(&MCross, "Cross");
		// ReportDataUnit(&MLine, "Line");
#ifdef RADOP
		ReportSG();
#endif
		ReportThick();
		ReportResult();
		AnsiString a = "CLTG: ";
		a += MCross.IsComplete() ? "true" : "false";
		a += ",";
		a += MLine.IsComplete() ? "true" : "false";
		a += ",";
		a += MThick.IsComplete() ? "true" : "false";
		a += ",";
		a += MSG.IsComplete() ? "true" : "false";
		pr(a);
	} cs->Leave();
}
// ---------------------------------------------------------------------------
