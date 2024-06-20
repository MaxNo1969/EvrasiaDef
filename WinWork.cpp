#pragma hdrstop
#include "WinWork.h"
#include "uTFWinWork.h"
#include "PA.h"
#pragma package(smart_init)

WinWork::WinWork(TForm* _owner)
{
	owner = _owner;
	timer = NULL;
}

WinWork::~WinWork(void)
{
	Dispose();
}

void WinWork::Init(void)
{
	Dispose();
	MuchWinWorkTime = PA("Defect.Some.MuchWinWorkTime").Int() * 60 * 60 * 1000;
	DWORD interval = PA("Defect.Some.MuchWinWorkTimeInterval").Int() * 60 * 60 * 1000;
	if (MuchWinWorkTime != 0 && interval != 0)
	{
		timer = new TTimer(owner);
		timer->OnTimer = Exec;
		timer->Interval = interval;
		timer->Enabled = true;
	}
}

void WinWork::Dispose(void)
{
	if (timer != NULL)
		delete timer;
	timer = NULL;
}

void __fastcall WinWork::Exec(TObject *Sender)
{
	timer->Enabled = false;
	if (GetTickCount() > (DWORD)MuchWinWorkTime)
	{
		TFWinWork* f = new TFWinWork(timer->Owner);
		f->ShowModal();
		delete f;
	}
	timer->Enabled = true;
}
