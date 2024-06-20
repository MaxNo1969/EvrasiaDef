#ifndef WinWorkH
#define WinWorkH
#include <Forms.hpp>
#include <ExtCtrls.hpp>

class WinWork
{
private:
	TTimer* timer;
	void __fastcall Exec(TObject *Sender);
	TForm* owner;
	int MuchWinWorkTime;
public:
	WinWork(TForm* _owner);
	~WinWork(void);
	void Init(void);
	void Dispose(void);
};
#endif
