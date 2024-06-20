// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uTFRSG.h"
#include "uCExecSQL.h"
#include "protocol.h"
#include "uCSelect.h"
#include "PA.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRSG *FRSG;

// ---------------------------------------------------------------------------
__fastcall TFRSG::TFRSG(TComponent* Owner) : TFrame(Owner)
{
	Clear();
	Edit1->Visible = false;
	pSolidGroup->Visible = true;
	block = true;
	OnChange = NULL;
}

// ---------------------------------------------------------------------------
void TFRSG::Init()
{
	LoadSettings();
}

// ---------------------------------------------------------------------------
void TFRSG::LoadSettings(void)
{
	CheckBox2->Checked = PA("Defect.Work.IsWorkSG").Bool();
	CheckBox1->Checked = PA("Defect.SolidGroup.IsFix").Bool();
	Edit1->Text = PA("Defect.SolidGroup.GroupFix").String();
	if (CheckBox1->Checked)
	{
		Edit1->Visible = true;
		pSolidGroup->Visible = false;
	}
	else
	{
		Edit1->Visible = false;
		pSolidGroup->Visible = true;
	}
	block = false;
}

// ---------------------------------------------------------------------------
void TFRSG::Set(AnsiString _SolidGroup, TColor _SolidGroupColor)
{
	pSolidGroup->Caption = _SolidGroup;
	pSolidGroup->Color = _SolidGroupColor;
}

// ---------------------------------------------------------------------------
void TFRSG::Clear()
{
	pSolidGroup->Caption = "";
	pSolidGroup->Color = clBtnFace;
}

// ---------------------------------------------------------------------------
void TFRSG::CopyFrom(TFRSG* _th)
{
	pSolidGroup->Caption = _th->pSolidGroup->Caption;
	pSolidGroup->Color = _th->pSolidGroup->Color;
}

// ---------------------------------------------------------------------------
void __fastcall TFRSG::CheckBox1Click(TObject *Sender)
{
	TCheckBox* s = (TCheckBox*)Sender;
	if (s->Checked)
	{
		Edit1->Visible = true;
		pSolidGroup->Visible = false;
	}
	else
	{
		Edit1->Visible = false;
		pSolidGroup->Visible = true;
	}
	Save();
}

// ---------------------------------------------------------------------------
void TFRSG::Save(void)
{
	if (block)
		return;
	PA("Defect.Work.IsWorkSG").Write(CheckBox2->Checked);
	PA("Defect.SolidGroup.IsFix").Write(CheckBox1->Checked);
	PA("Defect.SolidGroup.GroupFix").Write(Edit1->Text);
	if (OnChange != NULL)
		OnChange(CheckBox1->Checked, Edit1->Text);
}

// ---------------------------------------------------------------------------
void __fastcall TFRSG::Edit1Change(TObject *Sender)
{
	Save();
}

// ---------------------------------------------------------------------------
AnsiString TFRSG::GetFix(void)
{
	if (CheckBox1->Checked)
		return (Edit1->Text);
	else
		return ("");
}

// ---------------------------------------------------------------------------
void TFRSG::Set(SGR::SG _sg)
{
	pSolidGroup->Caption = _sg.group;
	pSolidGroup->Color = _sg.color;
}
// ---------------------------------------------------------------------------

void __fastcall TFRSG::CheckBox2Click(TObject *Sender)
{
	Save();
	// PA("Defect.Work.IsWorkSG").Write(CheckBox2->Checked);
}

// ---------------------------------------------------------------------------
AnsiString TFRSG::SGGroup(void)
{
	if (IsFix())
		return (Edit1->Text);
	if (!IsSG())
		return (NULL);
	return (pSolidGroup->Caption);
}
