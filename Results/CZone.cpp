#pragma hdrstop
#include "CZone.h"
#include<System.hpp>
#include <SysUtils.hpp>
#include "uFunctions.h"
#include "Classer.h"
#pragma package(smart_init)

CZone::CZone(int _VZoneLength)
{
	VZoneLength=_VZoneLength;
	Level = -1;
	DClass = -1;
}

CZone::~CZone(void)
{
}

//void CZone::ReSize(int _size)
//{
//	if (_size < 0)
//		throw(Exception("CZone::ReSize: отрицательный размер"));
//	if (_size == 0)
//	{
//		if (MSensor != NULL)
//			delete MSensor;
//		MSensor = NULL;
//		size = 0;
//		return;
//	}
//	if (MSensor == NULL)
//	{
//		size = _size;
//		MSensor = new CSensor[size];
//		return;
//	}
//	if (size == _size)
//		return;
//	CSensor* M = new CSensor[_size];
//	int sz = size;
//	if (sz > _size)
//		sz = _size;
//	for (int i = 0; i < sz; i++)
//		(M + i)->Copy(MSensor + i);
//	delete MSensor;
//	MSensor = M;
//	size = _size;
//}
//
//void CZone::Copy(CZone* _src)
//{
//	size = _src->size;
//	MSensor = _src->MSensor;
//	VZoneLength = _src->VZoneLength;
//	Level = _src->Level;
//	DClass = _src->DClass;
//}

bool CZone::Load(FILE* _df, int _sensors)
{
	/* TODO : Где то используется Level который никакой не Level, а класс */
	double dDClass;
	Fread(&dDClass, sizeof(dDClass), 1, _df);
	DClass = Classer::Check(dDClass);
	int lVZoneLength;
	Fread(&lVZoneLength, sizeof(lVZoneLength), 1, _df);
	if(lVZoneLength>0)
		VZoneLength=lVZoneLength;
	MSensor.Clear();
	MSensor.Capacity(_sensors);
	for (int s = 0; s < _sensors; s++)
		MSensor.Add()->Load(_df);
	return (true);
}

void CZone::Save(FILE* _df)
{
	double dDClass = DClass;
	fwrite(&dDClass, sizeof(dDClass), 1, _df);
	fwrite(&VZoneLength, sizeof(VZoneLength), 1, _df);
	for (int s = 0; s < MSensor.Count(); s++)
		MSensor[s]->Save(_df);
}

void CZone::Calc(void)
{
	DClass = -1;
	Level = -1;
	for (int s = 0; s < MSensor.Count(); s++)
	{
		CSensor* S = MSensor[s];
		if (Level < S->Level)
			Level = S->Level;
		if (DClass == -1)
			DClass = S->DClass;
		else
		{
			if (DClass > S->DClass)
				DClass = S->DClass;
		}
	}
}


