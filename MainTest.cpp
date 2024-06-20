#pragma hdrstop
#include "MainTest.h"
#include "Protocol.h"
#include "JRectifier.h"

#include "LCard502.h"
#pragma package(smart_init)
void MainTest::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("MainTest: ")+_msg);
}

void MainTest::Exec(void)
{
	pr("Начали");
	AnsiString sss;
	int a1=1;
	int a2=22;
	int a3=0;
	sss=AnsiString().sprintf("%02d:%02d:%02d",a1,a2,a3);
	pr(sss);
	//	ModBus modBus;
//	JRectifier jRectCross(&modBus,'c');
//	JRectifier jRectLine(&modBus,'l');


//	LCard502Pars lcardPars;
//	lcardPars.LoadSettings();
//	LCardChGroup current;
//	current.Add(lcardPars.Cross);
//	current.Add(lcardPars.Line);
//	current.Add(lcardPars.SG);
//
//
//	LCard502 lcard;
//	lcard.Start(&(lcardPars.board), &current);
//	for(int i=0;i<50;i++)
//	{
//		pr(AnsiString("Шаг ")+i);
//		Sleep(200);
//		LCard502::RBuf rbuf=lcard.Read();
//		pr(rbuf.ToString());
//	}
//	lcard.Stop();

	pr("закончили");
}
