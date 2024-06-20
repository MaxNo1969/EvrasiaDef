#pragma hdrstop
#include "CSum.h"
#include "PA.h"
#include<System.hpp>
#include <SysUtils.hpp>
#pragma package(smart_init)

CSum::CSum(void)
{
	cut1=0;
	cut2=0;
	DClass = -1;
	min_good_length=0;
	end_cut=0;
	ZoneLength=PA("ZoneSize").Int();
}

CSum::~CSum(void)
{
}


void CSum::MakeDecision(void)
{
	// принимает решение по трубе, заполняет значения резов
	bool flag = false;
	// сигнализирует, что текущий участок будет помечен 2-ым классом, если превысит минимальную годную длину
	bool class2 = false; // участок точно будет помечен 2-ым классом
	int temp = 0; // длина текущего участка в зонах
	int tcut1 = 0; // временный первый рез
	cut1 = 0;
	cut2 = 0; // резов по умолчанию нет
	DClass = -1; // решение не принято
	if (min_good_length > 0)
	{
		for (int z = 0; z < MZone.Count(); z++)
		{
			int dclass = MZone[z]->DClass;
			if (dclass == 2)
				temp++;
			else if (dclass == 0)
			{
				if (temp >= min_good_length)
				{
					cut2 = z;
					cut1 = z - temp;
					class2 = flag;
				}
				temp = 0;
				tcut1 = z + 1;
				flag = false;
			}
			else if (dclass == 1)
			{
				flag = true;
				temp++;
			}
		}

		if (temp < min_good_length && cut2 == 0 && cut1 == 0)
			DClass = 0;
		else if (temp >= min_good_length)
		{
			if (flag)
				DClass = 1;
			else
				DClass = 2;
			cut1 = tcut1;
			cut2 = 0;
		}
		else if (cut1 > 0 || cut2 > 0)
		{
			if (class2)
				DClass = 1;
			else
				DClass = 2;
		}

		// ебаный пыть-ях блеать
		if (end_cut > 0 && DClass != 0)
		{
			if (cut2 == 0)
				cut2 = MZone.Count();
			int f1 = (end_cut - cut1 > 0) ? (end_cut - cut1) : (0);
			int f2 = (end_cut - MZone.Count() + cut2 > 0) ?
				(end_cut - MZone.Count() + cut2) : (0);
			if (cut2 - cut1 - f1 - f2 < min_good_length)
				DClass = 0;
		}
		// Примочка для Казахстана
		if (cut1 > 0)
			cut1++;
	}
	// работа по зеленке - любой брак - сразу косяк
	else
	{
		bool brack = false;
		for (int z = 0; z < MZone.Count(); z++)
		{
			int dclass = MZone[z]->DClass;
			if (dclass == 0)
			{
				brack = true;
				break;
			}
			else if (dclass == 1)
				class2 = true;
		}
		if (brack)
			DClass = 0;
		else if (class2)
			DClass = 1;
		else
			DClass = 2;

	}
}
void CSum::LoadSettings(void)
{
	min_good_length = PA("TSSet.Current.MinGoodLength").Int();
	end_cut = PA("TSSet.Current.EndCut").Int();
}

