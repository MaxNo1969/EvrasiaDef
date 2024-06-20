#pragma hdrstop
#include <VCLTee.Series.hpp>
#include "Filters.h"
#include "Protocol.h"
#include "uFunctions.h"
#include "PA.h"
#pragma package(smart_init)
// ------------------------------------------------------------------------------
Filters *LinearFilterIn;
Filters *LinearFilterOut;
Filters *CrossFilter;

// ------------------------------------------------------------------------------
Filters::Settings::Settings(AnsiString _type)
{
	type = _type;
}

// ------------------------------------------------------------------------------
void Filters::Settings::Load(void)
{
	PA pa;
	if (type == "Cross")
		pa = PA("Defect.Cross.Filter");
	else if (type == "Line")
		pa = PA("Defect.Line.Filter");
	else if (type == "LineIn")
		pa = PA("Defect.Line.FilterIn");
	else
	{
		AnsiString a = "Filters::Settings::Load: Не верный тип: ";
		a += type;
		FATAL(a);
	}
	isFilter = pa.Item("IsFilter").Bool();
	CurrentType = pa.Item("CurrentType").Int();
	CurrentSubType = pa.Item("CurrentSubType").Int();
	order = pa.Item("Order").Int();
	cutoffFrequency = pa.Item("CutoffFrequency").Double();
	centerFrequency = pa.Item("CenterFrequency").Double();
	widthFrequency = pa.Item("WidthFrequency").Double();
	rippleDb = pa.Item("RippleDb").Double();
	rolloff = pa.Item("Rolloff").Double();
	sampleRate = PA("Defect.L502.FrequencyPerChannel").Double();
}

// ------------------------------------------------------------------------------
void Filters::Settings::Save(void)
{
	PA pa;
	if (type == "Cross")
		pa = PA("Defect.Cross.Filter");
	else if (type == "Line")
		pa = PA("Defect.Line.Filter");
	else if (type == "LineIn")
		pa = PA("Defect.Line.FilterIn");
	else
	{
		AnsiString a = "Filters::Settings::Load: Не верный тип: ";
		a += type;
		FATAL(a);
	}
	pa.Item("IsFilter").Write(isFilter);
	pa.Item("CurrentType").Write(CurrentType);
	pa.Item("CurrentSubType").Write(CurrentSubType);
	pa.Item("Order").Write(order);
	pa.Item("CutoffFrequency").Write(cutoffFrequency);
	pa.Item("CenterFrequency").Write(centerFrequency);
	pa.Item("WidthFrequency").Write(widthFrequency);
	pa.Item("RippleDb").Write(rippleDb);
	pa.Item("Rolloff").Write(rolloff);
	PA("Defect.L502.FrequencyPerChannel").Write(sampleRate);
}

// ------------------------------------------------------------------------------
void Filters::Settings::Save(FILE* _df)
{
	fwrite(&isFilter, sizeof(isFilter), 1, _df);
	fwrite(&CurrentType, sizeof(CurrentType), 1, _df);
	fwrite(&CurrentSubType, sizeof(CurrentSubType), 1, _df);
	fwrite(&order, sizeof(order), 1, _df);
	fwrite(&cutoffFrequency, sizeof(cutoffFrequency), 1, _df);
	fwrite(&widthFrequency, sizeof(widthFrequency), 1, _df);
	fwrite(&centerFrequency, sizeof(centerFrequency), 1, _df);
	fwrite(&rippleDb, sizeof(rippleDb), 1, _df);
	fwrite(&rolloff, sizeof(rolloff), 1, _df);
	fwrite(&sampleRate, sizeof(sampleRate), 1, _df);
}

// ------------------------------------------------------------------------------
void Filters::Settings::Load(FILE* _df)
{
	Fread(&isFilter, sizeof(isFilter), 1, _df);
	Fread(&CurrentType, sizeof(CurrentType), 1, _df);
	Fread(&CurrentSubType, sizeof(CurrentSubType), 1, _df);
	Fread(&order, sizeof(order), 1, _df);
	Fread(&cutoffFrequency, sizeof(cutoffFrequency), 1, _df);
	Fread(&widthFrequency, sizeof(widthFrequency), 1, _df);
	Fread(&centerFrequency, sizeof(centerFrequency), 1, _df);
	Fread(&rippleDb, sizeof(rippleDb), 1, _df);
	Fread(&rolloff, sizeof(rolloff), 1, _df);
	Fread(&sampleRate, sizeof(sampleRate), 1, _df);
}

// ------------------------------------------------------------------------------
Filters::Filters(AnsiString _type) : settings(_type)
{
	dllInstance = LoadLibrary(L"filters.dll");

	if (!dllInstance)
	{
		String strError = L"Не удалось загрузить библиотеку фильтров";
		MessageBox(NULL, strError.w_str(), L"Ошибка", MB_ICONERROR | MB_OK);
	}
	else
	{
		filter_chebyshev = (_ChebyshevI) GetProcAddress(dllInstance,
			"ChebyshevI");
		filter_butterworth = (_Butterworth) GetProcAddress(dllInstance,
			"Butterworth");
		filter_elliptic = (_Elliptic) GetProcAddress(dllInstance, "Elliptic");
		LoadSettings();
	}
}

// ------------------------------------------------------------------------------
void Filters::toFilter(double *data, int N)
{
	if (!settings.isFilter)
		return;
	switch (settings.CurrentType)
	{
	case 0:
		{
			filter_butterworth(data, N, settings.order, settings.sampleRate,
				settings.cutoffFrequency, settings.centerFrequency,
				settings.widthFrequency, settings.CurrentSubType);
			break;
		}
	case 1:
		{
			filter_chebyshev(data, N, settings.order, settings.sampleRate,
				settings.cutoffFrequency, settings.centerFrequency,
				settings.widthFrequency, settings.rippleDb,
				settings.CurrentSubType);
			break;
		}
	case 2:
		{
			filter_elliptic(data, N, settings.order, settings.sampleRate,
				settings.cutoffFrequency, settings.centerFrequency,
				settings.widthFrequency, settings.rippleDb, settings.rolloff,
				settings.CurrentSubType);
			break;
		}
	}
}

// ------------------------------------------------------------------------------
void Filters::LoadSettings()
{
	settings.Load();
}

// ------------------------------------------------------------------------------
void Filters::Save(FILE* _df)
{
	settings.Save(_df);
}
// ------------------------------------------------------------------------------
