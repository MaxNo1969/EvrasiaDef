#pragma hdrstop
#include "SerCursor.h"
#pragma package(smart_init)

SerCursor::SerCursor(TChartSeries* _BaseSeries)
{
	BaseSeries = _BaseSeries;
	Chart = (TChart*)BaseSeries->ParentChart;
	TComponent* tk = NULL;
	for (tk = Chart->Owner; !tk->ClassType()->InheritsFrom(__classid(TForm)); tk = tk->Owner)
	{
		if (tk == NULL)
			break;
	}
	Form = (TForm*)tk;
	Chart->OnMouseEnter = MouseEnter;
	Series = new TArrowSeries(Chart);
	Series->ParentChart = Chart;
	Series->Color = clBlack;
	Series->ArrowWidth = 1;
	Series->ArrowHeight = 1;
	OnSet = NULL;
	index = -1;
}

SerCursor::~SerCursor(void)
{
	Chart->RemoveSeries(Series);
	delete Series;
}

void SerCursor::Clear(void)
{
	Series->Clear();
	index = -1;
	if (OnSet != NULL)
		OnSet(-1, 0);
}

void SerCursor::Set(int _index)
{
	Series->Clear();
	int mx = Chart->LeftAxis->Maximum;
	int mn = Chart->LeftAxis->Minimum;
	index = _index;
	if (index < 0)
		index=0;
	if(index>=BaseSeries->Count())
		index=BaseSeries->Count()-1;
	if (index < 0)
		index=0;
	if (index >= 0)
		Series->AddArrow(index, mn, index, mx);
	if (OnSet == NULL)
		return;
	if (index >= 0)
		OnSet(index, BaseSeries->YValue[_index]);
	else
		OnSet(-1, 0);
}

void __fastcall SerCursor::MouseEnter(TObject *Sender)
{
	if (Form != NULL)
		Form->OnMouseWheel = FormMouseWheel;
}

void __fastcall SerCursor::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, const TPoint &MousePos,
	bool &Handled)
{
	if (index < 0)
	{
		index = 0;
		Set(index);
		return;
	}
	int det = 0;
	if (WheelDelta > 0)
		det = 1;
	else
		det = -1;
	Set(index + det);
}
