// ---------------------------------------------------------------------------
#pragma hdrstop
#include "SGR.h"
// ---------------------------------------------------------------------------
#include "protocol.h"
#include "SignalListDef.h"
#include <Math.hpp>
#include "uCExecSQL.h"
#include "uCExecSQLP.h"
#include "uFunctions.h"
#include "uCExecute.h"
#include "uCSelect.h"
#include "PA.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

AnsiString SGR::SG::ToString()
{
	AnsiString a="SG: g=";
	a+=group;
	a+=" p=";
	a+=probability;
	a+=" color=";
	a+=color;
	return(a);
}

// ---------------------------------------------------------------------------
SGR::SGR(AnsiString _SGroupFix)
{
	SGroupFix = _SGroupFix;
	periodMin = 500;
	periodMax = 700;

	borders = 10;
	borders1 = 10;
	ByU = false;
	tube_id = 0;
	LoadSettings();
}

// ---------------------------------------------------------------------------
void SGR::LoadSettings(void)
{
	typeSize = PA("TSSet.Current.Name").String();
	AnsiString SQL;
	SQL = "select * from Uran.SGPars";
	CSelect S1 = CSelect(SQL);
	int period;
	if (S1.Count() == 1)
	{
		period = S1.AsInt("period");
		int period_dif = S1.AsInt("period_dif");
		periodMin = period - period_dif;
		periodMax = period + period_dif;
		borders = S1.AsInt("borders");
		borders1 = S1.AsInt("borders1");
		ByU = S1.AsAnsiString("algorithm") == "По напряжению";
	}

	SQL = "select val from Uran.SGTresh where typeSize='";
	SQL += typeSize;
	SQL += "' order by par";
	CSelect S = CSelect(SQL);
	tresh.resize(S.Count());
	for (unsigned int i = 0; i < tresh.size(); i++)
	{
		double v = period;
		v /= 100;
		v *= S.AsInt("val");
		tresh[i] = (int)v;
		S.Next();
	}
}

// ---------------------------------------------------------------------------
void SGR::pr(AnsiString _msg)
{
	AnsiString a = "SGR: ";
	a += _msg;
	pr0(a);
}

// ---------------------------------------------------------------------------
void SGR::pr0(AnsiString _msg)
{
	TPr::pr(_msg);
}

// ---------------------------------------------------------------------------
//bool SGR::SaveToDB(void)
//{
//	CExecute E("Uran.AddSGTube");
//	E.InputString("@typeSize", typeSize);
//	E.InputString("@img", data);
//	E.OutputLong("@id");
//	if (E.Exec() != 1)
//		FATAL("SG::SaveToDB: Не удалось добавить трубу");
//	tube_id = E.AsLong("@id");
//
//	for (unsigned int i = 0; i < coords.size(); i++)
//	{
//		AnsiString SQL = "insert into Uran.SGTubePars values (";
//		SQL += tube_id;
//		SQL += ",";
//		SQL += i;
//		SQL += ",";
//		SQL.cat_printf("%0.10lf", coords[i]);
//		SQL += ")";
//		pr(SQL);
//		CExecSQL* E = new CExecSQL(SQL);
//		AnsiString ret = E->IsOk();
//		delete E;
//		if (ret != "Ok")
//		{
//			pr(AnsiString("SaveToDB: ") + ret);
//			return (false);
//		}
//	}
//	return (true);
//}

// ---------------------------------------------------------------------------
//SGR::SG SGR::GetSG(int _position)
//{
//	CExecute E("Uran.GetSGw");
//	E.InputLong("@id", tube_id);
//	E.OutputString("@group");
//	E.OutputDouble("@probability");
//	E.OutputInt("@color");
//	if (E.Exec() != 1)
//		FATAL("SG::GetSG: Не удалось рассчитать трубу");
//	SG ret;
//	ret.group = E.AsString("@group");
//	ret.probability = E.AsDouble("@probability");
//	ret.color = conv_color(E.AsInt("@color"));
//	if (ret.group.Length() == 0)
//		ret.group = "Х";
//	return (ret);
//}

// ---------------------------------------------------------------------------
SGR::SG SGR::SaveGetSG()
{
	CExecute E("Uran.AddGetSGTube");
	E.InputString("@typeSize", typeSize);
	E.InputString("@img", data);
	E.OutputString("@group");
	E.OutputDouble("@probability");
	E.OutputInt("@color");
	if (E.Exec() != 1)
		FATAL("SG::SaveGetSG: Не удалось добавить трубу");
	SG ret;
	ret.group = E.AsString("@group");
	ret.probability = E.AsDouble("@probability");
	ret.color = conv_color(E.AsInt("@color"));
	if (ret.group.Length() == 0)
		ret.group = "Х";
	pr(ret.ToString());
	return (ret);
}
TColor SGR::conv_color(int _col)
{
	unsigned int ret;
	ret = _col >> 16 & 0xFF;
	ret |= _col & 0xFF00;
	ret |= _col << 16 & 0xFF0000;
	return ((TColor)ret);
}

