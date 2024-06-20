#include <vcl.h>
#pragma hdrstop
#include <algorithm>
#include <time.h>
#include "uTFRSOPCheck.h"
#include "uCDBS.h"
#include "Singleton.h"
#include "protocol.h"
#include "uFunctions.h"
#include "uCExecSQL.h"
#include "uCSelect.h"
#include "PA.h"
#include "Classer.h"
#include "Filters.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFRSOPCheck *FRSOPCheck;

// ---------------------------------------------------------------------------
__fastcall TFRSOPCheck::TFRSOPCheck(TComponent* Owner) : TFrame(Owner)
{
	OnUpdate = NULL;
}

// ---------------------------------------------------------------------------
void TFRSOPCheck::Init(AnsiString _user, AnsiString _group)
{
	user = _user;
	group = _group;
	mCheckedDefects->Clear();
	mCheckedDefects->Lines->Clear();
}

// ---------------------------------------------------------------------------
void TFRSOPCheck::Exec(AnsiString _SOP, AnsiString _TypeSize)
{
	mCheckedDefects->Clear();
	mCheckedDefects->Lines->Clear();
	SOP = _SOP;
	TypeSize = _TypeSize;
	EtalonCheck();
	// Закроем кнопку "сохранить" в случае загруженной трубы
	// bSave->Enabled = !Singleton->FromFile;
}

// ---------------------------------------------------------------------------
void TFRSOPCheck::EtalonCheck()
{
	SetData();
	AnsiString Str = "";
	numOfDefects = 0;
	matchedDefects = 0;
	// Идем по списку дефектов эталона
	AnsiString SQL;
	SQL = "SELECT * FROM EtalonTubeDefects ";
	SQL += "where SOP='" + SOP + "'";
	SQL += " order by id";
	for (CSelect S(SQL); !S.Eof(); S.Next())
	{
		numOfDefects++;
		// Читаем данные
		AnsiString Module = S.AsAnsiString("Module");
		AnsiString DefType = S.AsAnsiString("DefType");
		int DefPoint = S.AsInt("DefPoint");
		int DefRadius = S.AsInt("DefRadius");
		bool isTopBrackBorder = S.AsBool("isTopBrackBorder");
		double TopBorderPercent = S.AsDouble("TopBorderPercent");
		bool isBottomBrackBorder = S.AsBool("isBottomBrackBorder");
		double BottomBorderPercent = S.AsDouble("BottomBorderPercent");
		// проверяем дефект
		if (DefectCheck(Module, DefType, DefPoint, DefRadius, isTopBrackBorder, TopBorderPercent, isBottomBrackBorder,
			BottomBorderPercent))
		{
			matchedDefects++;
			AddMemoResult(true, Module, DefPoint);
		}
		else
			AddMemoResult(false, Module, DefPoint);
	}
	Str = IntToStr(matchedDefects) + " из " + IntToStr(numOfDefects);
	pResultNum->Caption = Str;
	if (matchedDefects == numOfDefects)
	{
		pResultBit->Caption = "Совпадает";
		pResultBit->Color = clGreen;
		if (group == "Master")
			bSave->Enabled = true;
		else
		{
			if (!Singleton->FromFile)
				bSave->Enabled = true;
		}
	}
	else
	{
		pResultBit->Caption = "Ошибка";
		pResultBit->Color = clRed;
		if (group == "Master")
			bSave->Enabled = true;
		else
		{
			if (!Singleton->FromFile)
				bSave->Enabled = true;
		}
	}
	pResultNum->Color = pResultBit->Color;
	// eDate->Text = DateTimeToStr((Date() + Time()));
	Str = "Закончили расчет дефектов эталона: " + pResultBit->Caption + " " + pResultNum->Caption;
	TPr::pr(Str);

}

