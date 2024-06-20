#ifndef CZoneThickH
#define CZoneThickH
#include <stdio.h>
class CZoneThick
{
public:
	CZoneThick(void);
	double Level;
	int DClass;
	void Copy(CZoneThick* _src);
	bool Load(FILE* _df);
	void Save(FILE* _df);
	void Calc(double* _borders);
};

#endif
