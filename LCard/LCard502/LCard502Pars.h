#ifndef LCard502ParsH
#define LCard502ParsH
#include "LCardChGroup.h"
//---------------------------------------------------------------------------
class LCard502Pars
{
private:
public:
	class Board
	{
	public:
		int syncMode;
		int syncStartMode;
		double kadrs_frequency_Hz;
		double TTL_frequency_Hz;
		bool IsTTL;

		void LoadSettings(void);
	};
	LCardChGroup Cross;
	LCardChGroup Line;
	LCardChGroup SG;
	Board board;

	LCard502Pars();
	void LoadSettings();
};
//---------------------------------------------------------------------------
#endif
