// --------------------------------------------------------------------------
#pragma hdrstop
#include <vcl.h>
#include <dir.h>
#include <Classes.hpp>
#include <time.h>

#include "Main.h"
#include "uFSignalsState.h"
#include "uFunctions.h"
#include "Singleton.h"
#include "uTFViewC.h"
#include "ABOUT_NTC_NK_URAN.h"
#include "SignalListDef.h"
#include "uCDBS.h"
#include "uCExecute.h"
#include "uCExecSQL.h"
#include "uCSelect.h"
#include "ThTest.h"
#include "SMSM.h"
#include "Protocol.h"
#include "TSChangeWarning.h"
#include "uTFSOPR.h"
#include "ThWork.h"
#include "Filters.h"

#include "uTFTest502.h"
#include "PA.h"
#include "MitFX.h"
#include "MainTest.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

//#pragma link "TeeGDIPlus"
//#pragma link "Chart"
//#pragma link "TeEngine"
//#pragma link "TeeProcs"
//#pragma link "Series"
//#pragma link "Chart"
#pragma link "uTFRBorders"
#pragma link "uTFRSum"
//#pragma link "TeCanvas"
#pragma link "uFRStatist"
#pragma link "uTFRButtons"
#pragma link "uTFRCross"
#pragma link "uTFRLineRemote"
#pragma link "uTFRSG"
#pragma link "uTFRSOP"
#pragma link "uTFRSplit"
#pragma link "uTFRSumM"
#pragma link "uTFRThick"
#pragma resource "*.dfm"

TMainForm *MainForm;

__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner), winWork(this)
{
}

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	pr("Начали");
	PA pa("Defect");
	PA("Defect.Wins").LoadFormPos(this);
	title_prefix = "«БУРАН®5000» №1750 Установка неразрушающего контроля";
	user = "";
	client = "";
	DBS = new CDBS();

	SLD = new SignalListDef();
	FSignalsState = new TFSignalsState(this, SLD);
	SLD->oTPCHPOW->Set(true);

	if (pa.Item("Some.SignalsVisible").Bool())
		FSignalsState->Show();
	DragAcceptFiles(Handle, true); // Разрешаем перетаскивание файлов

	bool RHKret = RegisterHotKey(Handle,
		// Handle окна, которому отправлять сообщения WM_HOTKEY
		0x00E, // УСЛОВНЫЙ идентификатор горячего ключа
		0, // модификатор
		VK_F1); // код клавиши

	bool RHKret1 = RegisterHotKey(Handle,
		// Handle окна, которому отправлять сообщения WM_HOTKEY
		0x00A, // УСЛОВНЫЙ идентификатор горячего ключа
		MOD_ALT + MOD_CONTROL, // модификатор
		VK_ADD); // код клавиши

	FRSplit1->Init(1, FRThick1, FRThick1->MinHeight(), FRCross1,
		FRCross1->MinHeight());
	FRSplit2->Init(2, FRCross1, FRCross1->MinHeight(), FRLine1,
		FRLine1->MinHeight());
	FRSplit3->Init(3, FRLine1, FRLine1->MinHeight(), FRSumM1,
		FRSumM1->MinHeight());
	prevHeight = Height;

	int space = 3;
	FRCross1->Left = 0;
	FRLine1->Left = FRCross1->Left;
	FRThick1->Left = FRCross1->Left;
	FRSumM1->Left = FRCross1->Left;

	FormResize(Sender);
	KeyPreview = true;

	CrossFilter = new Filters("Cross");
	LinearFilterOut = new Filters("Line");
	LinearFilterIn = new Filters("LineIn");

	Singleton = new CSingleton(this);

	FRCross1->Init();
	FRLine1->Init();
	FRThick1->Init();
	FRSumM1->Init();
	FRStatist1->Init();
	FRSG1->Init();
	// FRSum1->OnDecision=NULL;

	FRThick1->OnChange = Post;
	FRCross1->OnChange = Post;
	FRLine1->OnChange = Post;
	FRSumM1->OnChange = Post;

	FRSOP1->Init();
	bank = new Bank();
	LoadSettings();

	PA ppp = pa.Item("Some.IsInterruptView");
	cbInterruptView->Checked = pa.Item("Some.IsInterruptView").Bool();
	UnicodeString s = "Main ";
	TThread::CurrentThread->NameThreadForDebugging(s);
	SMSM::Init(Handle);
	thread_msg = SMSM::GetMsgId();

	// SLD->oPCHPOW->Set(true);
	// SLD->oPCHPOW_R->Set(true);
	ClearCharts();

	FRButtons1->ROnClick = OnClickButton;
	thCurrent = NULL;
	Caption = title_prefix;

	signalServer = new SignalServer();
	FRButtons1->SBView->Enabled = false;
	FRButtons1->SBSOP->Enabled = false;
	acs = NULL;
	winWork.Init();
}

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
	delete signalServer;
	if (thCurrent != NULL)
	{
		if (thCurrent->GetName() == "ThWork")
			thCurrent->Terminate();
		thCurrent->WaitFor();
		delete thCurrent;
	}
	DragAcceptFiles(Handle, false); // Запрещаем перетаскивание файлов
