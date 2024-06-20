// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <Math.hpp>
#include "uFViewZoneD.h"
#include "uFunctions.h"
#include <VCLTee.Series.hpp>
#include "Singleton.h"
#include "uCDBS.h"
#include "protocol.h"
#include "uCExecSQL.h"
#include "uCSelect.h"
#include "Classer.h"
#include "PA.h"
#include "Filters.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#pragma link "Chart"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "Series"
#pragma link "ArrowCha"
#pragma link "BubbleCh"
*/
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TFViewZoneD::TFViewZoneD(TComponent* Owner, CMeas::TP _Tp,
	AnsiString _title) : TForm(Owner)
{
	title = _title;
	Tp = _Tp;
	Tube = NULL;
}

// ---------------------------------------------------------------------------
void __fastcall TFViewZoneD::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if (Key == VK_ESCAPE)
		Close();
}

// ---------------------------------------------------------------------------
void __fastcall TFViewZoneD::FormCreate(TObject *Sender)
{
	PA("Defect.Wins").LoadFormPos(this);
	SetMetric(0, 0);
	KeyUpFlag = true;
	levelOut1 = 0;
	levelOut2 = 0;
	levelIn1 = 0;
	levelIn2 = 0;
	mouse_on = false;
}

// ---------------------------------------------------------------------------
void TFViewZoneD::SetInner(bool _v)
{
	if (_v)
		Chart1->LeftAxis->Minimum = -100;
	else
		Chart1->LeftAxis->Minimum = 0;
}

// ---------------------------------------------------------------------------
void __fastcall TFViewZoneD::FormDestroy(TObject *Sender)
{
	PA("Defect.Wins").SaveFormPos(this);
	/* TODO : It's need to send a event to parent for clear selected mark. */
}

// ---------------------------------------------------------------------------
void TFViewZoneD::SetCaption(AnsiString _cap)
{
	Caption = title + " " + _cap;
}

void TFViewZoneD::SetMetric(double _start, double _zone_size)
{
	start = _start;
	zone_size = _zone_size;
	if (start < 0)
		start = 0;
	if (zone_size < 0)
		zone_size = 0;
}

void TFViewZoneD::Clear(void)
{
	for (int i = 0; i < Chart1->SeriesCount(); i++)
		Chart1->Series[i]->Clear();
	Arrow->Clear();
	Mark->Clear();
};

// ---------------------------------------------------------------------------
void TFViewZoneD::SetBorder(TLineSeries* _series, double _level, TColor _color)
{
	_series->Clear();
	_series->AddXY(0, _level, "", _color);
	_series->AddXY(BarOut->MaxXValue(), _level, "", _color);
}

void TFViewZoneD::SetCurrPoint(int _curr_zone, int _curr_sens, bool _IsLinear)
{
	curr_zone = _curr_zone;
	curr_sens = _curr_sens;
	IsLinear = _IsLinear;
}
// ---------------------------------------------------------------------------

void __fastcall TFViewZoneD::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)

{
	if (KeyUpFlag)
	{
		curr_defect = cbEtalonTubeDefects->ItemIndex;
		KeyUpFlag = false;
	}
	switch (Key)
	{
	case VK_LEFT:
		if (curr_zone > 0)
		{
			curr_zone--;
			Draw();
		}
		break;
	case VK_RIGHT:
		{
			CCrossLine* CL = (Tp == CMeas::TP::Cross) ?
				(CCrossLine*)&Tube->Cross : (CCrossLine*)&Tube->Line;
			if (curr_zone + 1 < CL->Size())
			{
				curr_zone++;
				Draw();
			}
		} break;
	case VK_UP:
		{
			CCrossLine* CL = (Tp == CMeas::TP::Cross) ?
				(CCrossLine*)&Tube->Cross : (CCrossLine*)&Tube->Line;
			if (curr_sens + 1 < CL->GetSensorsCount())
			{
				curr_sens++;
				Draw();
			}
		} break;
	case VK_DOWN:
		if (curr_sens > 0)
		{
			curr_sens--;
			Draw();
		}
		break;
	case VK_ESCAPE:
		Close();
		break;
	}
}

