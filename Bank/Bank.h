#ifndef BankH
#define BankH
#include <System.hpp>
#include <SyncObjs.hpp>
#include "BankUnit.h"
#include "IsWork.h"
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------
// ����� ������������� � �� �� ����� ������ � ������� �� �������. ����� ����, ����� ������� ��� ���������������.
// ���� ������ ����� ����������, ��� ����� ����� ��������� �������, � ���� ��� ����� ������ � ������ ����, ��� ����� ������� �� ����,
// �� ������� �� ���� - �������� �� �������������, ������� ������ �� �����������������.
//
// ���� �������� ����� ������ �� ���� �����, ��������� ����� ������ ����� � ����� ���������� ����������� ������.
// ��������������, ��� ����� ������ ����� ��������� ������� �����, ������ ����� ���� ������ � ������ � � ����� �� ������ �������� Windows.
// �������������� �� ����� ��� ����� ������� ���� �����, � �������� �� ����� ���� ����� ������� ��� ���.
//
// ���� �������� ������� ��������� ����� � ���� ������ �� ��� �����: ��� � ���������. �� �����, ��� ���� ����� ������ � ����������,
// ����� ����� ��� ��� ���������������.
// ��������������, ��� ���� ����� ����������� ������ � ��������� ��������������, � ����� ��������� �� ����������� �� ���� �����������,
// ����� � �� � ������ �����.
//
// ���� �������� ����� �����, �� ��� ���, ���� �� �� ������� ����� ����� - �� ������������, ��� ��� ����� ���������� ��������� �����
// ��� �� �������� ����� �����.
//
// ���� ������ �� ������� ��������� ���� �� ������� ���������� � ���� ������ ������� ������������ �����, ��� ���� �����
// - ������ � ����� ���� � ������ �����������.
// ���� ��� ������������� ���� ������ ��� �� ���������, ��� �� ��������� ���� ��������� �����, �� ���� ���� �� ������.
// ��� ������� ���� ���� ���������� ��������� ���������, �.�. ��������� ���������� �������� � �������� �����.
// ���� ������������, ��� ����� ����������� ����������� ����� ����� ��������� ����������, ����� ������� ��� ������ ���� �����
// �������� ����� �� ������ � ����� �� �����, � �� ���� ������ ����� �������� ����� ������ � ����� ��������� ������.
//
// ���� ����� ������� ���� ������ �����������, ����� � ���� ��������� � �� ����� ��� ���� �� ���� ����������� ������ �� ����� �����.
//
// ���� �������� ���������������� - ����� ������ ����� ������� � ����� �����. �� ��� ����������� ������ ���� �����, ��������� ����.
// ���� �������� �������� - ���� ��� �� ���������� �� ������ �� ������.

class Bank
{
public:
	class TickPosition
	{
	public:
		TickPosition()
		{
		}

		TickPosition(double _tick, double _position)
		{
			tick = _tick;
			position = _position;
		}

		double tick;
		double position;

		AnsiString ToString(void);
	};

private:

	TCriticalSection* cs;
	DWORD startTick;
	vector<TickPosition>MTP;
	BankCUnit MCross;
	BankLUnit MLine;
	BankSGUnit MSG;
	BankTickUnit MThick;
	double TubeLength;
	vector<BankZoneResult>MZR;
	int resultzone_count;

	void Clear0();
	double TickByPosition(double _position);
	double* Get(BankLUnit* _LCUnit, double _position);
	double* Get2(BankCUnit* _LCUnit, double _position);
	BankZoneData GetNextZone0(BankLUnit* _unit,int _SensorsPosition);
	BankZoneData GetNextZone02(BankCUnit* _unit,int _SensorsPosition,bool _second);
	BankZoneTicks GetNextZoneThick(void);
	BankZoneData GetNextDataUnitZone(BankLUnit* _unit, bool _check);
	BankZoneData2 GetNextDataUnitZone2(BankCUnit* _unit, bool _check);
	void pr(AnsiString _msg);
	void prf(AnsiString _format, ...);
	void ReportDataUnit(BankLUnit* _dataUnit, AnsiString _head);
	void ReportThick(void);
	void ReportSG(void);
	void ReportResult(void);
	int GetMinZones(void);

	int WaitResultZones;

	bool CompleteGetResultZones; // �������� ��� �������������� ����
	bool DoneCompleteGetResultZones; // �������� � ��������� ���� �������������� ���
	bool CompleteResult; // ����������� ��� �������������� ����
	bool CompleteGiveResultZones; // ������ ��� �������������� ����

public:
	Bank(void);
	~Bank(void);
	void LoadSettings(void);

	void Start(IsWork _IW);

	void AddTickPosition(DWORD _tick, double _position);
	void SetTubeLength(int _length);
	int GetTubeLength(void);

	void FirstTickCross(DWORD _tick);
	void AddCross(DWORD _tick, double* _data, int _size);
	BankZoneData2 GetNextCrossZone(bool _check);

	void FirstTickLine(DWORD _tick);
	void AddLine(DWORD _tick, double* _data, int _size);
	BankZoneData GetNextLineZone(bool _check);

	void FirstTickSG(DWORD _tick);
	void FirstTickSG1(DWORD _tick);
	void LastTickSG1(DWORD _tick);
	void AddSG(DWORD _tick, double* _data, int _size);
	BankZoneData GetNextSGZone(bool _check);

	BankZoneTicks GetNextThickTicks(bool _check);
	void AddThickZone(int _zone, bool _Ok, double _val, bool _last);
	BankZoneVal GetNextThickZone(bool _check);

	void FirstTickGroup(DWORD _tick);
	void AddGroup(DWORD _tick, double* _data, int _size);

	void AddResultZone(int _index, bool _result);
	BankZoneResult GetNextResultZone(void);

	inline int GetThickZones(void)
	{
		return (MThick.MTV.size());
	}
	bool CheckCompleteGetResultZones(void);
	inline void SetCompleteResult(void)
	{
		CompleteResult=true;
	}
	bool IsComplete(void);
	void Report(void);
};
// ---------------------------------------------------------------------------
#endif
