#ifndef CCrossLineH
#define CCrossLineH
#include "CZone.h"
#include "CSensor2.h"
#include "Bank.h"

class CCrossLine
{
private:
	void CalcXStart(bool _dead);
	void CalcXEnd(bool _dead);
protected:
	int MaxZones;
	bool CalcXStart(int _zone, bool _dead);
	void pr(AnsiString _msg);
public:
	bool FromFile;
	CMeas::TP Tp;
	CCrossLine(void);
	~CCrossLine(void);

	CRListT<CZone> MZone;
	CRListT<CSensor2> MSensor2;
	double borders[2];
	double bordersIn[2];

	int dead_zone_start;
	int dead_zone_finish;
	double MultStart;
	int LenghtStart;
	double MultEnd;
	int LenghtEnd;
	int ZoneLength;
	int WidthMedianFilter;
	bool isMedianFilter;

//	void ReSize(int _size);
//	void ReSize2(int _size);
//	void Adjust2(void);
	bool Load(FILE* _df);
	void LoadSettings(void);
	void Calc(void);
	void CalcClass(void);
	bool IsInner(void);

	int GetSensorsCount(void);
	void PushGains(void);
	void PopGains(void);
	virtual void SaveGain(void)=0;
	virtual void Calibrate(int _zone, int _sensor,bool* _mb){}
	void Save(FILE* _df);
	virtual void AddZone(BankZoneData* _zone)=0;
	inline int Size()
	{
		return(MZone.Count());
	}
	inline int Size2()
	{
		return(MSensor2.Count());
	}
};
#endif
