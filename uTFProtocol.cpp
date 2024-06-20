#include <vcl.h>
#pragma hdrstop
#include "uTFProtocol.h"
#include "uFunctions.h"
#include "PA.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TFProtocol *FProtocol;

//---------------------------------------------------------------------------
__fastcall TFProtocol::TFProtocol(TComponent* Owner, TCriticalSection* _cs) :
	TForm(Owner)
{
	cs = _cs;
	block_SetFile=true;
}
//---------------------------------------------------------------------------

void __fastcall TFProtocol::FormCreate(TObject *Sender)
{
	PA pa("Defect.Some.Protocol");
	L = new TStringList();
	Timer1->Interval = pa.Item("Period").Int();
	PA("Defect.Wins").LoadFormPos(this);
	cbProtocolToFile->Checked = pa.Item("IsFile").Bool();
	file=NULL;
	ByDay=pa.Item("ByDay").Bool();
	block_SetFile=false;
	SetFile();
	if (pa.Item("IsVisible").Bool())
		Show();
	Timer1->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TFProtocol::FormDestroy(TObject *Sender)
{
	Timer1->Enabled = false;
	fclose(file);
	delete L;
}

void TFProtocol::Save(void)
{
	PA("Defect.Wins").SaveFormPos(this);
	PA pa("Defect.Some.Protocol");
	pa.Item("IsFile").Write(cbProtocolToFile->Checked);
	pa.Item("IsVisible").Write(Visible);
}

//---------------------------------------------------------------------------
void TFProtocol::Add(AnsiString _msg)
{
	L->Add(_msg);
}

void __fastcall TFProtocol::Timer1Timer(TObject *Sender)
{
	TTimer* s = (TTimer*)Sender;
	s->Enabled = false;
	cs->Enter();
	{

		for (int i = 0; i < L->Count; i++)
		{
			AnsiString a = L->Strings[i];
			if (Visible)
				mProtocol->Lines->Add(a);
			if (cbProtocolToFile->Checked)
			{
				fprintf(file, a.c_str());
				fprintf(file, "\n");
			}
		}
		if (cbProtocolToFile->Checked && L->Count > 0)
			fflush(file);
		L->Clear();
	} cs->Leave();
	s->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFProtocol::FormResize(TObject *Sender)
{
	cs->Enter();
	{
		mProtocol->Width = ClientWidth - mProtocol->Left * 2;
		mProtocol->Height = ClientHeight - mProtocol->Top - mProtocol->Left;
	} cs->Leave();
}

void __fastcall TFProtocol::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key != 27)
		return;
	cs->Enter();
	{
		Close();
	} cs->Leave();
}

void TFProtocol::DateTimeMark(AnsiString _msg)
{
	AnsiString mark = _msg;
	TDateTime now = Now();
	mark += now.FormatString("dd");
	mark += "/";
	mark += now.FormatString("mm");
	mark += "/";
	mark += now.FormatString("yyyy");
	mark += " ";
	mark += now.FormatString("hh:mm:ss");
	L->Add(mark);
}

void TFProtocol::DateTimeMark(void)
{
	DateTimeMark(AnsiString(""));
}

void TFProtocol::SetFile()
{
	if(block_SetFile)
		return;
	if(file!=NULL)
	{
		fclose(file);
		L->Add("Закрыли протокол");
	}
	file=NULL;
	if (cbProtocolToFile->Checked)
	{
		if(file!=NULL)
			fclose(file);
		AnsiString fname = "..\\..\\Protocols\\pr";
		TDateTime now = Now();
		fname += Now().FormatString("dd");
		fname += ".";
		fname += Now().FormatString("mm");
		fname += ".";
		fname += Now().FormatString("yyyy");
		if (!ByDay)
		{
			fname += "_";
			fname += Now().FormatString("hh.mm.ss");
		}
		fname += ".txt";

		file = fopen(fname.c_str(), "a");
		if (file == NULL)
		{
			CreateDirectoryW(L"..\\..\\Protocols", 0);
			file = fopen(fname.c_str(), "a");
		}
		L->Add(AnsiString("Открыли протокол: ")+fname);
	}
}
void __fastcall TFProtocol::cbProtocolToFileClick(TObject *Sender)
{
	SetFile();
}
//---------------------------------------------------------------------------