//	throw;

	// SLD->oPCHPOW->Set(false);

	// запись дефолтного всего
	PA pa("Defect");
	pa.Item("Some.IsInterruptView").Write(cbInterruptView->Checked);

	UnregisterHotKey(Handle, // Handle окна
		0x00E); // наш идентификатор горячего ключа
	UnregisterHotKey(Handle, // Handle окна
		0x00A); // наш идентификатор горячего ключа
	SLD->oTPCHPOW->Set(false);
//	throw;
	delete Singleton;
	pa.Item("Some.SignalsVisible").Write(FSignalsState->Visible);
	delete FSignalsState;
//	throw;

	PA("Defect.Wins").SaveFormPos(this);
	TPr::Dispose();
	delete bank;
	FRSplit1->Save();
	FRSplit2->Save();
	FRSplit3->Save();
	delete DBS;
	if (acs != NULL)
		delete acs;
//	delete SLD;
	PA::Dispose();
}

void __fastcall TMainForm::FormResize(TObject *Sender)
{
	int space = 3;

	FRSplit1->Left = 0;
	FRSplit1->Width = ClientWidth;
	FRSplit2->Left = 0;
	FRSplit2->Width = ClientWidth;
	FRSplit3->Left = 0;
	FRSplit3->Width = ClientWidth;
	Panel4->Left = 0;
	Panel4->Width = ClientWidth;
	FRCross1->Width = ClientWidth - FRCross1->Left - space;
	FRLine1->Width = FRCross1->Width;
	FRThick1->Width = FRCross1->Width;
	FRSumM1->Width = FRCross1->Width;

	int p4 = Panel4->Height + Panel4->Height;
	double t = Height - p4;
	t /= prevHeight - p4;

	FRSplit1->Top = (int)(((double)FRSplit1->Top - p4) * t) + p4;
	FRSplit2->Top = (int)(((double)FRSplit2->Top - p4) * t) + p4;
	FRSplit3->Top = (int)(((double)FRSplit3->Top - p4) * t) + p4;

	FRThick1->Top = Panel4->Top + Panel4->Height;
	FRThick1->Height = FRSplit1->Top - FRThick1->Top;

	FRCross1->Top = FRSplit1->Top + FRSplit1->Height;
	FRCross1->Height = FRSplit2->Top - FRCross1->Top;

	FRLine1->Top = FRSplit2->Top + FRSplit2->Height;
	FRLine1->Height = FRSplit3->Top - FRLine1->Top;

	FRSumM1->Top = FRSplit3->Top + FRSplit3->Height;
	FRSumM1->Height = ClientHeight - FRSumM1->Top;

	StatusBarTop->Width = ClientWidth - StatusBarTop->Left;

	FRStatist1->Left = ClientWidth - FRStatist1->Width - space;
	cbInterruptView->Left = ClientWidth - cbInterruptView->Width - space;
#ifdef RADOP
	FRSG1->Left = ClientWidth - FRSG1->Width - space;
#endif
	prevHeight = Height;
}

