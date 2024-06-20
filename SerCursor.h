#ifndef SerCursorH
#define SerCursorH
#include <VCLTee.Chart.hpp>
#include <VCLTee.ArrowCha.hpp>

class SerCursor
{
private:
	TForm* Form;
	TChart* Chart;
	TArrowSeries* Series;
	TChartSeries *BaseSeries;
    int index;

	void __fastcall MouseEnter(TObject *Sender);
	void __fastcall MouseLeave(TObject *Sender);
	void __fastcall FormMouseWheel(TObject* Sender, TShiftState Shift, int WheelDelta, const TPoint &MousePos, bool &Handled);

//bool Entered;
public:
	SerCursor(TChartSeries* _BaseSeries);
	~SerCursor(void);
	void Clear(void);
	void Set(int _index);

	typedef void(__closure * OnSetDef)(int _index, double _level);

	OnSetDef OnSet;
};
#endif
