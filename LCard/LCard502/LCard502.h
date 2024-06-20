#ifndef LCard502H
#define LCard502H
#include "LCard502Pars.h"

#ifndef LCARD502_Virtual
#include "l502api.h"
#pragma comment(lib, "l502api.lib")
#define LCard502_INIT_SIZE 2000
#define LCard502_ADD_PERCENT 50

// ---------------------------------------------------------------------------
class LCard502
{
private:
	// ! Хендл платы
	t_l502_hnd handle;
	int raw_size;

	unsigned int* rawi;
	double* raw;
	unsigned int* rawd;
	double* values;
	double* tail;
	int tail_size;

	double* VoltPercent;
	bool IsStarted;
	// ! ТаймАут для сбора (с каким периодом будем скидывать данные из ацп в большой буфер,мс)
	int RECV_TOUT;
	int CurrentSensors;

	void SetRawSize(int _size);
	void LFATAL(AnsiString _msg, int _err);
	bool CheckError(int _err);
	void pr(AnsiString _msg);

	double f_din_save;

public:
	struct RBuf
	{
		int ADC_size;
		double* ADC_buf;
		int TTL_size;
		unsigned int* TTL_buf;
		bool Ok;
		AnsiString Error;
//		unsigned int count;
//		unsigned int firstLch;
//		unsigned int adcSize;
//		unsigned int dinSize;
//		int packets;
//		int tail_size;

		RBuf()
		{
			ADC_size = 0;
			ADC_buf = NULL;
			TTL_size = NULL;
			TTL_buf = NULL;
			Error = NULL;
			Ok = false;
//			count = 0;
//			firstLch = 0;
//			adcSize=0;
//			dinSize=0;
//			packets=0;
//			tail_size=0;
		}
		AnsiString ToString(void);
	};

	AnsiString LastError;

	LCard502();
	~LCard502(void);
	void LoadSettings(LCard502Pars::Board* _b, LCardChGroup* _g);
	void Start(LCard502Pars::Board* _b, LCardChGroup* _g);
	void Stop(void);
	double* Read(int* _size);
	RBuf Read(void);
	double GetValueV(RChannel_parameters* _channel, LCard502Pars::Board* _b, bool* _ret);
	double GetValueP(double _val);
	double GetValueP(RChannel_parameters* _channel, LCard502Pars::Board* _b, bool* _ret);
	void Report(void);
	inline double GetTTLFrequencyHz(void)
	{
		return(f_din_save);
	}
};
#else

// ---------------------------------------------------------------------------
class LCard502
{
public:
	AnsiString LastError;

	void LoadSettings(LCard502Pars::Board* _b, LCardChGroup* _g)
	{
	};

	void Start(LCard502Pars::Board* _b, LCardChGroup* _g)
	{
	};

	void Stop(void)
	{
	};

	double* Read(int* _size)
	{
		return (NULL);
	};

	double GetValue(RChannel_parameters* _channel, LCard502Pars::Board* _b, bool* _ret)
	{
		*_ret = true;
		return (0);
	};

	double GetValueV(RChannel_parameters* _channel, LCard502Pars::Board* _b, bool* _ret)
	{
		return (0);
	}

	double GetValueP(double _val)
	{
		return (0);
	};

	double GetValueP(RChannel_parameters* _channel, LCard502Pars::Board* _b, bool* _ret)
	{
		*_ret = true;
		return (0);
	}
};
// ---------------------------------------------------------------------------
#endif
#endif