void TMainForm::Post(void)
{
	Singleton->FromFile = true;
	SMSM::SetPost("LoadSettings");
}

void TMainForm::ClearCharts(void)
{
	pr("ClearCharts()");
	Singleton->Clear();
	FRCross1->Clear();
	FRLine1->Clear();
	FRThick1->Clear();
	FRSumM1->Clear();
	FRSG1->Clear();
	Refresh();
	isView = false;
}

void TMainForm::LoadSettings(void)
{
	pr("LoadSettings");
	CrossFilter->LoadSettings();
	LinearFilterIn->LoadSettings();
	LinearFilterOut->LoadSettings();
	bank->LoadSettings();
	FRCross1->LoadSettings();
	FRLine1->LoadSettings();
	FRThick1->LoadSettings();
	FRSumM1->LoadSettings();
	Singleton->LoadSettings();
	FSignalsState->LoadSettings();
	Label1->Caption = AnsiString("Типоразмер: ") + PA("TSSet.Current.Name")
		.String();
	IsAuto = PA("Defect.Some.IsAuto").Bool();
}

void TMainForm::OnLoadSettings(void)
{
	LoadSettings();
	Singleton->Tube->Calc();
	ReDraw();
}

void __fastcall TMainForm::menuSignalsStateClick(TObject *Sender)
{
	FSignalsState->Show();
}

void __fastcall TMainForm::menuSaveTubeClick(TObject *Sender)
{
	user = PA("Users.CurrentUser.Name").String();
	if (SaveToFileDialog->Execute())
		Singleton->Save(SaveToFileDialog->FileName, user);
}

void __fastcall TMainForm::menuLoadTubeClick(TObject *Sender)
{
	if (OpenDialogFromFile->Execute())
	{
		ClearCharts();
		isView = Singleton->Load(OpenDialogFromFile->FileName);
		ReDraw();
		FRButtons1->SBView->Enabled = true;
		FRButtons1->SBSOP->Enabled = true;
	}
}

void __fastcall TMainForm::menuTestAdvantechClick(TObject *Sender)
{
	// закрывает прогу и вызывает прогу с управлением Выходами платы Advantech
	ShellExecute(0, L"open", L"..\\..\\Settings\\IO_Management.exe", 0, 0,
		SW_SHOWNORMAL);
}

void __fastcall TMainForm::menuProtocolClick(TObject *Sender)
{
	TPr::Show();
}

void __fastcall TMainForm::N1Click(TObject *Sender)
{
	TAboutBox1* f = new TAboutBox1(this);
	f->ShowModal();
	delete f;
}

void TMainForm::UpdateStatus(AnsiString _text1, AnsiString _text2)
{
	StatusBarTop->Panels->Items[0]->Text = _text1;
	StatusBarTop->Panels->Items[1]->Text = _text2;
	StatusBarTop->Refresh();
}

void TMainForm::ReDraw(void)
{
	if (!isView)
		return;
	FRCross1->Draw(Singleton->Tube);
	FRLine1->Draw(Singleton->Tube);
	FRThick1->Draw(Singleton->Tube);
	FRSumM1->Draw(Singleton->Tube);
}

void TMainForm::SetAbleButtons(bool state)
{
	FRLine1->SetEnabledR(state);
	FRCross1->SetEnabledR(state);
	FRThick1->SetEnabledR(state);
	FRSumM1->SetEnabledR1(state);

	ActionManager1->FindItemByCaption("Настройка")->Visible = state;
	ActionManager1->FindItemByCaption("Труба")->Visible = state;
	ActionManager1->FindItemByCaption("Диагностика")->Visible = state;
	// ActionManager1->FindItemByCaption("Группа прочности")->Visible = state;
	ActionManager1->FindItemByCaption("Помощь")->Visible = state;
	ActionManager1->FindItemByCaption("Контроль СОП")->Visible = state;

}

