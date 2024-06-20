#pragma hdrstop
#include "CMeas.h"
#include "uFunctions.h"
#include "Classer.h"
#pragma package(smart_init)

CMeas::CMeas(void)
{
	Source = 0;
	Median = 0;
	FilterOut = 0;
	FilterIn = 0;
	Dead = false;
	// DClass = -1;
	// DClassIn = -1;
}

void CMeas::Copy(CMeas* _src)
{
	Source = _src->Source;
	Median = _src->Median;
	FilterOut = _src->FilterOut;
	FilterIn = _src->FilterIn;
	Dead = _src->Dead;
	// DClass = -1;
	// DClassIn = -1;
}

bool CMeas::Load(FILE* _df)
{
	Fread(&Source, sizeof(Source), 1, _df);
	Median = 0;
	FilterOut = 0;
	FilterIn = 0;
	Dead = false;
//	DClass = -1;
//	DClassIn = -1;
	return (true);
}

void CMeas::Save(FILE* _df)
{
	fwrite(&Source, sizeof(Source), 1, _df);
}

// void CMeas::CalcClass(double _gain, double* _borders)
// {
// CalcClass(_gain, _borders, NULL);
// }
//
// void CMeas::CalcClass(double _gain, double* _borders, double* _bordersIn)
// {
// DClass = Classer::Class(FilterOut * _gain, _borders);
// if (_bordersIn == NULL)
// DClassIn = -1;
// else
// DClassIn = Classer::Class(FilterIn * _gain, _borders);
// }
