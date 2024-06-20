// ---------------------------------------------------------------------------

#ifndef uTFRViewDevH
#define uTFRViewDevH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFRViewZone.h"

// ---------------------------------------------------------------------------
class TFRViewDev : public TFrame
{
__published: // IDE-managed Components
	void __fastcall FrameResize(TObject *Sender);

private: // User declarations
	void GainChange(int _sensor, double _gain);
	void Calibrate(TFRViewZone* _arc);
	void FOnCalibrateWrite(TFRViewZone::OnCalibrateDef _v);
	void FOnChangeGainWrite(TFRViewZone::OnChangeGainDef _v);

public: // User declarations
	__fastcall TFRViewDev(TComponent* Owner);
	void Init(CTube* _Tube, CMeas::TP _Tp, bool _check_visible);
	void SetStep(double _step);
	void Draw(int _zone);
	__property TFRViewZone::OnCalibrateDef OnCalibrate =
	{write = FOnCalibrateWrite};
	__property TFRViewZone::OnChangeGainDef OnChangeGain =
	{write = FOnChangeGainWrite};
	bool NeedCalibrate(int _sensor);
	void SetInner(bool _v);
};

// ---------------------------------------------------------------------------
extern PACKAGE TFRViewDev *FRViewDev;
// ---------------------------------------------------------------------------
#endif
