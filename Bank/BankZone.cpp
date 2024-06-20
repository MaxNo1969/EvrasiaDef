#pragma hdrstop
#include "BankZone.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

BankZone::BankZone(EType _type)
{
	Ok = false;
	type = _type;
	last = false;
	index = 0;
}

AnsiString BankZone::TypeToString(void)
{
	return (TypeToString(type));
}

AnsiString BankZone::TypeToString(EType _type)
{
	switch (_type)
	{
	case EType::BASE:
		return ("Базовая");
	case EType::CROSS:
		return ("Пеперечная");
	case EType::LINE:
		return ("Продольная");
	case EType::SG:
		return ("ГП");
	case EType::THICK_TICKS:
		return ("Тики толщины");
	case EType::THICK_VAL:
		return ("Толщина");
	case EType::RESULT:
		return ("Результат");
	}
	return ("Неопределенная");
}

AnsiString BankZone::ToString(void)
{
	AnsiString a = TypeToString();
	a += "[";
	if (!Ok)
		a += "пустая";
	else
		a += index;
	a += "]";
	return (a);
}

// ---------------------------------------------------------------------------
BankZoneData::BankZoneData(EType _type) : BankZone(_type)
{
	data = NULL;
	size = 0;
	length = -1;
}

AnsiString BankZoneData::ToString(void)
{
	if (!Ok)
		return (BankZone::ToString());
	return (BankZone::ToString() + " " + size + ", length=" + length);
}

// ---------------------------------------------------------------------------
BankZoneData2::BankZoneData2(EType _type) : BankZoneData(_type)
{
	data2 = NULL;
	size2 = 0;
}

BankZoneData2::BankZoneData2(BankZoneData _z1, BankZoneData _z2)
	: BankZoneData(_z1.type)
{
	data = _z1.data;
	size = _z1.size;
	length = _z1.length;
	Ok = _z1.Ok && _z2.Ok;
	index = _z1.index;
	last = _z1.last;

	data2 = _z2.data;
	size2 = _z2.size;
}

AnsiString BankZoneData2::ToString(void)
{
	if (!Ok)
		return (BankZoneData::ToString());
	return (BankZoneData::ToString() + " size2=" + size2 + ", length2=" +
		length + ", delta=" + ((int)(data2 - data)));
}

// ---------------------------------------------------------------------------
BankZoneTicks::BankZoneTicks(void) : BankZone(EType::THICK_TICKS)
{
	FirstTick = 0;
	LastTick = 0;
}

AnsiString BankZoneTicks::ToString(void)
{
	if (!Ok)
		return (BankZone::ToString());
	AnsiString a = BankZone::ToString();
	a += " <";
	a += FirstTick;
	a += ",";
	a += LastTick;
	a += ">";
	if (last)
		a += "last";
	return (a);
}

// ---------------------------------------------------------------------------
BankZoneVal::BankZoneVal(void) : BankZone(EType::THICK_VAL)
{
	Val = 0;
	OkVal = false;
}

AnsiString BankZoneVal::ToString(void)
{
	if (!Ok)
		return (BankZone::ToString());
	if (!OkVal)
		return (BankZone::ToString() + " не измерено");
	AnsiString ret = BankZone::ToString();
	ret.cat_printf(" %0.3f", Val);
	if (last)
		ret += " last";
	return (ret);
}

// ---------------------------------------------------------------------------
BankZoneResult::BankZoneResult(void) : BankZone(EType::RESULT)
{
	OkResult = true;
}

BankZoneResult::BankZoneResult(bool _OkResult, int _index)
	: BankZone(EType::RESULT)
{
	Ok = true;
	OkResult = _OkResult;
	index = _index;
}

AnsiString BankZoneResult::ToString(void)
{
	return (BankZone::ToString() + (OkResult ? " Годно" : " Брак"));
}
// ---------------------------------------------------------------------------
