#pragma hdrstop
#include "uFunctions.h"
#include "Protocol.h"
#include "LCard502.h"
#pragma package(smart_init)

#ifndef LCARD502_Virtual

// ---------------------------------------------------------------------------
AnsiString LCard502::RBuf::ToString(void)
{
	AnsiString ret;
	ret = "Rbuf: ";
	if (!Ok)
	{
		ret += "Error: ";
		ret += Error;
		return (ret);
	}
	ret += "Ok";
	ret += " ADC_size=";
	ret += ADC_size;
	ret += " TTL_size=";
	ret += TTL_size;
//	ret += " all=";
//	ret += adcSize + dinSize;
//	ret += " firstLch=";
//	ret += firstLch;
//	ret += " adcSize=";
//	ret += adcSize;
//	ret += " dinSize=";
//	ret += dinSize;
//	ret += " packets=";
//	ret += packets;
//	ret += " tail_size=";
//	ret += tail_size;
	return (ret);
}

// ---------------------------------------------------------------------------
LCard502::LCard502(void)
{
	raw_size = LCard502_INIT_SIZE;
	rawi = new unsigned int[raw_size];
	raw = new double[raw_size];
	rawd = new unsigned int[raw_size];
	values = new double[raw_size];
	tail = NULL;
	tail_size = 0;

	handle = L502_Create();
	if (handle == NULL)
		FATAL("LCard502::LCard502: Ошибка создания описателя модуля");
	unsigned int dev_cnt = 0;
	if (L502_GetSerialList(NULL, 0, 0, &dev_cnt) < 0)
		FATAL("LCard502::LCard502: Ни одной платы не найдено !");
	if (dev_cnt <= 0)
		FATAL("LCard502::LCard502: Ни одной платы не найдено !!");
	t_l502_serial_list list = (t_l502_serial_list)(new char[dev_cnt * L502_SERIAL_SIZE]);
	if (L502_GetSerialList(list, dev_cnt, 0, NULL) <= 0)
		FATAL("LCard502::LCard502: Ни одной платы не найдено !!!");
	AnsiString a = "LCard502::LCard502: Ошибка открытия модуля: ";
	a += list[0];
	LFATAL(a, L502_Open(handle, list[0]));
	delete[](char*)list;
	IsStarted = false;
	RECV_TOUT = 250;
	CurrentSensors = 0;
	VoltPercent = NULL;
	f_din_save = 0;
}

// ---------------------------------------------------------------------------
LCard502::~LCard502(void)
{
	Stop();
	L502_Free(handle);
	delete rawi;
	delete raw;
	delete values;
	if (VoltPercent != NULL)
		delete[]VoltPercent;
	if (tail != NULL)
		delete tail;
}

// ---------------------------------------------------------------------------
void LCard502::LFATAL(AnsiString _msg, int _err)
{
	if (_err == 0)
		return;
	AnsiString a = _msg;
	a += " ";
	a += L502_GetErrorString(_err);
	FATAL(a);
}

// ---------------------------------------------------------------------------
bool LCard502::CheckError(int _err)
{
	if (_err == 0)
		return (false);
	LastError = L502_GetErrorString(_err);
	return (true);
}

