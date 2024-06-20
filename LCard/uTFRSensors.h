//---------------------------------------------------------------------------

#ifndef uTFRSensorsH
#define uTFRSensorsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "LCardChGroup.h"
#include "uTFRSensor.h"
//---------------------------------------------------------------------------
class TFRSensors : public TFrame
{
__published:	// IDE-managed Components
	TGroupBox *gSensors;
private:	// User declarations
	LCardChGroup* channels;
	void SetAll(TFRSensor* _p);
public:		// User declarations
	__fastcall TFRSensors(TComponent* Owner);
	void Init(LCardChGroup* _channels);
	void Save(void);
	void SetEnabledR(bool _v);
};
//---------------------------------------------------------------------------
extern PACKAGE TFRSensors *FRSensors;
//---------------------------------------------------------------------------
#endif
