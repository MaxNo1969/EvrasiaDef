//---------------------------------------------------------------------------

#ifndef uTFRSensorsCLH
#define uTFRSensorsCLH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uTFRSensors.h"
#include <Buttons.hpp>
#include "LCardChGroup.h"

//---------------------------------------------------------------------------
class TFRSensorsCL : public TFrame
{
__published: //IDE-managed Components

	TFRSensors *FRCross;
	TFRSensors *FRLine;

private: //User declarations
	LCardChGroup* Cross;
	LCardChGroup* Line;

public: //User declarations

	__fastcall TFRSensorsCL(TComponent* Owner);
	void Init(LCardChGroup* _Cross, LCardChGroup* _Line);
	void Save(void);
	void SetEnabledR(bool _v);
};

//---------------------------------------------------------------------------
extern PACKAGE TFRSensorsCL *FRSensorsCL;
//---------------------------------------------------------------------------
#endif
