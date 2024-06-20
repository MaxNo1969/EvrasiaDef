#pragma hdrstop
#include "CatchTTL.h"
#include "PA.h"
#pragma package(smart_init)
CatchTTL* CatchTTL::Instance = NULL;

void CatchTTL::Start(DWORD _tick, double _real_frequency_Hz)
{
	if(Instance!=NULL)
		delete Instance;
	Instance=new CatchTTL(_tick, _real_frequency_Hz);

}
void CatchTTL::Add(unsigned int* _buf, int _size)
{
	if(Instance!=NULL)
		Instance->Add0(_buf, _size);
}
void CatchTTL::Dispose(void)
{
	if(Instance!=NULL)
		delete Instance;
	Instance=NULL;
}

SignalEvent* CatchTTL::GetNext(void)
{
	if(Instance==NULL)
		return(NULL);
	return(Instance->GetNext0());
}
TTLSignal* CatchTTL::ByName(AnsiString _Name)
{
	if(Instance==NULL)
		return(NULL);
	return(Instance->ByName0(_Name));
}

CatchTTL::CatchTTL(DWORD _tick, double _real_frequency_Hz)
{
	startTick = _tick;
	frequency = _real_frequency_Hz;
	count_in=0;
	count_out=0;
	S.Add(new TTLSignal(PA("Defect.L502.TTL.CControl.Position").Int(),"CCONTROL"));
	S.Add(new TTLSignal(PA("Defect.L502.TTL.LControl.Position").Int(),"LCONTROL"));
	S.Add(new TTLSignal(PA("Defect.L502.TTL.TControl.Position").Int(),"TCONTROL"));
	S.Add(new TTLSignal(PA("Defect.L502.TTL.Strobe.Position").Int(),"STROBE"));
}

void CatchTTL::Add0(unsigned int* _buf, int _size)
{
	for (int i = 0; i < _size; i++)
	{
		count_in++;
		unsigned int v = _buf[i];
		for(int j=0;j<S.Count();j++)
		{
			TTLSignal* t=S[j];
			int v_out=t->Exec(v);
			if(v_out!=0)
			{
				SignalEvent* E=L.Add();
				E->signal=t;
				E->tick=TickByCount_Ms(count_in);
				E->name=t->Name;
				E->value=v_out>0;
			}
		}
	}
}

double CatchTTL::TickByCount_Ms(int _count)
{
	double t=_count*1000;
	t/=frequency;
	t+=startTick;
	return(t);
}
SignalEvent* CatchTTL::GetNext0(void)
{
	if(count_out>=L.Count())
		return(NULL);
	SignalEvent* SE=L[count_out];
	count_out++;
	return(SE);
}
TTLSignal* CatchTTL::ByName0(AnsiString _Name)
{
	for(int i=0;i<S.Count();i++)
	{
		if(S[i]->Name==_Name)
			return(S[i]);
	}
	return(NULL);
}



