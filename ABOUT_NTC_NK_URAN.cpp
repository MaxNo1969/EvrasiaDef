//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ABOUT_NTC_NK_URAN.h"
#include "IOUtils.hpp"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox1 *AboutBox1;
//--------------------------------------------------------------------- 
__fastcall TAboutBox1::TAboutBox1(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutBox1::OKButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox1::FormShow(TObject *Sender)
{
	TFile *f = new TFile();
	AnsiString sdate=f->GetLastWriteTime(Application->ExeName).FormatString("yyyymmdd");
	delete f;
	AnsiString programmer="A";

	DWORD dw;
	DWORD dwSize = GetFileVersionInfoSize(Application->ExeName.c_str(), &dw);

	char* pBuf = new char[dwSize];
	GetFileVersionInfo(Application->ExeName.c_str(), 0, dwSize, pBuf);
	VS_FIXEDFILEINFO* pvi;
	unsigned int l=sizeof(VS_FIXEDFILEINFO);
	VerQueryValue(pBuf, L"\\", (void**)(&pvi), &l);
	int serial=(pvi->dwFileVersionMS >> 16 ) & 0xffff;
	int global_version=(pvi->dwFileVersionMS >> 0 ) & 0xffff;
	int compile_number=(pvi->dwFileVersionLS >> 0 ) & 0xffff;
	delete (pBuf);

	AnsiString version="Версия: ";
	version+=serial;
	version+=".";
	version+=global_version;
	version+=".";
	version+=compile_number;
	version+=".";
	version+=sdate;
	version+=programmer;

	lVersion->Caption=version;

//	lCreationDate->Caption = "Дата сборки: " + 	f->GetLastWriteTime(Application->ExeName);
}
//---------------------------------------------------------------------------


