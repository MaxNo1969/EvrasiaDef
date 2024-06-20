#ifndef JCollectH
#define JCollectH
#include "RChannel_parameters.h"
#include "Bank.h"
#include "IsWork.h"

//---------------------------------------------------------------------------
class JCollect
{
protected:

public:
	JCollect()
	{
	};

	virtual ~JCollect(void)
	{
	};
	virtual void Init(IsWork _isWork) = 0;
	virtual void Start(void) = 0;
	virtual bool Exec(DWORD _tick) = 0;
	virtual void Stop(DWORD _tick) = 0;
};
#endif
