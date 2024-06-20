//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>


//---------------------------------------------------------------------------
USEFORM("Solenoids\TFRTEstSolenoid502.cpp", FRTEstSolenoid502); /* TFrame: File Type */
USEFORM("Solenoids\TFRRectifier.cpp", FRRectifier); /* TFrame: File Type */
USEFORM("SoligGroup\uTFRSG.cpp", FRSG); /* TFrame: File Type */
USEFORM("SOP\uTFRSOP.cpp", FRSOP); /* TFrame: File Type */
USEFORM("uTFRLineRemote.cpp", FRLineRemote); /* TFrame: File Type */
USEFORM("uTFRLine.cpp", FRLine); /* TFrame: File Type */
USEFORM("uTFRSum.cpp", FRSum); /* TFrame: File Type */
USEFORM("uTFRSplit.cpp", FRSplit); /* TFrame: File Type */
USEFORM("uTFRCross.cpp", FRCross); /* TFrame: File Type */
USEFORM("uTFRButtons.cpp", FRButtons); /* TFrame: File Type */
USEFORM("uTFRDefects.cpp", FRDefects); /* TFrame: File Type */
USEFORM("uTFRDeads.cpp", FRDeads); /* TFrame: File Type */
USEFORM("uTFViewC.cpp", FViewC);
USEFORM("uTFView.cpp", ViewForm);
USEFORM("uTFWinWork.cpp", FWinWork);
USEFORM("uTFRThick.cpp", FRThick); /* TFrame: File Type */
USEFORM("uTFRSumM.cpp", FRSumM); /* TFrame: File Type */
USEFORM("uTFRViewLDev.cpp", FRViewLDev); /* TFrame: File Type */
USEFORM("uTFRViewDev.cpp", FRViewDev); /* TFrame: File Type */
USEFORM("SOP\uTFSOPR.cpp", FSOPR);
USEFORM("SOP\uTFRSOPCheck.cpp", FRSOPCheck); /* TFrame: File Type */
USEFORM("Test\uTFTest502.cpp", FTest502);
USEFORM("uFViewZoneS.cpp", FViewZoneS);
USEFORM("uFViewZoneD.cpp", FViewZoneD);
USEFORM("uTFRBorders.cpp", FRBorders); /* TFrame: File Type */
USEFORM("uTFProtocol.cpp", FProtocol);
USEFORM("uFRStatist.cpp", FRStatist); /* TFrame: File Type */
USEFORM("TSChangeWarning.cpp", TSChangeWarningForm);
USEFORM("uFRViewZone.cpp", FRViewZone); /* TFrame: File Type */
USEFORM("A1730\uFRSigPanel.cpp", FRSigPanel); /* TFrame: File Type */
USEFORM("ABOUT_NTC_NK_URAN.cpp", AboutBox1);
USEFORM("A1730\uFSignalsState.cpp", FSignalsState);
USEFORM("LCard\LCard502\uTFRTestTTL.cpp", FRTestTTL); /* TFrame: File Type */
USEFORM("Main.cpp", MainForm);
USEFORM("Invertor\uTFRTestInverters.cpp", FRTestInverters); /* TFrame: File Type */
USEFORM("Invertor\uTFRTestInverter.cpp", FRTestInverter); /* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

	try
	{
        // Пытаемся открыть мьютекс.
		HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, L"Defectoscope");
        if(!hMutex)
          // Мьютекса не существует. То есть,
		  // это первый экземпляр,
          // создаем мьютекс.
		  hMutex = CreateMutex(0, 0, L"Defectoscope");
		else
		{
		  // Мьютекс существует , то есть , запущен
		  // второй экземпляр, говорим юзеру что он олень и закрываем прогу.
		  Application->MessageBoxW(L"Приложение уже запущено!!!",L"Ошибка",MB_OK|MB_ICONERROR);
		  return 0;
		}

		Application->Initialize();
		Application->MainFormOnTaskBar = true;

		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();

		// Приложение закрывается ,
		// освобождаем мьютекс.
		ReleaseMutex(hMutex);
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
