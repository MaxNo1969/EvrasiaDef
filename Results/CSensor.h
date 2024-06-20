#ifndef CSensorH
#define CSensorH
#include "CMeas.h"
#include "uCRListT.h"

class CSensor
{
private:
	void _medianfilter(int _Width, double* _extension, int _half);
	void bubbleSort(double* _arr, int _size);
	void Medianfilter(int _Width);
	void CalcFilters(CMeas::TP _Tp);

public:
	CSensor(void);
	~CSensor(void);

	CRListT<CMeas> MMeas;
	double Level;
	int DClass;

	inline int Size()
	{
		return(MMeas.Count());
	}
	//	void Copy(CSensor* _src);
	bool Load(FILE* _df);
	void Save(FILE* _df);
	void Calc(int _WidthMediam, CMeas::TP _Tp, double _gain, double* _borders);
	void CalcClass(double _gain, double* _borders);
	double GetMaxLevel(void);
};

#endif
