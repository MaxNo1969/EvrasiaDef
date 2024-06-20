#ifndef SolenoidH
#define SolenoidH
#include <System.hpp>
//#include "RChannel_parameters.h"
#include "JCollect502.h"

//---------------------------------------------------------------------------
class SolenoidPars
{
private:
public:
	bool ByTemp;
	double Devider;
	double AlarmLevel;
	double AlarmULevel;
	double DifULevel;
	double TempStart;
	double ResistStart;
	double TRC;
	double AlarmTemp;
	RChannel_parameters ChI;
	RChannel_parameters ChU;
	SolenoidPars(void);
	SolenoidPars(PA _pa);
};
//---------------------------------------------------------------------------

class Solenoid
{
private:
	SolenoidPars Pars;
	void pr(AnsiString _msg);
public:
	Solenoid(void);
	Solenoid(PA _pa,JCollect502* _jCollect);
	void LoadSettings(PA _pa);
	double getAmperage();
	double getVoltage();
	double getResist();
	bool OkResist();
	bool OkU(void);
	AnsiString GetUIR(void);
	double getTemp();
	bool OkTemp();
	bool Ok();
	JCollect502* jCollect;

	inline bool ByTemp()
	{
		return (Pars.ByTemp);
	}
};
//---------------------------------------------------------------------------
#endif
