#pragma hdrstop
#include "L502Test.h"
#pragma package(smart_init)

L502Test::L502Test()
{
	t_l502_hnd handle = L502_Create();
	if (handle == NULL)
		throw;
	unsigned int dev_cnt = 0;
	if (L502_GetSerialList(NULL, 0, 0, &dev_cnt) < 0)
		throw;
	if (dev_cnt <= 0)
		throw;
	t_l502_serial_list list =
		(t_l502_serial_list)(new char[dev_cnt * L502_SERIAL_SIZE]);
	if (L502_GetSerialList(list, dev_cnt, 0, NULL) <= 0)
		throw;
	if (L502_Open(handle, list[0]) != 0)
		throw;
	if (L502_SetLChannelCount(handle, 1) != 0)
		throw;
	if (L502_SetLChannel(handle, 0, 0, 0, 0, 0) != 0)
		throw;
	if (L502_SetSyncMode(handle, 0) != 0)
		throw;
	if (L502_SetSyncStartMode(handle, 0) != 0)
		throw;
	double f_acq = 8000;
	double f_lch = 8000;
	if (L502_SetAdcFreq(handle, &f_acq, &f_lch) != 0)
		throw;
	if (L502_Configure(handle, 0) != 0)
		throw;
	double buf = 0;
	if (L502_AsyncGetAdcFrame(handle, L502_PROC_FLAGS_VOLT, 1000, &buf) != 0)
		throw;
    L502_Free(handle);
}

