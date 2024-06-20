//---------------------------------------------------------------------------
#ifndef SignalH
#define SignalH
#include<System.hpp>
#include<SyncObjs.hpp>

//---------------------------------------------------------------------------
class CSignal
{
	friend class SignalList;
	friend class SignalListDef;
	friend class SignalListThick;
	friend class CatchSignals;

public:
	typedef void(__closure * tagOnSet)(void);

	typedef bool(__closure * tagOnWait)(bool _value, CSignal * _signal, DWORD _tm);

private:
	bool value;
	bool value_prev;
	AnsiString name;

	int dev;
	bool in;
	bool digital;
	int index;

	tagOnSet OnSet;
	tagOnWait OnWait;
	TCriticalSection* cs;
	DWORD last_changed;

	bool WasConst0(bool _value, DWORD _period);
	void Set0(bool _value);
	void AddHint(AnsiString _hint);

public:
	CSignal(AnsiString _name,AnsiString _hint, int _dev, bool _in, bool _digital, int _index, tagOnSet _OnSet, TCriticalSection* _cs,
		tagOnWait _OnWait);
	bool Get(void);
	bool WasConst(bool _value, DWORD _period);
	void Set(bool _value);
	bool Wait(bool _value, DWORD _tm);
	struct ValCh
	{
		bool value;
		DWORD last_changed;
	};
	ValCh GetCh(void);

	inline bool IsInput()
	{
		return (in);
	}

	inline int GetIndex()
	{
		return (index);
	}

	inline AnsiString GetName()
	{
		return (name);
	}

	inline int GetDev()
	{
		return (dev);
	}
	DWORD LastChanged(void);

	AnsiString hint;

};
#endif