void __fastcall TMainForm::Action25Execute(TObject *Sender)
{
	user = PA("Users.CurrentUser.Name").String();
	client = PA("Clients.Current.Name").String();
	AnsiString lGroup = PA("Users.CurrentUser.Group").String();
	TFSOPR* f = new TFSOPR(this, user, lGroup);
	f->ShowModal();
	bool need_reload = f->need_reload;
	delete f;
	if (need_reload)
		FRSOP1->Load();
}

void TMainForm::ChangeDecision(void)
{
	if (Singleton->Tube->RSum.DClass == 0)
		Singleton->Tube->RSum.DClass = 2;
	else
		Singleton->Tube->RSum.DClass = 0;
	FRSumM1->Draw(Singleton->Tube);
}

void __fastcall TMainForm::Action27Execute(TObject *Sender)
{
	int hhh = (ClientHeight - Panel4->Top - Panel4->Height -
		FRSplit1->Height * 3) / 5;

	FRThick1->Top = Panel4->Top + Panel4->Height;
	FRThick1->Height = hhh * 2;

	FRSplit1->Top = Panel4->Top + Panel4->Height + FRThick1->Height;

	FRCross1->Top = FRSplit1->Top + FRSplit1->Height;
	FRCross1->Height = hhh;

	FRSplit2->Top = FRCross1->Top + FRCross1->Height;

	FRLine1->Top = FRSplit2->Top + FRSplit2->Height;
	FRLine1->Height = hhh;

	FRSplit3->Top = FRLine1->Top + FRLine1->Height;

	FRSumM1->Top = FRSplit3->Top + FRSplit3->Height;
	FRSumM1->Height = hhh;
	prevHeight = Height;
}

IsWork TMainForm::GetIsWork(void)
{
	IsWork IW;
	IW.Cross = FRCross1->IsCross();
	IW.Line = FRLine1->IsLinear();
	IW.Thick = FRThick1->IsThick();
	IW.SG = FRSG1->IsSG();
	return (IW);
}

void TMainForm::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("Main: ") + _msg);
}

void TMainForm::StartWorkSOP(AnsiString _button)
{
	if (thCurrent != NULL)
		FATAL("Повторный запуск");
	AnsiString title = title_prefix;
	title += " Оператор ";
	title += user;
	title += ", Заказчик ";
	title += client;
	Caption = title;
	SetAbleButtons(false);
	FRSumM1->OnDecision = NULL;
	TPr::Clear();
	WasSOP = _button == "СОП";
	IW = GetIsWork();
	user = PA("Users.CurrentUser.Name").String();
	client = PA("Clients.Current.Name").String();
	FRSumM1->SetEnabledResult(false);
	FRButtons1->SBView->Enabled = false;
	FRButtons1->SBSOP->Enabled = false;
	thCurrent = new ThWork(IW, bank);
}

void __fastcall TMainForm::ApplicationEventsMessage(tagMSG &Msg, bool &Handled)
{
	if (Msg.message == WM_HOTKEY)
	{ // сообщение наше
		if (Msg.wParam == 0x00E) // идентификатор наш
		{
			// WinExec("hh ..\\..\\help\\Help.chm", SW_RESTORE);
			Handled = true;
			return;
		}
		else if (Msg.wParam == 0x00A) // идентификатор наш
		{
			Handled = true;
			return;
		}
	}
	if (Msg.message == thread_msg)
	{
		DoThreadMessage();
		Handled = true;
		return;
	}
}

