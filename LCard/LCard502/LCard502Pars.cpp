#pragma hdrstop
#include "LCard502Pars.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
void LCard502Pars::Board::LoadSettings()
{
	PA pa("Defect.L502");
	syncMode = pa.Item("SyncMode").Int();
	syncStartMode = pa.Item("SyncStartMode").Int();
	kadrs_frequency_Hz =pa.Item("FrequencyPerChannel").Double();
	TTL_frequency_Hz =pa.Item("TTL.Frequency").Double();
}

//---------------------------------------------------------------------------
LCard502Pars::LCard502Pars()
{
	LoadSettings();
}

//---------------------------------------------------------------------------
void LCard502Pars::LoadSettings()
{
	PA pa("TSSet.Current.TSDef");
	Cross.Clear();
	Cross.LoadSettings(pa.Item("Cross.L502Chs"));

	Line.Clear();
	Line.LoadSettings(pa.Item("Line.L502Chs"));

	SG.Clear();

	SG.Add(RChannel_parameters(pa.Item("SG.Sensor_I"),"Sensor_SG_I"));
	SG.Add(RChannel_parameters(pa.Item("SG.Sensor_U"),"Sensor_SG_U"));
	board.LoadSettings();
}

//---------------------------------------------------------------------------

