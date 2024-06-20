//---------------------------------------------------------------------------

#ifndef uTFViewCH
#define uTFViewCH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
#include <Menus.hpp>
#include "uTFRViewDev.h"
#include "uTFRViewLDev.h"
#include <vector>
#include "uFRViewZone.h"
#include "CTube.h"
using namespace std;

//---------------------------------------------------------------------------

class TFViewC : public TForm
{
__published:	// IDE-managed Components
	TComboBox *CBStep;
	TLabel *Label1;
	TFRViewDev *FRViewDevC;
	TFRViewLDev *FRViewLDevC;
	void __fastcall EditKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ViewCrossChartKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall CBStepChange(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);


private:	// User declarations
	void  ViewFormInit();				// инициализация формы
	int CrossPos;						//Начальная позиция Поперечного
	int LinePos;						//Начальная позиция Продольного
	TColor SelectedColor;                  //Цвет выделеной зоны
	bool GainEnable;
	bool inited;
	void GainChangeC(int _sensor,double _gain);
	int lsensors_a;
	void Calibrate(TFRViewZone* _arc);
	int max_zones;
	int RangeIndex(double _val);
	double RangeValue();
	CTube* Tube;
	int CSensors;
	void CrossMove(int _pos);
public:		// User declarations
	__fastcall TFViewC(TComponent* Owner,CTube* _Tube);
	bool need_repaint;
};
//---------------------------------------------------------------------------
extern PACKAGE TFViewC *FViewC;
//---------------------------------------------------------------------------
#endif