// ----------------------------------------------------------------------------
bool TFRSOPCheck::DefectCheck(AnsiString _Module, AnsiString _DefType, int _DefPoint, int _DefRadius, bool _isTopBrackBorder,
	double _TopBorderPercent, bool _isBottomBrackBorder, double _BottomBorderPercent)
{
	// Алгоритм сверки:
	// Для каждого Дефекта
	// Для каждого датчика
	// проверяем диапозон поиска
	// Результат пишем в массив
	// Проверяем массив на соответствие типу дефекта
	// Если подходит, то возвращаем True
	// Иначе возвращаем False
	// список границ диапозонов поиска
	int startPoint = _DefPoint - _DefRadius;
	int endPoint = _DefPoint + _DefRadius;

	int sensorMax = 0;
	if (_Module == "Поперечный") // Поперечник
			sensorMax = Singleton->Tube->Cross.GetSensorsCount();
	else if (_Module == "Продольный") // Продольник
			sensorMax = Singleton->Tube->Line.GetSensorsCount();
	else if (_Module == "Толщиномер") // Толщиномер
			sensorMax = 1;
	else
	{
		TPr::pr("Ошибка: Неизвестен модуль дефекта");
		return false;
	}
	// Проверяем, что дефект находится в пределах трубы
	int startZone = startPoint / 200;
	int endZone = endPoint / 200;
	if (_Module == "Поперечный")
	{
		if (Singleton->Tube->Cross.Size() < endZone || startZone < 0)
		{
			TPr::pr("Дефект по поперечному модулю за пределами трубы");
			Application->MessageBoxW(L"Дефект эталона по поперечному модулю за пределами трубы!", L"Предупреждение!",
				MB_ICONWARNING);
			return false;
		}
	}
	else if (_Module == "Продольный")
	{
		if (Singleton->Tube->Line.Size() < endZone || startZone < 0)
		{
			TPr::pr("Дефект по продольному модулю за пределами трубы");
			Application->MessageBoxW(L"Дефект эталона по продольному модулю за пределами трубы!", L"Предупреждение!",
				MB_ICONWARNING);
			return false;
		}
	}
	else if (_Module == "Толщиномер")
	{
		if (Singleton->Tube->Thick.Size() < endZone || startZone < 0)
		{
			TPr::pr("Дефект по толщиномеру за пределами трубы");
			Application->MessageBoxW(L"Дефект эталона по толщиномеру за пределами трубы!", L"Предупреждение!", MB_ICONWARNING);
			return false;
		}
	}
	// Проверяем зону поиска
	vector<int>dirtyFind;
	for (int sens = 0; sens < sensorMax; sens++)
	{
		dirtyFind.push_back(0); // Ниже нижней границы
		if (_TopBorderPercent != 0) // Если указана верхняя граница
		{
			if (CheckDiap(_Module, sens, _isTopBrackBorder, _TopBorderPercent, startPoint, endPoint))
				dirtyFind[sens] = 2; // Выше верхней границы
			else
				dirtyFind[sens] = 1; // Ниже верхней границы
		}
		if ((_BottomBorderPercent != 0) && (dirtyFind[sens] != 2))
			// Если указана нижняя граница
		{
			if (CheckDiap(_Module, sens, _isBottomBrackBorder, _BottomBorderPercent, startPoint, endPoint))
				dirtyFind[sens] = 1; // Между верхней и нижней границами
			else
				dirtyFind[sens] = 0; // Ниже нижней границы
		}
	}

	AnsiString Str = "DirtyFind = [";
	for (int i = 0; i < (int)dirtyFind.size(); i++)
		Str += IntToStr(dirtyFind[i]);
	Str += "]";
	TPr::pr(Str);

	// Проверяем на соответствие типу дефекта
	bool Result = false;
	Result = CheckDefType(_Module, _DefType, dirtyFind);
	return Result;
}

// ----------------------------------------------------------------------------
void TFRSOPCheck::SetData()
{
	// Поперечник
	// CrossFilteredOut_Data = Singleton->CrossResult->GetFilteredOut_Data();
	// CrossGain = Singleton->CrossResult->GetGain();
	// CrossDeads = Singleton->CrossResult->GetDeads();
	// Продольник
	// LinearFilteredOut_Data = Singleton->LinearResult->GetFilteredOut_Data();
	// if (Singleton->LinearResult->isLinearDigitalFilterIn)
	// LinearFilteredIn_Data = Singleton->LinearResult->GetFilteredIn_Data();
	// LinearGain = Singleton->LinearResult->GetGain();
	// LinearDeads = Singleton->LinearResult->GetDeads();
}

