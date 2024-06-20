#pragma hdrstop
#include "SignalServer.h"
#include "PA.h"
#include "SignalListDef.h"
#pragma package(smart_init)
SignalServer::SignalServer(void)
{
	timeout=PA("Defect.Work.SigTimeout").Int();
	if(timeout<10)
		timeout=10;
	PA("Defect.Work.SigCommang").Write("ANS~Error");
}
__fastcall SignalServer::~SignalServer(void)
{
	Terminate();
	WaitFor();
}
void _fastcall SignalServer::Execute()
{
	while (true)
	{
		if (Terminated)
			break;
		Parce();
		Sleep(timeout);
		if (Terminated)
			break;
	}
}
void SignalServer::Parce(void)
{
	TStringList* pList = new TStringList();
	pList->StrictDelimiter = true;
	pList->Delimiter = '~';
	pList->DelimitedText = PA("Defect.Work.SigCommang").String();
	CSignal* sig=NULL;
	switch(pList->Count)
	{
		case 2:
			if(pList->Strings[0]!="CMD")
				break;
			sig=SLD->FindZero(pList->Strings[1], true);
			if(sig==NULL)
			{
				PA("Defect.Work.SigCommang").Write("ANS~Error");
				break;
			}
			PA("Defect.Work.SigCommang").Write(AnsiString("ANS~")+(sig->Get()?"True":"False"));
			break;
		case 3:
			if(pList->Strings[0]!="CMD")
				break;
			sig=SLD->FindZero(pList->Strings[1], false);
			if(sig==NULL)
			{
				PA("Defect.Work.SigCommang").Write("ANS~Error");
				break;
			}
			sig->Set(pList->Strings[2]=="True");
			PA("Defect.Work.SigCommang").Write("ANS~Ok");
			break;
		default:
			break;
	}
	delete pList;

}