// ---------------------------------------------------------------------------
void TFViewZoneD::ViewEtalonCheck()
{
	// TPr::pr("ViewEtalonCheck");
	AnsiString Str = "";
	AnsiString SOP = PA("Defect.SOP.SOPPaint").String();
	if (SOP != "Empty")
	{
		// собираем данные по дефектам эталона
		AnsiString SQL;
		SQL = "SELECT * FROM EtalonTubeDefects  where SOP='";
		SQL += SOP;
		SQL += "' and Module='";
		SQL += IsLinear ? "Продольный" : "Поперечный";
		SQL += "' order by SOP,id";

		int countDefects = 0;
		int selectedDefect = cbEtalonTubeDefects->ItemIndex;
		cbEtalonTubeDefects->Clear();
		cbEtalonTubeDefects->Visible = true;
		Chart1->SeriesList->AddGroup("Defects");
		CSelect S = CSelect(SQL);
		int numOfDefects = S.Count();
		for (; !S.Eof(); S.Next())
		{
			int startMeas = 0;
			int finalMeas = 0;
			// добавляем запись в КомбоБокс
			countDefects++;
			Str = IntToStr(countDefects) + "/" + IntToStr(numOfDefects);
			Str += IsLinear ? " продольный " : " поперечный ";
			Str += S.AsInt("DefPoint") - S.AsInt("DefRadius");
			Str += "-";
			Str += S.AsInt("DefPoint") + S.AsInt("DefRadius");
			cbEtalonTubeDefects->AddItem(Str, NULL);

			AnsiString markh;
			markh = S.AsAnsiString("SOP");
			markh += "[";
			markh += S.AsInt("Id");
			markh += "] ";
			markh += S.AsInt("DefPoint") - S.AsInt("DefRadius");
			markh += "-";
			markh += S.AsInt("DefPoint") + S.AsInt("DefRadius");
			markh += " \"";
			markh += S.AsAnsiString("DefType");
			markh += "\" ";
			// если участок поиска пересекается с отображаемым участком,
			// то выясняем его точки начала и конца
			int startX = S.AsInt("DefPoint") - S.AsInt("DefRadius");
			int finalX = S.AsInt("DefPoint") + S.AsInt("DefRadius");
			bool Include = true;
			if (startX < (start + zone_size))
			{
				if (startX > start)
					startMeas = CalcMeasFromRange((int)(startX - start));
				else
					startMeas = 0;
			}
			else
				Include = false;
			if (Include && (finalX > start))
			{
				if (finalX < (start + zone_size))
					finalMeas = CalcMeasFromRange((int)(finalX - start));
				else
					finalMeas = Chart1->Series[0]->Count();
			}
			else
				Include = false;
			// рисуем отрезки поиска
			if (Include)
			{
				double level;
				// Рисуем верхнюю границу
				if (S.AsInt("TopBorderPercent"))
				{
					AnsiString markhh = markh;
					markhh += S.AsInt("TopBorderPercent");
					markhh += "% от ";
					AnsiString mark = markhh;
					if (S.AsBool("isTopBrackBorder"))
					{
						level = levelOut1;
						mark += "верхн.пор.";
					}
					else
					{
						level = levelOut2;
						mark += "нижн.пор.";

					}
					double Border = level * S.AsInt("TopBorderPercent") / 100;
					SetBrackBorder(startMeas, finalMeas, Border,
						clFuchsia, mark);
					// Если включен внутренний фильтр продольника
					if (IsLinear && LinearFilterIn->IsFilter())
					{
						AnsiString mark = markhh;
						mark += "внутр.";
						if (S.AsBool("isTopBrackBorder"))
						{
							level = levelIn1;
							mark += "верхн.пор.";
						}
						else
						{
							level = levelIn2;
							mark += "нижн.пор.";
						}
						Border = level * S.AsInt("TopBorderPercent") / -100;
						SetBrackBorder(startMeas, finalMeas, Border,
							clFuchsia, mark);
					}
				}
				// Рисуем нижнюю границу
				if (S.AsInt("BottomBorderPercent"))
				{
					AnsiString markhh = markh;
					markhh += S.AsInt("BottomBorderPercent");
					markhh += "% от ";
					AnsiString mark = markhh;
					if (S.AsBool("isBottomBrackBorder"))
					{
						level = levelOut1;
						mark += "верхн.пор.";
					}
					else
					{
						level = levelOut2;
						mark += "нижн.пор.";
					}
					double Border =
						level * S.AsInt("BottomBorderPercent") / 100;
					SetBrackBorder(startMeas, finalMeas, Border, clBlue, mark);
					// Если включен внутренний фильтр продольника
					if (IsLinear && LinearFilterIn->IsFilter())
					{
						AnsiString mark = markhh;
						mark += "внутр.";
						if (S.AsBool("isBottomBrackBorder"))
						{
							level = levelIn1;
							mark += "верхн.пор.";
						}
						else
						{
							level = levelIn2;
							mark += "нижн.пор.";
						}
						Border = level * S.AsInt("BottomBorderPercent") / -100;
						SetBrackBorder(startMeas, finalMeas, Border,
							clBlue, mark);
					}
				}
			}
		}
		cbEtalonTubeDefects->ItemIndex = selectedDefect;
	}
}

