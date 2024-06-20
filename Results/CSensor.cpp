#pragma hdrstop
#include "CSensor.h"
#include<System.hpp>
#include <SysUtils.hpp>
#include "uFunctions.h"
#include "Filters.h"
#include "Classer.h"
#pragma package(smart_init)

CSensor::CSensor(void)
{
	Level = -1;
	DClass = -1;
}

CSensor::~CSensor(void)
{
}

//void CSensor::ReSize(int _size)
//{
//	if (_size < 0)
//		throw(Exception("CSensor::ReSize: отрицательный размер"));
//	if (_size == 0)
//	{
//		if (MMeas != NULL)
//			delete MMeas;
//		MMeas = NULL;
//		size = 0;
//		return;
//	}
//	if (MMeas == NULL)
//	{
//		size = _size;
//		MMeas = new CMeas [size];
//		return;
//	}
//	if (size == _size)
//		return;
//	CMeas* M = new CMeas[_size];
//	int sz = size;
//	if (sz > _size)
//		sz = _size;
//	for (int i = 0; i < sz; i++)
//		(M + i)->Copy(MMeas + i);
//	delete MMeas;
//	MMeas = M;
//	size = _size;
//}

//void CSensor::Copy(CSensor* _src)
//{
//	size = _src->size;
//	MMeas = _src->MMeas;
//	Level = _src->Level;
//}

bool CSensor::Load(FILE* _df)
{
	Fread(&Level, sizeof(Level), 1, _df);
	int size;
	Fread(&size, sizeof(size), 1, _df);
	MMeas.Clear();
	MMeas.Capacity(size);
	for (int m = 0; m < size; m++)
		MMeas.Add()->Load(_df);
	return (true);
}

void CSensor::Save(FILE* _df)
{
	fwrite(&Level, sizeof(Level), 1, _df);
	int size=MMeas.Count();
	fwrite(&size, sizeof(size), 1, _df);
	for (int m = 0; m < size; m++)
		MMeas[m]->Save(_df);
}

void CSensor::Medianfilter(int _Width)
{
	int half = (_Width - 1) / 2;
	if (half < 1 || MMeas.Count() <= half)
	{
		for (int m = 0; m < MMeas.Count(); m++)
		{
			CMeas* M = MMeas[m];
			M->Median = M->Source;
		}
		return;
	}
	int size_e = MMeas.Count() + half * 2;
	double* extension = new double[size_e];
	for (int m = 0; m < MMeas.Count(); m++)
		extension[half + m] = MMeas[m]->Source;
	for (int i = 0; i < half; i++)
	{
		extension[i] = MMeas[i]->Source;
		extension[size_e - half + i] = MMeas[MMeas.Count() - half + i]->Source;
	}
	_medianfilter(_Width, extension, half);
	delete[]extension;
}

void CSensor::_medianfilter(int _Width, double* _extension, int _half)
{
	double* window = new double[_Width];
	for (int i = 0; i < MMeas.Count(); i++)
	{
		for (int j = 0; j < _Width; j++)
			window[j] = _extension[i + j];
		bubbleSort(window, _Width);
		MMeas[i]->Median = window[_half];
	}
	delete window;
}

void CSensor::bubbleSort(double* _arr, int _size)
{
	double tmp;
	for (int i = 0; i < _size - 1; ++i) // i - номер прохода
	{
		for (int j = 0; j < _size - 1; ++j) // внутренний цикл прохода
		{
			if (_arr[j + 1] < _arr[j])
			{
				tmp = _arr[j + 1];
				_arr[j + 1] = _arr[j];
				_arr[j] = tmp;
			}
		}
	}
}

void CSensor::CalcFilters(CMeas::TP _Tp)
{
	for (int m = 0; m < MMeas.Count(); m++)
	{
		CMeas* M = MMeas[m];
		M->FilterIn = M->Median;
		M->FilterOut = M->Median;
	}
	double* buf = new double[MMeas.Count()];
	if (_Tp == CMeas::TP::Line)
	{
		if (LinearFilterOut->IsFilter())
		{
			for (int m = 0; m < MMeas.Count(); m++)
			{
				CMeas* M = MMeas[m];
				buf[m] = M->FilterOut;
			}
			LinearFilterOut->toFilter(buf, MMeas.Count());
			for (int m = 0; m < MMeas.Count(); m++)
			{
				CMeas* M = MMeas[m];
				M->FilterOut = buf[m];
			}
		}
		if (LinearFilterIn->IsFilter())
		{
			for (int m = 0; m < MMeas.Count(); m++)
			{
				CMeas* M = MMeas[m];
				buf[m] = M->FilterIn;
			}
			LinearFilterIn->toFilter(buf, MMeas.Count());
			for (int m = 0; m < MMeas.Count(); m++)
			{
				CMeas* M = MMeas[m];
				M->FilterIn = buf[m];
			}
		}
	}
	else
	{
		if (CrossFilter->IsFilter())
		{
			for (int m = 0; m < MMeas.Count(); m++)
			{
				CMeas* M = MMeas[m];
				buf[m] = M->FilterOut;
			}
			CrossFilter->toFilter(buf, MMeas.Count());
			for (int m = 0; m < MMeas.Count(); m++)
			{
				CMeas* M = MMeas[m];
				M->FilterOut = buf[m];
			}
		}
	}
	delete buf;
}

void CSensor::Calc(int _WidthMediam, CMeas::TP _Tp, double _gain,
	double* _borders)
{
	Medianfilter(_WidthMediam);
	CalcFilters(_Tp);
	CalcClass(_gain, _borders);
}
void CSensor::CalcClass(double _gain, double* _borders)
{
	DClass = Classer::Class(GetMaxLevel() * _gain, _borders);
}

double CSensor::GetMaxLevel(void)
{
	Level = -1;
	double v;
	for (int m = 0; m < MMeas.Count(); m++)
	{
		CMeas* M = MMeas[m];
		if (M->Dead)
			continue;
		v = M->FilterOut;
		if (v < 0)
			v = -v;
		if (Level < v)
			Level = v;
	}
	return (Level);
}
