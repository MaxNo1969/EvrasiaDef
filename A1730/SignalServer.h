#ifndef SignalServerH
#define SignalServerH
#include<SyncObjs.hpp>
#include<Classes.hpp>
class SignalServer:private TThread
{
private:
	void __fastcall Execute();
	int timeout;
	void Parce(void);
public:
	SignalServer(void);
	__fastcall ~SignalServer(void);
};
#endif