// ---------------------------------------------------------------------------
void LCard502::LoadSettings(LCard502Pars::Board* _b, LCardChGroup* _g)
{
	CurrentSensors = _g->Count();
	AnsiString a = "LCard502::LoadMainSettings: Не удалось задать параметры";
	LFATAL(a, L502_SetLChannelCount(handle, CurrentSensors));
	if (VoltPercent != NULL)
		delete[]VoltPercent;
	VoltPercent = new double[CurrentSensors];
	double K[6] =
	{10, 20, 50, 100, 200, 500};
	for (int i = 0; i < CurrentSensors; i++)
	{
		AnsiString a = "Канал[";
		a += i;
		a += "]: ";
		a += _g->Item(i).ToString();
		TPr::pr(a);
		RChannel_parameters chp = _g->Item(i);
		LFATAL(a, L502_SetLChannel(handle, i, _g->Item(i).phisicalChannel, _g->Item(i).collectedMode, _g->Item(i).range, 0));
		VoltPercent[i] = K[_g->Item(i).range];
	}
	if (tail != NULL)
		delete tail;
	tail = new double[CurrentSensors];
	// Настраиваем источник частоты синхронизации
	LFATAL(a, L502_SetSyncMode(handle, _b->syncMode));
	// Настраиваем  источник запуска сбора
	LFATAL(a, L502_SetSyncStartMode(handle, _b->syncStartMode));
	double f_acq = _b->kadrs_frequency_Hz * CurrentSensors;
	double f_lch = _b->kadrs_frequency_Hz;
	// настраиваем частоту сбора с АЦП
	LFATAL(a, L502_SetAdcFreq(handle, &f_acq, &f_lch));
	// Parameters.frequencyCollect = f_acq;
	// Parameters.frequencyPerChannel = f_lch;
	// Записываем настройки в модуль

	f_din_save = _b->TTL_frequency_Hz;
	LFATAL(a, L502_SetDinFreq(handle, &f_din_save));
	LFATAL(a, L502_Configure(handle, 0));
}

// ---------------------------------------------------------------------------
void LCard502::Start(LCard502Pars::Board* _b, LCardChGroup* _g)
{
	if (IsStarted)
		return;
	LoadSettings(_b, _g);
	IsStarted = true;
	Report();
#ifdef TTL_SIGNALS
	LFATAL("LCard502::Start: не смогли разрешить потоки: ", L502_StreamsEnable(handle, L502_STREAM_ADC | L502_STREAM_DIN));
#else
	LFATAL("LCard502::Start: не смогли разрешить потоки: ", L502_StreamsEnable(handle, L502_STREAM_ADC));
#endif
	LFATAL("LCard502::Start: не смогли стартовать: ", L502_StreamsStart(handle));
}

// ---------------------------------------------------------------------------
void LCard502::Stop(void)
{
	if (!IsStarted)
		return;
	IsStarted = false;
	LFATAL("LCard502::Start: не смогли остановиться: ", L502_StreamsStop(handle));
}

// ---------------------------------------------------------------------------
double* LCard502::Read(int* _size)
{
	uint32_t count;
	if (CheckError(L502_GetRecvReadyCount(handle, &count)))
	{
		*_size = -1;
		return (NULL);
	}
	count /= CurrentSensors;
	count *= CurrentSensors;
	SetRawSize(count);
	int rcv_size = L502_Recv(handle, rawi, count, RECV_TOUT);
	/* значение меньше нуля означает ошибку... */
	/* получаем номер лог. канала, соответствующий первому
	 отсчету АЦП, так как до этого могли обработать
	 некратное количество кадров */
	unsigned int firstLch;
	// L502_GetNextExpectedLchNum(handle, &firstLch);
	// AnsiString a = "firstLch=";
	// a += firstLch;
	// TPr::pr(a);
	if (CheckError(L502_GetNextExpectedLchNum(handle, &firstLch)))
	{
		*_size = -2;
		return (NULL);
	}
	if (rcv_size != (int)count)
	{
		*_size = -3;
		LastError = "Размер полученный не равен размеру запрошенному";
		return (NULL);
	}
	// переводим АЦП в Вольты
	unsigned int count1 = count;
	if (CheckError(L502_ProcessAdcData(handle, rawi, raw, &count1, L502_PROC_FLAGS_VOLT)))
	{
		*_size = -4;
		return (NULL);
	}
	if (count != count1)
	{
		*_size = -6;
		LastError = "Размер преобразование полученный не равен размеру запрошенному";
		return (NULL);
	}
	*_size = count;
	int sensor = 0;
	for (int i = 0; i < *_size; i++)
	{
		values[i] = raw[i] * VoltPercent[sensor];
		sensor++;
		if (sensor == CurrentSensors)
			sensor = 0;
	}
	return (values);
}

