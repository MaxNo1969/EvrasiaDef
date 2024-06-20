#ifndef BankUnitH
#define BankUnitH
#include <vector>
#include "BankZone.h"
using namespace std;

class BankUnit
{
public:
	BankUnit(void);
	BankZone::EType type;
	bool isStarted;
	bool complete;
	double SensorsPosition;
	void Clear(void);
	bool IsComplete(void);
	AnsiString ToString();
	int deadEnd;
	void SetDeadEnd(int _ZoneLength, int _dead);
};

class BankDataUnit : public BankUnit
{
private:
	int size;
	int count;

public:
	BankDataUnit(BankZone::EType _type);
	~BankDataUnit(void);
	double* data;
	double firstTick;
	double lastTick;
	int packet_offset;
	int Sensors;
	void ReSize(int _size);
	void Clear(void);
	void Add(double* _data, int _size, DWORD _lastTick);

	inline int GetCount(void)
	{
		return (count);
	}
};
class BankLUnit : public BankDataUnit
{
public:
	BankLUnit(BankZone::EType _type);
	double ZoneLength;
	BankZoneData prevZone;
	void Clear(void);
};
class BankCUnit : public BankDataUnit
{
public:
	BankCUnit(BankZone::EType _type);
	double SensorsPosition2;
	double ZoneLength;
	BankZoneData2 prevZone;
	void Clear(void);
};


class BankTickUnit : public BankUnit
{
public:
	BankTickUnit(void);
	void Clear(void);
	BankZoneTicks prevTicks;
	vector<BankZoneVal>MTV;
	BankZoneVal prevZone;
	double ZoneLength;
};

class BankSGUnit : public BankDataUnit
{
public:
	BankSGUnit(void);
	void Clear(void);
	DWORD firstSGTick;
	DWORD lastSGTick;
	BankZoneData Get();
	bool done;
};
#endif
