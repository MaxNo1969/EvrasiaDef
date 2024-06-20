#pragma hdrstop
#include "BankUnit.h"
#include "uFunctions.h"
#include "Protocol.h"
#pragma package(smart_init)

BankUnit::BankUnit(void)
{
	type = BankZone::EType::BASE;
	SensorsPosition = 0;
	deadEnd = 0;
	Clear();
}

void BankUnit::Clear(void)
{
	isStarted = false;
	complete = false;
}

bool BankUnit::IsComplete()
{
	if (!isStarted)
		return (true);
	return (complete);
}

AnsiString BankUnit::ToString()
{
	return (AnsiString("BankUnit[") + BankZone::TypeToString(type) + "]");
}

void BankUnit::SetDeadEnd(int _ZoneLength, int _dead)
{
	int ldeadEnd = _dead / _ZoneLength;
	if (ldeadEnd*_ZoneLength < _dead)
		ldeadEnd++;
	if (deadEnd < ldeadEnd)
		deadEnd = ldeadEnd;
}

// ===========================================================================
BankDataUnit::BankDataUnit(BankZone::EType _type)
{
	type = _type;
	data = NULL;
	size = 0;
	Clear();
}

void BankDataUnit::Clear(void)
{
	BankUnit::Clear();
	count = 0;
	firstTick = 0;
	lastTick = 0;
}

BankDataUnit::~BankDataUnit(void)
{
	if (data != NULL)
		delete data;
}

void BankDataUnit::ReSize(int _size)
{
	if (size == _size)
		return;
	if (data != NULL)
		delete data;
	size = _size;
	data = new double[size];
	Clear();
}

void BankDataUnit::Add(double* _data, int _size, DWORD _lastTick)
{
	if (!isStarted)
		return;
	if (_size <= 0)
		return;
	lastTick = _lastTick;
	if (count + _size > size)
		FATAL(AnsiString().sprintf
		("BankDataUnit::Add: Превышен размер буфера: %s: count=%d + _size=%d > size=%d",
		BankZone::TypeToString(type), count, _size, size));
	memcpy(data + count, _data, _size*sizeof(double));
	count += _size;
}

// ===========================================================================
BankCUnit::BankCUnit(BankZone::EType _type) : BankDataUnit(_type),
	prevZone(_type)
{
	ZoneLength = 0;
	Sensors = 0;
	SensorsPosition2 = 0;
	Clear();
}

void BankCUnit::Clear(void)
{
	BankDataUnit::Clear();
	prevZone.Ok = false;
}

// ===========================================================================
BankLUnit::BankLUnit(BankZone::EType _type) : BankDataUnit(_type),
	prevZone(_type)
{
	ZoneLength = 0;
	Sensors = 0;
	Clear();
}

void BankLUnit::Clear(void)
{
	BankDataUnit::Clear();
	prevZone.Ok = false;
}

// ===========================================================================
BankTickUnit::BankTickUnit(void)
{
	type = BankZone::EType::THICK;
	MTV.reserve(100);
	Clear();
	ZoneLength = 0;
}

void BankTickUnit::Clear(void)
{
	BankUnit::Clear();
	MTV.clear();
	prevZone.Ok = false;
	prevTicks.Ok = false;
}

// ===========================================================================
BankSGUnit::BankSGUnit(void) : BankDataUnit(BankZone::EType::SG)
{
	Clear();
}

void BankSGUnit::Clear(void)
{
	BankDataUnit::Clear();
	firstSGTick = 0;
	lastSGTick = 0;
	done = false;
}

BankZoneData BankSGUnit::Get()
{
	BankZoneData z = BankZoneData(BankZone::EType::SG);
	if (lastTick == 0 || firstSGTick == 0 || lastSGTick == 0 || data == NULL ||
		lastTick <= firstTick || lastSGTick <= firstSGTick || lastSGTick >
		lastTick)
		return (z);
	double perTick = GetCount();
	perTick /= lastTick - firstTick;

	int f0 = (int)((firstSGTick - firstTick) * perTick);
	if (f0 % 2 != 0)
		f0++;
	if (f0 > GetCount() - 2)
		f0 = GetCount() - 2;

	int f1 = (int)((lastSGTick - firstTick) * perTick);
	if (f1 % 2 != 0)
		f1++;
	if (f1 > GetCount() - 2)
		f1 = GetCount() - 2;

	AnsiString a = "BankSGUnit::Get:";
	a += " f0=";
	a += f0;
	a += " f1=";
	a += f1;
	a += " GetCount()=";
	a += GetCount();
	TPr::pr(a);

	double* data0 = data + f0;
	double* data1 = data + f1;
	z.data = data0;
	z.size = data1 - data0;
	z.Ok = true;
	z.last = true;
	complete = true;
	return (z);
}