// ----------------------------------------------------------------------------
bool TFRSOPCheck::CheckDiap(AnsiString _Module, int _sensor, bool _isBrackBorder, double _borderPercent, int _startPoint,
	int _endPoint)
{
	CCrossLine* CL = NULL;
	if (_Module == "Поперечный") // Поперечник
			CL = &Singleton->Tube->Cross;
	else if (_Module == "Продольный")
		CL = &Singleton->Tube->Line;
	int startZone = _startPoint / CL->ZoneLength;
	int endZone = _endPoint / CL->ZoneLength;
	double borderCoefficient = 100.0 / _borderPercent;
	bool inner = CL->Tp == CMeas::TP::Line && LinearFilterIn->IsFilter();

	if (_Module == "Поперечный" || _Module == "Продольный")
	{
		if (CL->GetSensorsCount() < _sensor || _sensor < 0)
		{
			TPr::pr("Ошибка: Неправильно указан датчик для сверки с эталоном");
			Application->MessageBoxW(L"Ошибка: Неправильно указан датчик для сверки с эталоном", L"Предупреждение!",
				MB_ICONWARNING);
			return false;
		}
		int startMeasure = (int) CL->MZone[startZone]->MSensor[0]->Size() * (_startPoint % 200) / 200;
		int endMeasure = (int) CL->MZone[endZone]->MSensor[0]->Size() * (_endPoint % 200) / 200;
		// Если обе точки в одной зоне
		if (startZone == endZone)
		{
			CSensor* S = CL->MZone[startZone]->MSensor[_sensor];
			for (int j = startMeasure; j < endMeasure; j++)
			{
				TColor col = Classer::ClassColor(S->MMeas[j]->FilterOut * CL->MSensor2[_sensor]->Gain * borderCoefficient, false);
				if (_isBrackBorder)
				{
					if (col == Classer::Brack())
						return true;
				}
				else
				{
					if (col != Classer::Good())
						return true;

				}
				if (inner)
				{
					TColor col =
						Classer::ClassColor(S->MMeas[j]->FilterIn * CL->MSensor2[_sensor]->Gain * borderCoefficient, false);
					if (_isBrackBorder)
					{
						if (col == Classer::Brack())
							return true;
					}
					else
					{
						if (col != Classer::Good())
							return true;
					}
				}
			}
		}
		else // если в разных
		{
			// проверим начальную зону
			CSensor* S = CL->MZone[startZone]->MSensor[_sensor];
			for (int j = startMeasure; j < S->Size(); j++)
			{
				TColor col =
					Classer::ClassColor(CL->MZone[startZone]->MSensor[_sensor]->MMeas[j]->FilterOut * CL->MSensor2[_sensor]
					->Gain * borderCoefficient, false);
				if (_isBrackBorder)
				{
					if (col == Classer::Brack())
						return true;
				}
				else
				{
					if (col != Classer::Good())
						return true;
				}
				if (inner)
				{
					TColor col = Classer::ClassColor(S->MMeas[j]->FilterIn * CL->MSensor2[_sensor]->Gain * borderCoefficient,
					false);
					if (_isBrackBorder)
					{
						if (col == Classer::Brack())
							return true;
					}
					else
					{
						if (col != Classer::Good())
							return true;
					}
				}
			}
			// проверим промежуточные зоны
			for (int zone = startZone + 1; zone < endZone; zone++)
			{
				CSensor* Sz = CL->MZone[startZone]->MSensor[_sensor];
				for (int j = 0; j < Sz->Size(); j++)
				{
					TColor col =
						Classer::ClassColor(Sz->MMeas[j]->FilterOut * CL->MSensor2[_sensor]->Gain * borderCoefficient, false);
					if (_isBrackBorder)
					{
						if (col == Classer::Brack())
							return true;
					}
					else
					{
						if (col != Classer::Good())
							return true;
					}
					if (inner)
					{
						TColor col =
							Classer::ClassColor(S->MMeas[j]->FilterIn * CL->MSensor2[_sensor]->Gain * borderCoefficient, false);
						if (_isBrackBorder)
						{
							if (col == Classer::Brack())
								return true;
						}
						else
						{
							if (col != Classer::Good())
								return true;
						}
					}
				}
			}
			// Проверим конечную зону
			S = CL->MZone[endZone]->MSensor[_sensor];
			for (int j = 0; j < endMeasure; j++)
			{
				if (S->Size() <= j)
				{
					AnsiString a = "Размер зоны ";
					a += S->Size();
					a += " за границами ";
					a += j;
					FATAL(a);
				}
				TColor col = Classer::ClassColor(S->MMeas[j]->FilterOut * CL->MSensor2[_sensor]->Gain * borderCoefficient, false);
				if (_isBrackBorder)
				{
					if (col == Classer::Brack())
						return true;
				}
				else
				{
					if (col != Classer::Good())
						return true;
				}
				if (inner)
				{
					TColor col = Classer::ClassColor(S->MMeas[j]->FilterIn * CL->MSensor2[_sensor]->Gain * borderCoefficient,
					false);
					if (_isBrackBorder)
					{
						if (col == Classer::Brack())
							return true;
					}
					else
					{
						if (col != Classer::Good())
							return true;
					}
				}
			}
		}
	}
	else if (_Module == "Толщиномер") // Толщиномер
	{
		for (int j = startZone; j < endZone + 1; j++)
		{
			if (Singleton->Tube->Thick.MZone[j]->Level >= _borderPercent)
				return true;
		}
	}
	return false;
}

