//---------------------------------------------------------------------------
#ifndef SGRH
#define SGRH
#include <System.hpp>
#include <vector>
#include <Graphics.hpp>
#include "BankZone.h"
using namespace std;

//---------------------------------------------------------------------------
class SGR
{
public:
	class SG
	{
		//Группа прочности с атрибутами вероятности и цвета
	public:
		SG(void)
		{
			group = "?";
			probability = 0;
			color = clYellow;
		}
		AnsiString group;
		double probability;
		TColor color;
		AnsiString ToString();
	};
private:
	class IU
	{
	public:
		double I;
		double U;

		IU(void)
		{
			I = 0;
			U = 0;
		};
	};
	class Point : public IU
	{
	public:
		int index;

		Point(void)
		{
			index = 0;
		};
	};

	vector<IU>iu;
	AnsiString data;
	vector<int>tresh;
	AnsiString typeSize;
	int periodMin;
	int periodMax;
	int borders;
	int borders1;
	bool ByU;
	vector<double>coords;
	int stop;

	void IUToStr(void);
	void LoadSettings(void);
	bool GetNextPeriodI(int* _start, int* _size);
	int GetNextSizeI(int* _start);
	bool GetNextPeriodU(int* _start, int* _size);
	int GetNextSizeU(int* _start);
	void CalcCoords(void);

	void pr(AnsiString _msg);
	void pr0(AnsiString _msg);

//	bool SaveToDB(void);
//	SG GetSG(int _position);
	SG SaveGetSG();

	AnsiString SGroupFix;
	TColor conv_color(int _col);
	void CheckTypeSize(void);

	long tube_id;
	SG sg;

public:
	SGR(AnsiString _SGroupFix);

	inline SG GetSG(void)
	{
		return (sg);
	};
	bool Test(int _period);
	void AddZone(BankZoneData _zone);
};
#endif
