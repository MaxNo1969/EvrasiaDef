#ifndef CZoneH
#define CZoneH
#include "CSensor.h"
#include <stdio.h>

class CZone
{
private:

public:
	CZone(int _VZoneLength);
	~CZone(void);

	CRListT<CSensor> MSensor;
	double Level;
	int DClass;
	int VZoneLength;

//	void ReSize(int _size);
//	void Copy(CZone* _src);
	bool Load(FILE* _df, int _sensors);
	void Save(FILE* _df);
	void Calc(void);
	inline int Size()
	{
		return(MSensor.Count());
	}
};
#endif
