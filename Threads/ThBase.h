#ifndef ThBaseH
#define ThBaseH
#include<SyncObjs.hpp>
#include<Classes.hpp>
// ---------------------------------------------------------------------------
class ThBase : public TThread
{
private:
protected:
	void __fastcall Execute()=0;
	void pr(AnsiString _msg);
	AnsiString name;
	void PostStatus1(AnsiString _msg);
	void PostStatus2(AnsiString _msg);
	void PPR(AnsiString _msg);
public:
	__fastcall ThBase(AnsiString _name);
	virtual __fastcall ~ThBase(void);
	inline AnsiString GetName(void)
	{
		return(name);
    }
};
#endif