// ----------------------------------------------------------------------------
bool TFRSOPCheck::CheckDefType(AnsiString _Module, AnsiString _DefType, vector<int>dirtyFind)
{
	AnsiString a = "CheckDefType: ";
	a += _Module;
	a += " ";
	a += _DefType;
	TPr::pr(a);
	if ((int)dirtyFind.size() == 0)
	{
		AnsiString Str = "Ошибка: Длина DirtyFind = " + IntToStr((int)dirtyFind.size());
		TPr::pr(Str);
		return false;
	}
	if (_Module == "Поперечный") // Поперечник
	{
		// составим список датчиков с дефектами
		std::vector<int>sensDef;
		for (int i = 0; i < (int)dirtyFind.size(); i++)
		{
			if (dirtyFind[i] == 2)
			{
				TPr::pr("Ошибка: Дефект вышел за верхнюю границу на одном из датчиков");
				return false;
			}
			else if (dirtyFind[i] == 1)
			{
				sensDef.push_back(i);
			}
		}
		int DefCount = sensDef.size();
		if (_DefType == "До 3 соседних")
		{
			// зависимость от кол-ва датчиков нашедших дефект
			switch (DefCount)
			{
			case 1:
				TPr::pr("Успех: Дефект найден на 1 датчике поперечного");
				return true;
				break;
			case 2:
				if ((sensDef[1] - sensDef[0]) == 1 || (sensDef[1] - sensDef[0]) == (int)dirtyFind.size() - 1)
				{
					TPr::pr("Успех: Дефект найден на 2 соседних датчиках поперечного");
					return true;
				}
				else
				{
					TPr::pr("Ошибка: Дефект найден на 2 не соседних датчиках поперечного");
					return false;
				}
				break;
			case 3:
				if (sensDef[0] == 0) // если есть вероятность дефекта на стыке
				{
					for (int k = 0; k < 3; k++)
					{
						sensDef[k] += 2;
						sensDef[k] = sensDef[k] % dirtyFind.size();
					}
					std::sort(sensDef.begin(), sensDef.end());
				}
				if ((sensDef[0] + 1 == sensDef[1]) && (sensDef[1] + 1 == sensDef[2]))
				{
					TPr::pr("Успех: Дефект найден на 3 соседних датчиках поперечного");
					return true;
				}
				else
				{
					TPr::pr("Ошибка: Дефект найден на 3 не соседних датчиках поперечного");
					return false;
				}
				break;
			default:
				TPr::pr("Ошибка: Дефект найден на более чем 3 датчиках поперечного или вообще не найден");
				return false;
				break;
			}
		}
		if (_DefType == "Все датчики")
		{
			if (DefCount == (int)dirtyFind.size())
			{
				TPr::pr("Успех: Дефект найден на всех датчиках поперечного");
				return true;
			}
			else
			{
				TPr::pr("Ошибка: Дефект найден не на всех датчиках поперечного или выходит за границы");
				return false;
			}
		}
		else
		{
			TPr::pr("Ошибка: Не определен тип дефекта поперечного");
			return false;
		}
	}

	else if (_Module == "Продольный") // Продольник
	{
		if (_DefType == "Все датчики")
		{
			for (int i = 0; i < (int)dirtyFind.size(); i++)
			{
				if (dirtyFind[i] == 2)
				{
					TPr::pr("Ошибка: Дефект вышел за верхнюю границу на одном из датчиков");
					return false;
				}
				if (dirtyFind[i] != 1)
					// Если хотя бы на одном датчике нет дефекта - ошибка
				{
					TPr::pr("Ошибка: Дефект найден не на всех датчиках продольного");
					return false;
				}
			}
			TPr::pr("Успех: Дефект найден на всех датчиках продольного");
			return true;
			// Если все датчики видят дефект, то дефект совпадает
		}
		else if (_DefType == "1 и более")
		{
			int sensFind = 0;
			for (int i = 0; i < (int)dirtyFind.size(); i++)
			{
				if (dirtyFind[i] == 2)
				{
					TPr::pr("Ошибка: Дефект вышел за верхнюю границу на одном из датчиков");
					return false;
				}
				else if (dirtyFind[i] == 1)
				{
					sensFind++;
				}
			}
			if (sensFind == 0)
			{
				TPr::pr("Ошибка: Дефект не найден ни на одном датчике продольного");
				return false;
			}
			TPr::pr("Успех: Дефект найден на 1 и более датчиках продольного");
			return true;
			// Если хотя бы 1 датчик видит дефект, то дефект совпадает
		}
		else
		{
			TPr::pr("Ошибка: Не определен тип дефекта продольного");
			return false;
		}
	}
	else if (_Module == "Толщиномер") // Толщиномер
	{
		if (_DefType == "Толщина")
		{
			if (dirtyFind[0] == 2)
			{
				TPr::pr("Ошибка: Дефект вышел за верхнюю границу");
				return false;
			}
			if (dirtyFind[0] != 1) // Если нет дефекта - ошибка
			{
				TPr::pr("Ошибка: Дефект толщиномера не найден");
				return false;
			}
			TPr::pr("Успех: Дефект толщиномера найден");
			return true; // Если датчики видят дефект, то дефект совпадает
		}
		else
		{
			TPr::pr("Ошибка: Не определен тип дефекта толщиномера");
			return false;
		}
	}
	TPr::pr("Ошибка: Не определен модуль дефекта");
	return false;
}

