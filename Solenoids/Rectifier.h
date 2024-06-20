//---------------------------------------------------------------------------
#ifndef RectifierH
#define RectifierH
#include "ModBus.h"
//---------------------------------------------------------------------------
class RectifierPars
{
public:
	int Abonent;
	char IU;
	int Timeout;
	double NominalI;
	double NominalU;
	double MaxI;
	double MaxU;
	double MaxR;
	int Period;

	RectifierPars(char _Tp);
};

class Rectifier
{
private:
	ModBus* modBus;
	RectifierPars Pars;
	char tp;

	bool SetMode(void);
	bool SetTimeout(void);
	bool SetNominal(void);
	bool SetMaximum(void);
	bool OnOff(bool _On);
	bool IsOk(AnsiString _ret);
	void pr(AnsiString _msg);

public:
	Rectifier(ModBus* _modBus, char _Tp);
	~Rectifier(void);

	struct State
	{
		bool started;
		bool error;
		AnsiString errorMsg;
		double OutputVoltage;
		double OutputCurrent;
		int ResidualProcessTimeSec;
		int ResidualProcessTimeMin;
		int ResidualProcessTimeHour;
		double MaxI;
		double MaxU;
		double MaxR;
		bool real;

		inline double Resistance(void)
		{
			return (OutputCurrent == 0 ? 0 : OutputVoltage / OutputCurrent);
		}

		inline AnsiString ResidualTime(void)
		{
			return (AnsiString().sprintf("%02d:%02d:%02d", ResidualProcessTimeHour, ResidualProcessTimeMin,
				ResidualProcessTimeSec));
		}

		State(void)
		{
			started=false;
			error=false;
			errorMsg=NULL;
			OutputVoltage = 0;
			OutputCurrent = 0;
			ResidualProcessTimeSec = 0;
			ResidualProcessTimeMin = 0;
			ResidualProcessTimeHour = 0;
			MaxI=0;
			MaxU=0;
			MaxR=0;
			real=false;
		}
		bool Overheat(void);
		AnsiString Tostring(void);

	};
	State state;
	bool Start(void);
	bool Stop(void);
	State Exec(void);
	inline char GetIU(void)
	{
		return (Pars.IU);
	}
};
//------------------------------------------------------------------------------
#endif
