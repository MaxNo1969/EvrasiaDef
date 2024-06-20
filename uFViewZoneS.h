//---------------------------------------------------------------------------

#ifndef uFViewZoneSH
#define uFViewZoneSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.ArrowCha.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include "CTube.h"
#include <VclTee.TeeGDIPlus.hpp>
//#include <VclTee.TeeGDIPlus.hpp>

//---------------------------------------------------------------------------
class TFViewZoneS : public TForm
{
__published: //IDE-managed Components

	TChart *Chart1;
	TStatusBar *StatusBar1;
	TSpeedButton *SBSource;
	TSpeedButton *SBMedian;
	TSpeedButton *SBFilterOut;
	TLineSeries *Series1;
	TLineSeries *Series2;
	TLineSeries *Series3;
	TLineSeries *Series4;
	TSpeedButton *SBFilterIn;
	TLineSeries *Out10;
	TLineSeries *Out11;
	TLineSeries *Out20;
	TLineSeries *Out21;
	TLineSeries *In10;
	TLineSeries *In11;
	TLineSeries *In20;
	TLineSeries *In21;

	void __fastcall FormKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Chart1ClickBackground(TCustomChart *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall SBSourceClick(TObject *Sender);
	void __fastcall SBMedianClick(TObject *Sender);
	void __fastcall SBFilterOutClick(TObject *Sender);
	void __fastcall SBFilterInClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private: //User declarations

	AnsiString title;
	double start;
	double zone_size;
	void SetBorder(TLineSeries* _series, double _level, TColor _color);
	void BorderVisible(AnsiString _mark, bool _v);

	int curr_zone;
	int curr_sens;
	CMeas::TP Tp;
	void Draw(void);
	CTube* Tube;
	inline void AddSource(double _level)
	{
		Chart1->Series[0]->AddY(_level);
	};

public: //User declarations

	__fastcall TFViewZoneS(TComponent* Owner, CMeas::TP _Tp, AnsiString _title);
	void SetCaption(AnsiString _cap);
	void Clear(void);
	void SetMetric(double _start, double _zone_size);

//	inline void AddSource(double _level)
//	{
//		Chart1->Series[0]->AddY(_level);
//	};

	inline void AddMedian(double _level)
	{
		Chart1->Series[1]->AddY(_level);
	};

	inline void AddFilteredOut(double _level)
	{
		Chart1->Series[2]->AddY(_level);
	};

	inline void AddFilteredIn(double _level)
	{
		Chart1->Series[3]->AddY(_level);
	};

	inline void SetBorderOut1(double _level, TColor _color)
	{
		SetBorder(Out10, _level, _color);
		SetBorder(Out11, -_level, _color);
	}

	inline void SetBorderOut2(double _level, TColor _color)
	{
		SetBorder(Out20, _level, _color);
		SetBorder(Out21, -_level, _color);
	}

	inline void SetBorderIn1(double _level, TColor _color)
	{
		SetBorder(In10, _level, _color);
		SetBorder(In11, -_level, _color);
	}

	inline void SetBorderIn2(double _level, TColor _color)
	{
		SetBorder(In20, _level, _color);
		SetBorder(In21, -_level, _color);
	}
	void Draw(CTube* _Tube, int _zone, int _sensor);
};
#endif