// ----------------------------------------------------------------------------
void __fastcall TFRSOPCheck::bSaveClick(TObject *Sender)
{
	// Формируем полное имя нового файла
	AnsiString path = PA("Defect.SOP.SOPPath").String();
	AnsiString FileName = path + "\\SOPCheck_";
	time_t t;
	time(&t);
	tm ltm = *localtime(&t);
	AnsiString fn;
	FileName.cat_printf("%.2d%.2d%.2d_%.2d%.2d%.2d.bindkb", ltm.tm_year - 100, ltm.tm_mon + 1, ltm.tm_mday, ltm.tm_hour,
		ltm.tm_min, ltm.tm_sec);
	Singleton->Save(FileName, user);
	// Сделаем файл скрытым
	UnicodeString unicName = (UnicodeString)FileName;
	int attr = GetFileAttributes(unicName.w_str());
	if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0)
		SetFileAttributes(unicName.w_str(), attr | FILE_ATTRIBUTE_HIDDEN);

	// сохраняем данные о проверке в БД
	AnsiString Str = "";
	AnsiString SQL;
	SQL = "insert into dbo.EtalonCheckResult (SOP,TypeSize,Result,MatchedDefects,NumOfDefects,Defectoscoper,SaveAddress )";
	SQL += " values('";
	SQL += SOP;
	SQL += "','";
	SQL += TypeSize;
	SQL += "','";
	SQL += pResultBit->Caption;
	SQL += "',";
	SQL += IntToStr(matchedDefects);
	SQL += ",";
	SQL += IntToStr(numOfDefects);
	SQL += ",'";
	SQL += user;
	SQL += "','";
	SQL += AnsiString(FileName);
	SQL += "')";

	CExecSQL E(SQL);
	if (E.IsOk() != "Ok")
	{
		Str = " Не смогли сохранить результат проверки эталона !";
		TPr::pr(Str);
		Application->MessageBoxW(L" Не смогли сохранить результат проверки !", L" Предупреждение !", MB_ICONWARNING);
	}
	else
	{
		Str = " Сохранили результат проверки эталона : " + pResultBit->Caption;
		TPr::pr(Str);
		bSave->Enabled = false;
		if (OnUpdate != NULL)
			OnUpdate();
	}
}

// ---------------------------------------------------------------------------
bool TFRSOPCheck::AddMemoResult(bool _matched, AnsiString _module, int _defPoint)
{
	// Формируем сообщение
	AnsiString Str = " ";
	Str += _module;
	Str += " точка " + IntToStr(_defPoint);
	if ((_defPoint % 200) == 0)
		Str += " в зонах " + IntToStr((_defPoint / 200)) + " и ";
	else
		Str += " в зоне ";
	Str += IntToStr((_defPoint / 200) + 1);

	if (_matched)
		Str += " совпала.";
	else
		Str += " не совпала !";

	// Выводим на боковую панель
	mCheckedDefects->Lines->Add(Str);
	return true;
}
// ---------------------------------------------------------------------------

void __fastcall TFRSOPCheck::FrameResize(TObject *Sender)
{
	int space = 2;
	pResultNum->Width = GroupBox1->Width - 2 * pResultNum->Left;
	pResultBit->Width = pResultNum->Width;
	mCheckedDefects->Width = pResultNum->Width;
	bSave->Width = pResultNum->Width;
	bSave->Top = GroupBox1->Height - bSave->Height - space;
	mCheckedDefects->Height = bSave->Top - space - mCheckedDefects->Top;
}
// ---------------------------------------------------------------------------
