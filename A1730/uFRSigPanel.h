// ---------------------------------------------------------------------------

#ifndef uFRSigPanelH
#define uFRSigPanelH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "Signal.h"

// ---------------------------------------------------------------------------
class TFRSigPanel : public TFrame
{
__published: // IDE-managed Components

	TPanel *Panel1;

private: // User declarations

public: // User declarations

	CSignal* signal;
	__fastcall TFRSigPanel(TComponent* Owner, CSignal* _signal);
	void CheckSignal(void);
	void ByHint(bool _val);
};

// ---------------------------------------------------------------------------
extern PACKAGE TFRSigPanel *FRSigPanel;
// ---------------------------------------------------------------------------
#endif
