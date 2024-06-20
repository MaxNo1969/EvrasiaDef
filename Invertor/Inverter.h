#ifndef InverterH
#define InverterH
#include "MitCome/uCInv.h"
//#include "Protocol.h"
#include "vcl.h"

//------------------------------------------------------------------------------
class rotationThread;

class Inverter
{
private:
	CInv* inverter;
	TCriticalSection* cs;
	//! ����� ������� ����� ����������� ��������� ��������� ������ 500��
	rotationThread *testThread;
	void OnProtocol(AnsiString _msg);
	int abonent;
	int SpeedRegister;
	int speed;
public:
	Inverter(bool _line, CInv* _Inv);
	~Inverter(void);
	//! @brief ������������� �������� � ���� �� ����������
	//! @param number - ����� ������ � ���������� ( 4,5,6 )
	//! @param value  - �������� � ��
	bool setParameterSpeed(int value);
	bool setSpeed(void);
	//! @param number ����� ������ �� (4,5,6)
	int getParameterSpeed(void);
	//! �������� ��������
	bool startRotation();
	//! ������������� ��������
	bool stopRotation();
	//! ��������� ��� ��������, ����� ��� �������� � ��������� ������
	CInv::State stateRead();
	CInv::State GetCurrentState();
	bool ResetErrors();
	bool NETManage();
	AnsiString GetErrorMsg();

	inline int GetAbonent()
	{
		return (abonent);
	}
	inline int DefaultSpeed(void)
	{
		return (speed);
	}
};

//------------------------------------------------------------------------------
class rotationThread : public TThread
{
private:
	void __fastcall Execute();
	CInv* inv;
	TCriticalSection* cs;
	int abonent;
public:
	__fastcall rotationThread(CInv* _inv, TCriticalSection* _cs, int _abonent);
	CInv::State CurrentState;
};
//------------------------------------------------------------------------------

#endif
