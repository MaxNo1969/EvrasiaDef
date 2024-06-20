#ifndef CLineH
#define CLineH
#include "CCrossLine.h"

class CLine : public CCrossLine
{
public:
	CLine(void);
	void LoadSettings(void);
	bool Load(FILE* _df);
	void SaveGain(void);
	void AddZone(BankZoneData* _zone);
};
#endif