// ---------------------------------------------------------------------------
void SGR::CheckTypeSize(void)
{
	AnsiString SQL = "select count(*) as nn from Uran.SGTypeSizes where name='";
	SQL += typeSize;
	SQL += "'";
	CSelect S(SQL);
	if (S.AsInt("nn") < 1)
	{
		SQL = "insert into Uran.SGTypeSizes values('";
		SQL += typeSize;
		SQL += "')";
		CExecSQL E(SQL);
		if (E.RowsAffected() != 1)
			FATAL("SGR::CheckTypeSize: не могу вставить типоразмер");
	}
}

// ---------------------------------------------------------------------------
void SGR::IUToStr(void)
{
	int psize = 7 + 1 + 7 + 1;
	char* cc = new char[9 + iu.size() * psize + 1];
	char* p = cc;
	sprintf(p, "%08d;", (int)iu.size());
	p += 9;
	for (unsigned int i = 0; i < iu.size(); i++)
	{
		sprintf(p, "%07.2lf %07.2lf;", iu[i].I, iu[i].U);
		p += psize;
	}
	data = cc;
	delete cc;
}

// ---------------------------------------------------------------------------
bool SGR::GetNextPeriodI(int* _start, int* _size)
{
	*_start += *_size + 1;
	bool last = true;
	for (; *_start < stop; (*_start)++)
	{
		if (iu[*_start].I < 0)
		{
			if (last == false)
			{
				int size = GetNextSizeI(_start);
				if (size >= 0)
				{
					*_size = size;
					return (true);
				}
			}
			last = true;
		}
		else
			last = false;
	}
	return (false);
}

// ---------------------------------------------------------------------------
int SGR::GetNextSizeI(int* _start)
{
	int size = 0;
	for (int i = *_start; i < stop; i++)
	{
		if (iu[i].I < 0)
			size++;
		else
			break;
	}
	if (size >= periodMin && size < periodMax)
		return (size);
	return (-1);
}

// ---------------------------------------------------------------------------
bool SGR::GetNextPeriodU(int* _start, int* _size)
{
	*_start += *_size + 1;
	bool last = true;
	for (; *_start < stop; (*_start)++)
	{
		if (iu[*_start].U > 0)
		{
			if (last == false)
			{
				int size = GetNextSizeU(_start);
				if (size >= 0)
				{
					*_size = size;
					return (true);
				}
			}
			last = true;
		}
		else
			last = false;
	}
	return (false);
}

// ---------------------------------------------------------------------------
int SGR::GetNextSizeU(int* _start)
{
	int size = 0;
	for (int i = *_start; i < stop; i++)
	{
		if (iu[i].U > 0)
			size++;
		else
			break;
	}
	if (size >= periodMin && size < periodMax)
		return (size);
	return (-1);
}

// ---------------------------------------------------------------------------
void SGR::CalcCoords(void)
{
	double v = iu.size();
	v /= 100;
	v *= borders;
	int start = (int)v;
	v = iu.size();
	v /= 100;
	v *= borders1;
	stop = iu.size() - (int)v;
	int size_period = 0;
	coords.resize(tresh.size());
	for (unsigned int i = 0; i < coords.size(); i++)
		coords[i] = 0;
	double nn = 0;
	for (; ;)
	{
		bool ok;
		if (ByU)
			ok = GetNextPeriodU(&start, &size_period);
		else
			ok = GetNextPeriodI(&start, &size_period);
		if (!ok)
			break;
		/*
		 AnsiString a;
		 a += "start=";
		 a += start;
		 a += " size=";
		 a += size_period;
		 pr(a);
		 */
		for (unsigned int i = 0; i < coords.size(); i++)
		{
			if (ByU)
				coords[i] += iu[start + tresh[i]].I;
			else
				coords[i] += iu[start + tresh[i]].U;
		}
		nn++;
	}
	for (unsigned int i = 0; i < coords.size(); i++)
	{
		coords[i] /= nn;
		if (IsNan(coords[i]))
			coords[i] = 0;

	}
}

// ---------------------------------------------------------------------------
bool SGR::Test(int _period)
{
	// lcard->StartSG();
	// Sleep(_period*1000);
	// lcard->Read();
	// lcard->StopSG();
	// GetSGSignal();
	// IUToStr();
	// CalcCoords();
	// if (!SaveToDB())
	// {
	//
	// pr("Test: не смогли записать группу прочности в базу");
	// return(false);
	// }
	return (true);
}

// ---------------------------------------------------------------------------
void SGR::AddZone(BankZoneData _zone)
{
	iu.resize(_zone.size / 2);
	for (unsigned int i = 0; i < iu.size(); i++)
	{
		iu[i].I = _zone.data[i * 2];
		iu[i].U = _zone.data[i * 2 + 1];
	}
	IUToStr();
	sg=SaveGetSG();
	if (SGroupFix.Length() != 0)
	{
		sg.color = clYellow;
		sg.probability = 0;
		sg.group = SGroupFix;
	}
//	CalcCoords();
//	CheckTypeSize();
//	if (!SaveToDB())
//		FATAL("SGR::Exec: не смогли записать группу прочности в базу");
//	if (SGroupFix.Length() != 0)
//	{
//		sg.color = clYellow;
//		sg.probability = 0;
//		sg.group = SGroupFix;
//	}
//	else
//		sg = GetSG(0);

}
// ---------------------------------------------------------------------------
