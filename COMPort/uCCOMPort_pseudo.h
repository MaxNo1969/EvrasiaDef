// ---------------------------------------------------------------------------
#ifndef uCCOMPort_pseudoH
#define uCCOMPort_pseudoH
#include<system.hpp>
#include "uCCOMPort.h"
// ---------------------------------------------------------------------------
class CCOMPort_pseudo : public CCOMPort
{
private:
	CCOMPort_pseudo()
	{
	};
public:
	static CCOMPort* Create(void)
	{
		return (new CCOMPort_pseudo());
	};
	bool read_s(unsigned char* _s,int _n)
	{
		return (true);
	};
	bool write_s(unsigned char* _s,int _n)
	{
		return (true);
	};
	void ClearBuffer(void)
	{
	};
};
#endif
