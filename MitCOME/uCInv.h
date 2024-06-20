// ---------------------------------------------------------------------------
#ifndef uCInvH
#define uCInvH
// ---------------------------------------------------------------------------
#include<System.hpp>
#include "uCCOMPort.h"
#include "PA.h"
#include<SyncObjs.hpp>

class CInv
{
public:
	class State
	{
	public:
		State();
		void SetI(byte _v);
		byte Get(void);
		static void CopyO(State* _src, State* _dst);

		bool oSTF;
		bool oSTR;
		bool oRL;
		bool oRM;
		bool oRH;
		bool oRT;
		bool oMRS;

		bool iRUN;
		bool iSTF;
		bool iSTR;
		bool iSU;
		bool iOL;
		bool iFU;
		bool iABC;

		bool error;
		AnsiString Tostring(void);
	};

private:
	CCOMPort* comport;

	void FOnProtocolWrite(OnProtocolDef _v);

	OnProtocolDef OnProtocolL;

	void pr(int _abonent, AnsiString _msg);

	int max_iters;

	int GetMode(int _abonent);
	bool Reset9696(int _abonent);

	bool Exec(int _abonent, AnsiString _code, AnsiString _request,
		AnsiString _request_data, AnsiString _reply0, int _reply0_size,
		AnsiString _reply1, int _reply1_size, AnsiString _reply2,
		int _reply2_size, AnsiString* _reply, AnsiString* _reply_data);

	AnsiString error_msg;
	TCriticalSection* cs;

	State StateRead0(int _abonent);
	bool StateWrite0(int _abonent, State _state);
	int GetFrequency0(int _abonent, AnsiString _cmd);
	bool SetFrequency0(int _abonent, AnsiString _cmd, int _frequency);
	bool SetMode0(int _abonent, int _mode);
	bool Reset99660(int _abonent);

	int timeout;
	State CurrentState;

public:
	CInv(PA _pa);
	~CInv(void);
	__property OnProtocolDef OnProtocol =
	{write = FOnProtocolWrite};

	State GetCurrentState(void);
	State StateRead(int _abonent);
	bool StateWrite(int _abonent, State _state);
	int GetFrequency(int _abonent, AnsiString _cmd);
	bool SetFrequency(int _abonent, AnsiString _cmd, int _frequency);
	bool SetMode(int _abonent, int _mode);
	bool Reset9966(int _abonent);
	AnsiString GetErrorMsg(void);

};
#endif
