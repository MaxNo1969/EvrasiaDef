#ifndef CCrossH
#define CCrossH
#include "CCrossLine.h"

class CCross: public CCrossLine
{
public:
	CCross(void);
	void LoadSettings(void);
	void SaveGain(void);
	bool Load(FILE* _df);
	void Calibrate(int _zone, int _sensor,bool* _mb);
	void AddZone(BankZoneData* _z);
};
#endif