// ---------------------------------------------------------------------------
LCard502::RBuf LCard502::Read(void)
{
	RBuf rbuf;
	rbuf.Ok = false;
	unsigned int count;
	if (CheckError(L502_GetRecvReadyCount(handle, &count)))
	{
		rbuf.Error = LastError;
		return (rbuf);
	}
	if (count == 0)
		return (rbuf);
	SetRawSize((int)count);
	int rcv_size = L502_Recv(handle, rawi, count, RECV_TOUT);
	if (rcv_size != count)
	{
		rbuf.Error = "Размер полученный не равен размеру запрошенному";
		return (rbuf);
	}
	unsigned int firstLch;
	if (CheckError(L502_GetNextExpectedLchNum(handle, &firstLch)))
	{
		rbuf.Error = LastError;
		return (rbuf);
	}
	unsigned int adcSize=rcv_size;
	unsigned int dinSize=rcv_size;
	if (CheckError(L502_ProcessData(handle, rawi, (unsigned int)rcv_size, L502_PROC_FLAGS_VOLT, raw+tail_size, &adcSize, rawd,
		&dinSize)))
	{
		rbuf.Error = LastError;
		return (rbuf);
	}
	int adcSize_new = tail_size+adcSize;
	int packets = adcSize_new / CurrentSensors;
	int adcSize_packets = packets*CurrentSensors;
	int tail_new = adcSize_new-adcSize_packets;

	tail_new=tail_size+adcSize-((int)((tail_size+adcSize) / CurrentSensors))*CurrentSensors;

	pr(AnsiString(tail_size)+"+"+adcSize+"="+adcSize_new+"="+adcSize_packets+"+"+tail_new);
	pr(AnsiString("dinSize=")+dinSize);

	for (int i = 0; i < tail_new; i++)
	{
		raw[i] = raw[adcSize_packets + i];
//		pr(AnsiString("raw[")+i+"]=raw["+(adcSize_packets + i)+"]");
	}
	tail_size=tail_new;
	rbuf.ADC_size=adcSize_packets;
	rbuf.ADC_buf=raw;
	rbuf.TTL_size=dinSize;
	rbuf.TTL_buf=rawd;
	rbuf.Ok = true;
	return (rbuf);

}

// ---------------------------------------------------------------------------
void LCard502::SetRawSize(int _size)
{
	int lsize = _size + CurrentSensors;
	if (lsize > raw_size)
	{
		delete rawi;
		delete raw;
		delete rawd;
		delete values;
		double k = LCard502_ADD_PERCENT;
		k /= 100;
		k += 1;
		raw_size = (int)(lsize * k);
		rawi = new unsigned int[raw_size];
		raw = new double[raw_size];
		rawd = new unsigned int[raw_size];
		values = new double[raw_size];
	}
}

// ---------------------------------------------------------------------------
double LCard502::GetValueV(RChannel_parameters * _channel, LCard502Pars::Board * _b, bool* _ret)
{
	if (IsStarted)
	{
		*_ret = false;
		return (0);
	}
	LCardChGroup g;
	g.Add(*_channel);
	double buf;
	LoadSettings(_b, &g);
	*_ret = !CheckError(L502_AsyncGetAdcFrame(handle, L502_PROC_FLAGS_VOLT, 1000, &buf));
	pr(AnsiString("GetValueV=") + buf);
	return (buf);
}

// ---------------------------------------------------------------------------
double LCard502::GetValueP(double _val)
{
	return (_val * VoltPercent[0]);
}

// ---------------------------------------------------------------------------
double LCard502::GetValueP(RChannel_parameters * _channel, LCard502Pars::Board * _b, bool* _ret)
{
	return (GetValueP(GetValueV(_channel, _b, _ret)));
}

// ---------------------------------------------------------------------------
void LCard502::pr(AnsiString _msg)
{
	TPr::pr(AnsiString("LCard502: " + _msg));
}

// ---------------------------------------------------------------------------
void LCard502::Report(void)
{
	double f_acq;
	double f_frame;
	double f_din = f_din_save;
	LFATAL("L502_GetAdcFreq", L502_GetAdcFreq(handle, &f_acq, &f_frame));
	pr(AnsiString().sprintf("Частота на канал=%0.3lf", f_acq));
	pr(AnsiString().sprintf("Частота кадров=%0.3lf", f_frame));
	LFATAL("L502_SetDinFreq", L502_SetDinFreq(handle, &f_din));
	pr(AnsiString().sprintf("Частота TTL=%0.3lf", f_din));
}
// ---------------------------------------------------------------------------
#endif