// ---------------------------------------------------------------------------
int TFViewZoneD::CalcMeasFromRange(int _x)
{
	double Measure;
	int CurrentZoneMeasures;
	int StartOfZoneMeas = 0;
	int LastMeas = Chart1->Series[0]->Count();
	int zone_length = Singleton->Tube->Cross.ZoneLength;
	// Определяем конкретную зону (из 3)
	if ((_x > zone_length) && (DevidMeas1 > 0))
	{
		if ((_x > (2 * zone_length)) && (DevidMeas2 > 0))
		{
			StartOfZoneMeas = DevidMeas2;
			_x -= (2 * zone_length);
			CurrentZoneMeasures = LastMeas - DevidMeas2;
		}
		else
		{
			StartOfZoneMeas = DevidMeas1;
			_x -= zone_length;
			if (DevidMeas2 > DevidMeas1)
				CurrentZoneMeasures = DevidMeas2 - DevidMeas1;
			else
				CurrentZoneMeasures = LastMeas - DevidMeas1;
		}
	}
	else
		CurrentZoneMeasures = DevidMeas1;
	// окончательный расчет нужного измерения
	double x = _x;
	Measure = StartOfZoneMeas + x / zone_length * CurrentZoneMeasures;
	return (int)Measure;
}

// ---------------------------------------------------------------------------
void TFViewZoneD::SetBrackBorder(int _startMeas, int _finalMeas, double _Border,
	TColor _color, AnsiString _mark)
{
	Arrow->AddArrow(_startMeas, _Border, _finalMeas, _Border, "", _color);
	Mark->AddBubble(_startMeas + (_finalMeas - _startMeas) / 2, _Border, 5,
		_mark, _color);
}
// ---------------------------------------------------------------------------