void TMainForm::OnClickButton(AnsiString _button)
{
	pr(AnsiString("OCB: ") + _button);
	if (_button == "Test")
	{
		pr("OCB: Test");
		SetAbleButtons(false);
		TPr::Clear();
		// pipeSender.NewTube();
		thCurrent = new ThTest(bank);
	}
	else if (_button == "View")
	{
		if (!isView)
			return;
		TFViewC* f = new TFViewC(this, Singleton->Tube);
		f->ShowModal();
		bool need_repaint = f->need_repaint;
		delete f;
		if (need_repaint)
			OnLoadSettings();
	}
	else if (_button == "Manage")
	{
		TFTest502* f = new TFTest502(this);
		f->ShowModal();
		delete f;
	}
	else if (_button == "Cancel")
	{
		if (thCurrent != NULL)
		{
			thCurrent->Terminate();
			thCurrent->WaitFor();
			thCurrent == NULL;
		}
		SetAbleButtons(true);
	}
	else if (_button == "Work")
		StartWorkSOP(_button);
	else if (_button == "СОП")
	{
		AnsiString file_name = PA("Defect.Some.SOPPath").String();
		file_name += "\\СОП ";
		file_name += PA("TSSet.Current.Name").String();
		file_name += " ";
		time_t t;
		time(&t);
		tm ltm = *localtime(&t);
		file_name.cat_printf("%.4d%.2d%.2d %.2d%.2d.bindkb", 1900 + ltm.tm_year,
			ltm.tm_mon + 1, ltm.tm_mday, ltm.tm_hour, ltm.tm_min);
		WideString w = AnsiString("Сохранить СОП: " + file_name);
		if (Application->MessageBoxW(w.c_bstr(), L"Сохранение СОП",
			MB_ICONQUESTION | MB_OKCANCEL) == mrOk)
		{
			TPr::pr(file_name);
			user = PA("Users.CurrentUser.Name").String();
			Singleton->Save(file_name, user);
			FRButtons1->SBSOP->Enabled = false;

		}
	}
	else if (_button == "ReStart")
	{
		FRStatist1->Add(Singleton->Tube->RSum.DClass == 0);
		SLD->oRESULT->Set(Singleton->Tube->RSum.DClass != 0);
		SLD->oSTROBE->Set(true);
		SLD->oSHIFT->Set(true);
		Sleep(500);
		if (!WasSOP)
		{
			Singleton->SaveTubeToDB(user, client, FRSG1->SGGroup());
			Singleton->Save(user);
		}
		if (IsAuto)
		{
			SetAbleButtons(false);
			FRSumM1->OnDecision = NULL;
			TPr::Clear();
			IW = GetIsWork();
			user = PA("Users.CurrentUser.Name").String();
			client = PA("Clients.Current.Name").String();
			FRSumM1->SetEnabledResult(false);
			FRButtons1->SBView->Enabled = false;
			FRButtons1->SBSOP->Enabled = false;
			thCurrent = new ThWork(IW, bank);
		}
		else
		{
			SetAbleButtons(true);
			FRButtons1->Enable();
        }
	}
}

void TMainForm::AddResultZone(void)
{
	for (int i = 0; i < Singleton->Tube->RSum.Size(); i++)
		bank->AddResultZone(i, Singleton->Tube->RSum.MZone[i]->DClass > 0);
}

