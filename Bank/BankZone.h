#ifndef BankZoneH
#define BankZoneH
#include <System.hpp>

// ---------------------------------------------------------------------------
class BankZone
{
public:
	enum class EType
	{
		BASE, CROSS, LINE, SG, THICK, THICK_TICKS, THICK_VAL, RESULT
	};

	bool Ok;
	int index;
	EType type;
	bool last;

	static AnsiString TypeToString(EType _type);
	AnsiString TypeToString(void);
	virtual AnsiString ToString(void);
	BankZone(EType _type);
};

// ---------------------------------------------------------------------------
class BankZoneData : public BankZone
{
public:
	double* data;
	int size;
	int length;

	BankZoneData(EType _type);
	AnsiString ToString(void);
};
class BankZoneData2 : public BankZoneData
{
public:
	double* data2;
	int size2;


	BankZoneData2(BankZoneData _z1,BankZoneData _z2);
	BankZoneData2(EType _type);
	AnsiString ToString(void);
};

// ---------------------------------------------------------------------------
class BankZoneTicks : public BankZone
{
public:
	DWORD FirstTick;
	DWORD LastTick;

	BankZoneTicks(void);
	AnsiString ToString(void);

};

// ---------------------------------------------------------------------------
class BankZoneVal : public BankZone
{
public:
	double Val;
	bool OkVal;

	BankZoneVal(void);
	AnsiString ToString(void);
};

// ---------------------------------------------------------------------------
class BankZoneResult : public BankZone
{
public:
	bool OkResult;

	BankZoneResult(void);
	BankZoneResult(bool _OkResult, int _index);
	AnsiString ToString(void);
};
#endif
