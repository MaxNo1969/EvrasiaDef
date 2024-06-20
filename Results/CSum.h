#ifndef CSumH
#define CSumH
#include "CZoneSum.h"
#include "uCRListT.h"

class CSum
{
private:
	int end_cut;
public:
	CSum(void);
	~CSum(void);

	int cut1;
	int cut2;
	int DClass;
	int min_good_length;
	int ZoneLength;

	CRListT<CZoneSum> MZone;

	inline int Size(void)
	{
		return (MZone.Count());
	}
	void MakeDecision(void);
	void LoadSettings(void);
};
#endif