void TMainForm::DoThreadMessage(void)
{
	for (; ;)
	{
		AnsiString post_name;
		bool Ok;
		AnsiString msg = SMSM::GetPost(&post_name, &Ok);
		if (!Ok)
			return;
		// AnsiString a = "DTM: ";
		// a += msg;
		// if (post_name != "?")
		// {
		// a += " | ";
		// a += post_name;
		// }
		// pr(a);
		if (msg == "LoadSettings")
#pragma region
			OnLoadSettings();
#pragma end_region
		else if (msg == "REDRAW CROSS")
#pragma region
		{
			bool need_draw = false;
			for (; ;)
			{
				BankZoneData2 z = bank->GetNextCrossZone(false);
				if (!z.Ok)
					break;
				need_draw = true;
				pr(z.ToString());
				Singleton->Tube->Cross.AddZone(&z);
			}
			if (need_draw)
			{
				FRCross1->Draw(Singleton->Tube);
				Singleton->Tube->CalcSum();
				Singleton->Tube->RSum.MakeDecision();
				FRSumM1->Draw(Singleton->Tube);
				AddResultZone();

				AnsiString a = "Перерисовали cross, зон ";
				a += Singleton->Tube->Cross.MZone.Count();
				a += " ";
				a += GetTickCount();
				pr(a);
			}
		}
#pragma end_region
		else if (msg == "REDRAW LINE")
#pragma region
		{
			bool need_draw = false;
			for (; ;)
			{
				BankZoneData z = bank->GetNextLineZone(false);
				if (!z.Ok)
					break;
				need_draw = true;
				pr(z.ToString());
				Singleton->Tube->Line.AddZone(&z);
			}
			if (need_draw)
			{
				FRLine1->Draw(Singleton->Tube);
				Singleton->Tube->CalcSum();
				Singleton->Tube->RSum.MakeDecision();
				FRSumM1->Draw(Singleton->Tube);
				AddResultZone();
				AnsiString a = "Перерисовали line, зон ";
				a += Singleton->Tube->Line.MZone.Count();
				a += " ";
				a += GetTickCount();
				pr(a);
			}
		}
#pragma end_region
		else if (msg == "REDRAW THICK")
#pragma region
		{
			bool need_draw = false;
			for (; ;)
			{
				BankZoneVal z = bank->GetNextThickZone(false);
				if (!z.Ok)
					break;
				need_draw = true;
				pr(z.ToString());
				Singleton->Tube->Thick.AddZone(&z);
			}
			if (need_draw)
			{
				FRThick1->Draw(Singleton->Tube);
				Singleton->Tube->CalcSum();
				Singleton->Tube->RSum.MakeDecision();
				FRSumM1->Draw(Singleton->Tube);
				AddResultZone();
				AnsiString a = "Перерисовали Tick, зон ";
				a += Singleton->Tube->Thick.Size();
				a += " ";
				a += GetTickCount();
				pr(a);
			}
		}
#pragma end_region
		else if (msg == "REDRAW SG")
#pragma region
		{
			pr("REDRAW SG");
			BankZoneData z = bank->GetNextSGZone(false);
			pr(z.ToString());
			if (z.Ok)
			{
				SGR sgr = SGR(FRSG1->GetFix());
				sgr.AddZone(z);
				FRSG1->Set(sgr.GetSG());
				pr(sgr.GetSG().ToString());
				MitFX mitFX = MitFX();
				AnsiString result = mitFX.SetSG(sgr.GetSG().group);
				pr(AnsiString("SetSG: ") + result);
			}
		}
#pragma end_region
		else if (msg == "STATUS1")
#pragma region
		{
			StatusBarTop->Panels->Items[0]->Text = post_name;
			StatusBarTop->Refresh();
		}
#pragma end_region
		else if (msg == "STATUS2")
#pragma region
		{
			StatusBarTop->Panels->Items[1]->Text = post_name;
			StatusBarTop->Refresh();
		}
#pragma end_region
		else if (msg == "CLEAR")
#pragma region
		{
			ClearCharts();
		}
#pragma end_region
		else if (msg == "ERROR")
#pragma region
		{
			thCurrent->WaitFor();
			delete thCurrent;
			thCurrent = NULL;
			FRButtons1->Enable();
			SetAbleButtons(true);
			FRButtons1->SBWork->Caption = "Работа";
			FRSumM1->OnDecision = NULL;
			bank->Report();
			// SLD->CatchReport();
		}
#pragma end_region
		else if (msg == "COMPLETE_ZONES")
#pragma region
		{
			Singleton->Tube->Calc();
			FRCross1->Draw(Singleton->Tube);
			FRLine1->Draw(Singleton->Tube);
			FRThick1->Draw(Singleton->Tube);
			FRSumM1->Draw(Singleton->Tube);
			AddResultZone();
			bank->SetCompleteResult();
			FRButtons1->SBView->Enabled = true;
			FRButtons1->SBSOP->Enabled = true;
			FRSumM1->SetEnabledResult(true);
			FRSumM1->OnDecision = ChangeDecision;
		}
#pragma end_region
		else if (msg == "VIEW")
#pragma region
		{
			isView = true;
			FRButtons1->SBView->Enabled = true;
			FRButtons1->SBSOP->Enabled = true;
			FRSumM1->SetEnabledResult(true);
			FRSumM1->OnDecision = ChangeDecision;
		}
#pragma end_region
		// else if (msg == "INTERRUPT")
		// #pragma region
		// {
		// if (!cbInterruptView->Checked)
		// {
		// thCurrent->WaitFor();
		// delete thCurrent;
		// thCurrent = NULL;
		//
		// ThWork* t = (ThWork*)thCurrent;
		// SLD->oRESULT->Set(Singleton->SumResult->decision != "Брак");
		// SLD->oSTROBE->Set(true);
		// Sleep(500);
		// SLD->oSHIFT->Set(true);
		// if (!WasSOP)
		// Singleton->SaveTubeToDB(user);
		// }
		// else
		// FRButtons1->Interrupt();
		// }
		// #pragma end_region
		else if (msg == "COMPLETE")
#pragma region
		{
			// MitFX mitFX = MitFX();
			// AnsiString result;
			// TubeLengthFX = mitFX.GetTubeLength(&result);
			// TubeLengthFX /= 1000;
			// pr(AnsiString("TubeLengthFX=") + TubeLengthFX + " " + result);
			// if (result == "Ok")
			// FRSumM1->SetTubeLenght(TubeLengthFX);
			thCurrent->WaitFor();
			if (thCurrent->GetName() == "ThWork")
			{
				delete thCurrent;
				thCurrent = NULL;
				// SLD->CatchReport();
				bool IsInterruptViewBrak =
					PA("Defect.Some.IsInterruptViewBrak").Bool();
				if (IsInterruptViewBrak)
					IsInterruptViewBrak = Singleton->Tube->RSum.DClass == 0;
				if (!cbInterruptView->Checked && !IsInterruptViewBrak)
				{
					FRStatist1->Add(Singleton->Tube->RSum.DClass == 0);
					SLD->oRESULT->Set(Singleton->Tube->RSum.DClass != 0);
					SLD->oSTROBE->Set(true);
					SLD->oSHIFT->Set(true);
					Sleep(500);
					if (!WasSOP)
					{
						Singleton->Save(user);
						Singleton->SaveTubeToDB(user, client, FRSG1->SGGroup());
					}
					SetAbleButtons(false);
					FRSumM1->OnDecision = NULL;
					TPr::Clear();
					IW = GetIsWork();
					user = PA("Users.CurrentUser.Name").String();
					client = PA("Clients.Current.Name").String();
					FRSumM1->SetEnabledResult(false);
					FRButtons1->SBView->Enabled = false;
					FRButtons1->SBSOP->Enabled = false;
					thCurrent = new ThWork(IW, bank);
				}
				else
				{
					FRButtons1->Interrupt();
					StatusBarTop->Panels->Items[1]->Text =
						"Прерывание на просмотр";
					StatusBarTop->Refresh();
				}
			}
			else
			{
				if (thCurrent->GetName() == "ThTest")
					isView = true;
				delete thCurrent;
				thCurrent = NULL;
				FRButtons1->Enable();
				SetAbleButtons(true);
				bank->Report();
				// SLD->CatchReport();
			}
		}
#pragma end_region
		else
			FATAL(AnsiString
			("TMainForm::DoThreadMessage: Неизвестное сообщение: ") + msg);
	}
}

void __fastcall TMainForm::ActionParsExecute(TObject *Sender)
{
	LoadSettings();
	Singleton->Tube->Calc();
	ReDraw();
}

// ---------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
	// f->ShowModal();
	// delete f;
	MainTest mTest;
	mTest.Exec();
}
// ---------------------------------------------------------------------------
