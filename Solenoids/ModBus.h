// ---------------------------------------------------------------------------
#ifndef ModBusH
#define ModBusH
// #include <StdCtrls.hpp>
#include "uCCOMPort.h"
#include<SyncObjs.hpp>

// ---------------------------------------------------------------------------
class ModBus
{
private:
	CCOMPort* comport;
	int max_iters;
	int timeout;

	void FOnProtocolWrite(OnProtocolDef _v);

	OnProtocolDef OnProtocolL;

	void pr(int _abonent, AnsiString _msg);

	AnsiString PresetSingleRegister0(int _abonent, int _pos, unsigned short _data);
	AnsiString ReadRegister0(char _cmd, int _abonent, int _pos, unsigned short* _result);

	AnsiString PresetSingleRegister(int _abonent, int _pos, unsigned short _data);
	AnsiString ReadRegister(char _cmd, int _abonent, int _pos, unsigned short* _result);

	AnsiString PresetSingleRegisterE(int _abonent, int _pos, unsigned short _data);
	AnsiString ReadRegisterE(char _cmd, int _abonent, int _pos, unsigned short* _result);
	AnsiString WriteReadE(int _abonent, int _pos, unsigned short _data);

	AnsiString ReadWriteReadE(int _abonent, int _pos, unsigned short _data);
	TCriticalSection* CS;
	void pr(AnsiString _msg);
public:
	ModBus(void);
	~ModBus(void);
	__property OnProtocolDef OnProtocol =
	{write = FOnProtocolWrite};

	AnsiString Write(int _abonent, int _pos, int _data);
	AnsiString Write(int _abonent, int _pos, double _data);
	AnsiString Write(int _abonent, int _pos, bool _data);

	AnsiString ReadInput(int _abonent, int _pos, int* _result);
	AnsiString ReadInput(int _abonent, int _pos, double* _result);

	AnsiString ReadHolding(int _abonent, int _pos, int* _result);
	AnsiString ReadHolding(int _abonent, int _pos, double* _result);
	AnsiString ReadHolding(int _abonent, int _pos, bool* _result);

	AnsiString WriteCheck(int _abonent, int _pos, int _data);
	AnsiString WriteCheck(int _abonent, int _pos, double _data);
	AnsiString WriteCheck(int _abonent, int _pos, bool _data);

};
#endif
