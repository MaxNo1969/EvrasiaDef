#ifndef CMeasH
#define CMeasH
#include <stdio.h>

class CMeas
{
private:
public:
	CMeas(void);

	double Source;
	double Median;
	double FilterOut;
	double FilterIn;
	bool Dead;
//	int DClass;
//	int DClassIn;

	void Copy(CMeas* _src);
	bool Load(FILE* _df);
	void Save(FILE* _df);
//	void CalcClass(double _gain, double* _borders);
//	void CalcClass(double _gain, double* _borders, double* _bordersIn);

	enum class TP
	{
		Cross, Line, None
	};
};
#endif