void __fastcall TFViewZoneD::cbEtalonTubeDefectsKeyUp(TObject * Sender,
	WORD & Key, TShiftState Shift)
{
	if (Key != VK_ESCAPE)
	{
		cbEtalonTubeDefects->ItemIndex = curr_defect;
		KeyUpFlag = true;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TFViewZoneD::Chart1MouseMove(TObject * Sender,
	TShiftState Shift, int X, int Y)
{
	double dx, y;
	BarOut->GetCursorValues(dx, y);
	int x = (int)dx;
	AnsiString a;
	a += " [";
	a += x;
	a += ",";
	a += y;
	a += "]";

	bool mouse_in = true;
	if (x < 0)
		mouse_in = false;
	else if (x >= BarOut->MaxXValue())
		mouse_in = false;
	else if (y < Chart1->LeftAxis->Minimum)
		mouse_in = false;
	else if (y >= Chart1->LeftAxis->Maximum)
		mouse_in = false;
	if (mouse_on)
	{
		if (!mouse_in)
		{
			// Screen->Cursor=crDefault;
			mouse_on = false;
			StatusBar1->Panels->Items[0]->Text = "";
		}
	}
	else
	{
		if (mouse_in)
		{
			// Screen->Cursor=crCross;
			mouse_on = true;
		}

	}
	if (!mouse_on)
		return;
	int StartOfZone = (int)start;
	int CurrentZoneMeasures = Chart1->Series[0]->Count();
	int zone_length = Singleton->Tube->Cross.ZoneLength;
	if ((x > DevidMeas1) && (DevidMeas1 > 0))
	{
		StartOfZone += zone_length;
		if ((x > DevidMeas2) && (DevidMeas2 > 0))
		{
			StartOfZone += zone_length;
			x -= DevidMeas2;
			CurrentZoneMeasures = CurrentZoneMeasures - DevidMeas2;
		}
		else
		{
			x -= DevidMeas1;
			if (DevidMeas2 > DevidMeas1)
				CurrentZoneMeasures = DevidMeas2 - DevidMeas1;
			else
				CurrentZoneMeasures = CurrentZoneMeasures - DevidMeas1;
		}
	}
	else
	{
		CurrentZoneMeasures = DevidMeas1;
	}
	double Range = StartOfZone + x * zone_length / CurrentZoneMeasures;

	a = "";
	a += Range;
	a += "мм  ";
	a += (double)RoundTo(y, -1);
	a += "%";
	StatusBar1->Panels->Items[0]->Text = a;
}

// ---------------------------------------------------------------------------
void TFViewZoneD::Draw(CTube * _Tube, int _zone, int _sensor)
{
	Tube = _Tube;
	curr_zone = _zone;
	curr_sens = _sensor;
	Draw();
}

void TFViewZoneD::Draw()
{
	if (Tube == NULL)
		return;
	Clear();
	bool inner = Tp == CMeas::TP::Line && LinearFilterIn->IsFilter();
	SetInner(inner);
	CCrossLine* CL = (Tp == CMeas::TP::Cross) ? (CCrossLine*)&Tube->Cross :
		(CCrossLine*)&Tube->Line;
	int startZone;
	int finalZone;
	int lastZone = CL->Size() - 1;
	int initZone = curr_zone;
	if (initZone <= 0)
		initZone = 0;
	if (initZone >= lastZone)
		initZone = lastZone;
	if (initZone == 0)
		startZone = initZone;
	else
		startZone = initZone - 1;
	if (initZone == lastZone)
		finalZone = initZone;
	else
		finalZone = initZone + 1;
	int lastSens = CL->GetSensorsCount() - 1;
	int sensor = curr_sens;
	if (sensor < 0)
		sensor = 0;
	if (sensor > lastSens)
		sensor = lastSens;

	SetCurrPoint(initZone, sensor, false);
	SetCaption("Датчик " + IntToStr(sensor + 1) + ", зоны с " + (startZone + 1)
		+ " по " + (finalZone + 1));
	double lgain = CL->MSensor2[sensor]->Gain;
	for (int z = startZone; z <= finalZone; z++)
	{
		CZone* Z = CL->MZone[z];
		CSensor* S = Z->MSensor[sensor];
		for (int m = 0; m < S->Size(); m++)
		{
			double level = S->MMeas[m]->FilterOut * lgain;
			TColor color = Classer::ClassColor(level, CL->borders, S->MMeas[m]->Dead);
			AddOut(level, color);
			// if(z==0)
			// {
			// AnsiString a="[";
			// a+=m;
			// a+="] level=";
			// a+=level;
			// a+=" borders[0]=";
			// a+= CL->borders[0];
			// a+=" dead=";
			// a+=(M[m].Dead)?"true":"false";
			// a+=" color=";
			// a+=color;
			// pr(a);
			// }
			if (inner)
			{
				level = S->MMeas[m]->FilterIn * lgain;
				AddIn(level, Classer::ClassColor(level, CL->bordersIn,
					S->MMeas[m]->Dead));
			}
		}
	}
	AddDevider1(CL->MZone[startZone]->MSensor[sensor]->Size(), clBlue);
	if ((initZone < finalZone) && (initZone > startZone))
		AddDevider2(CL->MZone[startZone]->MSensor[sensor]->Size() +
		CL->MZone[finalZone - 1]->MSensor[sensor]->Size(), clBlue);
	else
		AddDevider2(0, clBlue);
	SetBorderOut1(CL->borders[0], Classer::ClassColor(CL->borders[0],
		CL->borders));
	if (CL->borders[1] != 0)
		SetBorderOut2(CL->borders[1], Classer::ClassColor(CL->borders[1],
		CL->borders));
	if (inner)
	{
		SetBorderIn1(CL->bordersIn[0], Classer::ClassColor(CL->bordersIn[0],
			CL->bordersIn));
		if (CL->bordersIn[1] != 0)
			SetBorderOut2(CL->bordersIn[1],
			Classer::ClassColor(CL->bordersIn[1], CL->bordersIn));
		SetZero();
	}

	/* TODO : Последняя зона плавающей длины */
	int lZoneLength = CL->MZone[0]->VZoneLength;
	SetMetric(startZone * lZoneLength,
		(finalZone - startZone + 1) * lZoneLength);
	if (PA("Defect.SOP.ViewEtalonCheck").Bool())
		ViewEtalonCheck();
	else
		Panel1->Visible = false;
}

void TFViewZoneD::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("TFViewZoneD: ") + _msg);
}
