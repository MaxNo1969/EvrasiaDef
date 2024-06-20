#pragma hdrstop
#include "Rectifier.h"
#include "PA.h"
#include "Math.h"
#include "Protocol.h"
#pragma package(smart_init)
RectifierPars::RectifierPars(char _Tp)
{
	PA pa;
	if (_Tp == 'c')
		pa = PA("TSSet.Current.TSDef.Cross.Rectifier");
	else
		pa = PA("TSSet.Current.TSThick.Rectifier");
	Abonent = pa.Item("Abonent").Int();
	if (pa.Item("TpIU").String() == "ByI")
		IU = 'I';
	else
		IU = 'U';
	Timeout = pa.Item("Timeout").Int();
	NominalI = pa.Item("NominalI").Double();
	NominalU = pa.Item("NominalU").Double();
	MaxI = pa.Item("MaxI").Double();
	MaxU = pa.Item("MaxU").Double();
	MaxR = pa.Item("MaxR").Double();
	Period = pa.Item("Period").Int();
}

// =====================================================================================================================
bool Rectifier::State::Overheat(void)
{
	return(Resistance()>MaxR);
}
AnsiString Rectifier::State::Tostring(void)
{
	AnsiString ret="";
	ret+=" U=";
	ret+=OutputVoltage;
	ret+=" I=";
	ret+=OutputCurrent;
	ret+=" R=";
	ret+=FloatToStrF(Resistance(), ffFixed, 3, 0);
	ret+=" MaxR=";
	ret+=MaxR;
	ret+=" overheat=";
	ret+=Overheat()?"true":"false";
	ret+=" error=";
	ret+=error?"true":"false";
	if(errorMsg!=NULL)
	{
		ret+=" emsg=";
		ret+=errorMsg;
	}
	return(ret);
}
// =====================================================================================================================
Rectifier::Rectifier(ModBus* _modBus, char _Tp) : Pars(_Tp)
{
	modBus = _modBus;
	state.MaxI=Pars.MaxI;
	state.MaxU=Pars.MaxU;
	state.MaxR=Pars.MaxR;
	tp=_Tp;
}
Rectifier::~Rectifier(void)
{
	Stop();
}
void Rectifier::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("Rectifier ")+tp+": "+_msg);
}

bool Rectifier::Start(void)
{
	if (state.started)
		return(false);
	if (!SetMode())
		return(false);
	if (!SetTimeout())
		return(false);
	if (!SetNominal())
		return(false);
	if (!SetMaximum())
		return(false);
	if (!OnOff(true))
		return(false);
	state.started = true;
	state.error=false;
	state.errorMsg=NULL;
	return(true);
}

bool Rectifier::Stop(void)
{
	if (!state.started)
		return(true);
	if (!OnOff(false))
		return(false);
	state.started = false;
	return(true);
}

Rectifier::State Rectifier::Exec(void)
{
	if(state.error)
		return(state);
	if (!state.started)
		return(state);
	if(!IsOk(modBus->ReadInput(Pars.Abonent, 1, &state.OutputVoltage)))
		return(state);
	if(!IsOk(modBus->ReadInput(Pars.Abonent, 2, &state.OutputCurrent)))
		return(state);
	if(!IsOk(modBus->ReadInput(Pars.Abonent, 6, &state.ResidualProcessTimeSec)))
		return(state);
	if(!IsOk(modBus->ReadInput(Pars.Abonent, 7, &state.ResidualProcessTimeMin)))
		return(state);
	if(!IsOk(modBus->ReadInput(Pars.Abonent, 8, &state.ResidualProcessTimeHour)))
		return(state);
	state.error=false;
	state.errorMsg=NULL;
	state.real=true;
	return(state);
}

bool Rectifier::IsOk(AnsiString _ret)
{
	if (state.error)
		return (false);
	if (_ret == NULL)
		return (true);
	state.error = true;
	state.errorMsg = _ret;
	return (false);
}

bool Rectifier::SetMode(void)
{
	pr("SetMode");
	if (Pars.IU == 'U')
	{
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 60, true)))
			return (false);
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 61, false)))
			return (false);
		return (true);
	}
	else
	{
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 61, true)))
			return (false);
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 60, false)))
			return (false);
		return (true);
	}

}

bool Rectifier::SetTimeout(void)
{
	pr("SetTimeout");
	double v = Pars.Timeout;
	int Hour = (int)floor(v / (60 * 60));
	v -= Hour * 60 * 60;
	int Min = (int)floor(v / 60);
	int Sec = (int)floor(v - Min * 60);

	if (Pars.IU == 'U')
	{
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 59, Hour)))
			return (false);
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 58, Min)))
			return (false);
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 57, Sec)))
			return (false);
		return (true);
	}
	else
	{
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 56, Hour)))
			return (false);
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 55, Min)))
			return (false);
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 54, Sec)))
			return (false);
		return (true);
	}
}

bool Rectifier::SetNominal(void)
{
	pr("SetNominal");
	if (Pars.IU == 'U')
	{
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 51, Pars.NominalU)))
			return (false);
		return (true);
	}
	else
	{
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 50, Pars.NominalI)))
			return (false);
		return (true);
	}
}

bool Rectifier::SetMaximum(void)
{
	pr("SetMaximum");
	if (Pars.IU == 'U')
	{
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 53, Pars.NominalI)))
			return (false);
		return (true);
	}
	else
	{
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 52, Pars.NominalU)))
			return (false);
		return (true);
	}
}

bool Rectifier::OnOff(bool _On)
{
	pr("OnOff");
	if (Pars.IU == 'U')
	{
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 61, false)))
			return (false);
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 60, _On)))
			return (false);
		return (true);
	}
	else
	{
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 60, false)))
			return (false);
		if (!IsOk(modBus->WriteCheck(Pars.Abonent, 61, _On)))
			return (false);
		return (true);
	}
}
