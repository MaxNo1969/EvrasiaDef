#ifndef BankH
#define BankH
#include <System.hpp>
#include <SyncObjs.hpp>
#include "BankUnit.h"
#include "IsWork.h"
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------
// Класс бухгалтерский и ни от каких времен и событий не зависит. Важно лишь, чтобы события шли последовательно.
// Если задним тиком сообщается, что имело место некоторое событие, а банк уже выдал данные с учетом того, что этого события не было,
// то пеняйте на себя - ситуация не предсказуемая, никаких сторно на предусматривается.
//
// Банк получает поток данных от плат сбора, записывая время начала сбора и время последнего полученного пакета.
// Предполагается, что платы весьма точно соблюдают частоту сбора, ошибка может быть только в начале и в конце на уровне задержки Windows.
// Соответственно на любой тик можно указать байт сбора, и наоборот на любой байт можно указать его тик.
//
// Банк получает текущие положения трубы в виде потока из пар чисел: тик и положение. Не важно, что пара чисел придет с опозданием,
// важно чтобы они шли последовательно.
// Предполагается, что пары чисел формируются лирами с некоторой периодичностью, а также сигналами на устройствах по мере поступления,
// можно и то и другое сразу.
//
// Банк получает длину трубы, до тех пор, пока он не получил длину трубы - он предполагает, что все ранее полученные положения трубы
// еще не достигли конца трубы.
//
// Банк выдает по запросу очередную зону по каждому устройству в виде адреса массива определенной длины, или пары тиков
// - начала и конца зоны в случае толщиномера.
// Если для запрашиваемой зоны данные еще не поступили, или не поступили тики положения трубы, то банк зону не выдаст.
// Для расчета зоны банк использует геометрию установки, т.е. положение сигнальных датчиков и датчиков сбора.
// Банк предполагает, что между полученными положениями трубы труба двигалась равномерно, таким образом для кажной зоны можно
// получить время ее начала и время ее конца, а из этих времен можно получить байты начала и конца собранных данных.
//
// Банк будет считать свою работу законченной, когда у него запросили и он выдал все зоны по всем устройствам вплоть до конца трубы.
//
// Банк является потокозащищенным - любые методы любым потоком в любое время. За раз выполняется только один метод, остальные ждут.
// Банк является сервером - пока его не спрашивают он ничего не делает.

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

	bool CompleteGetResultZones; // получены все результирующие зоны
	bool DoneCompleteGetResultZones; // сообщено о получении всех результирующих зон
	bool CompleteResult; // пересчитаны все результирующие зоны
	bool CompleteGiveResultZones; // отданы все результирующие зоны

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
