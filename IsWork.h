//---------------------------------------------------------------------------
#ifndef IsWorkH
#define IsWorkH
//---------------------------------------------------------------------------
struct IsWork
{
	bool Cross;
	bool Line;
	bool Thick;
	bool SG;

	IsWork()
	{
		Cross= false;
		Line= false;
		Thick = false;
		SG= false;
	}
	IsWork(bool _Cross,bool _Line,bool _Thick,bool _SG)
	{
		Cross= _Cross;
		Line= _Line;
		Thick = _Thick;
		SG= _SG;
	}
};
#endif
