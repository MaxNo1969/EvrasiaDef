#pragma hdrstop
#include "ThPass.h"
#include "JPass.h"
#include "SMSM.h"
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall ThPass::ThPass(TIniFile*_ini)
	: ThBase(_ini, "Pass")
{
}

// ---------------------------------------------------------------------------
void __fastcall ThPass::Execute()
{
	JPass jPass=JPass(ini);
	PostStatus1("ֲûדמם");
	PostStatus2("");
	for (; ;)
	{
		if (Terminated)
			break;
		jPass.Exec();
		if (jPass.IsComplete())
			break;
		if (jPass.IsError())
		{
			PostStatus2(jPass.GetErrorMsg());
			break;
		}
		Sleep(500);
		if (Terminated)
			break;
	}
	SMSM::SetPost("COMPLETE");
}

// ---------------------------------------------------------------------------
