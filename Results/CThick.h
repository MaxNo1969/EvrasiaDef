#ifndef CThickH
#define CThickH
#include "CZoneThick.h"
#include "Bank.h"
#include "uCRListT.h"

class CThick
{
private:
	int MaxZones;

public:
	CThick(void);
	~CThick(void);

	CRListT<CZoneThick> MZone;
	double borders[2];
	double MinThick;
	int posMinThick;
	void CalcMinThick(int _cut0,int _cut1);

	inline int Size(void)
	{
		return (MZone.Count());
	}
	bool Load(FILE* _df);
	void Save(FILE* _df);
	void Calc(void);
	void LoadSettings(void);
	void AddZone(BankZoneVal* _z);
};
#endif
