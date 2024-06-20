#pragma hdrstop
#include "Solenoid.h"
#include "uFunctions.h"
#include "Protocol.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
SolenoidPars::SolenoidPars(void)
{
	ByTemp = false;

	AlarmLevel = 0;
	AlarmULevel = 0;
	DifULevel = 0;

	TempStart = 0;
	ResistStart = 0;
	TRC = 0;
	AlarmTemp = 0;

	Devider = 0;
}

//---------------------------------------------------------------------------
SolenoidPars::SolenoidPars(PA _pa)
{
	ChI = RChannel_parameters(_pa.Item("Sensor_I"));
	ChU = RChannel_parameters(_pa.Item("Sensor_U"));

	ByTemp = _pa.Item("ByTemp").Bool();

	AlarmLevel = _pa.Item("SolVoltage.ResistSolenoid").Int() * 1.4;
	AlarmULevel = _pa.Item("SolVoltage.VoltageSolenoid").Int();
	DifULevel = _pa.Item("SolVoltage.DifVoltageSolenoid").Int();

	TempStart = _pa.Item("SolTemperaturePars.TempStart").Double();
	ResistStart = _pa.Item("SolTemperaturePars.ResistStart").Double();
	TRC = _pa.Item("SolTemperaturePars.TRCoef").Double();
	AlarmTemp = _pa.Item("SolTemperaturePars.AlarmTemp").Double();

	Devider = _pa.Item("Devider").Double();
}

//---------------------------------------------------------------------------
Solenoid::Solenoid(void)
{
	jCollect = NULL;
}

//---------------------------------------------------------------------------
Solenoid::Solenoid(PA _pa,JCollect502* _jCollect)
{
	Pars=SolenoidPars(_pa);
	jCollect = _jCollect;
}

//---------------------------------------------------------------------------
void Solenoid::LoadSettings(PA _pa)
{
	Pars=SolenoidPars(_pa);
}


//---------------------------------------------------------------------------
double Solenoid::getAmperage()
{
	if (jCollect == NULL)
		FATAL("Solenoid: jCollect==NULL");
	bool ret;
	double val = jCollect->GetValueV(&Pars.ChI, &ret);
	if (!ret)
		FATAL(AnsiString("Solenoid:getAmperage: Ошибка: ")+jCollect->GetErrorMsg());
	pr(AnsiString("getAmperage=")+(val - 2.5) * 10);
	return ((val - 2.5) * 10);
}

//---------------------------------------------------------------------------
double Solenoid::getVoltage()
{
	if (jCollect == NULL)
		FATAL("Solenoid: jCollect==NULL");
	bool ret;
	double val = jCollect->GetValueV(&Pars.ChU, &ret);
	if (!ret)
		FATAL("Solenoid:getVoltage: Ошибка");
	pr(AnsiString("getVoltage=")+val * Pars.Devider);
	return (val * Pars.Devider);
}

//---------------------------------------------------------------------------
double Solenoid::getResist()
{
	double i = getAmperage();
	double u = getVoltage();
	double R = (double)(u / i);
	return R;
}

//---------------------------------------------------------------------------
bool Solenoid::OkU()
{
	bool pu = ((getVoltage() < Pars.DifULevel + Pars.AlarmULevel) && (getVoltage() > Pars.AlarmULevel -
		Pars.DifULevel));
	return pu;
}

//---------------------------------------------------------------------------
bool Solenoid::OkResist()
{
	double t = getResist();
	bool p = (t < Pars.AlarmLevel);
	if (!p)
	{
		AnsiString a;
		a += "!OkResist: ";
		a += GetUIR();
		a.cat_printf(" AlarmLevel=%.3f", Pars.AlarmLevel);
		TPr::pr(a);
	}
	return p;
}

//---------------------------------------------------------------------------
AnsiString Solenoid::GetUIR(void)
{
	double i = getAmperage();
	double u = getVoltage();
	double R = (double)(u / i);
	AnsiString ret;
	ret.printf("U=%.3lf I=%.3lf R=%.3lf", u, i, R);
	return (ret);
}

//---------------------------------------------------------------------------
double Solenoid::getTemp()
{
	double Temp = Pars.TempStart + (getResist() / Pars.ResistStart - 1) / Pars.TRC;
	return Temp;
}

//---------------------------------------------------------------------------
bool Solenoid::OkTemp()
{
	bool p = (Pars.AlarmTemp > getTemp());
	return p;
}

//---------------------------------------------------------------------------
bool Solenoid::Ok()
{
	if (Pars.ByTemp)
		return (OkTemp());
	else
		return (OkResist());
}
//---------------------------------------------------------------------------
void Solenoid::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("Solenoid: ")+_msg);
}

