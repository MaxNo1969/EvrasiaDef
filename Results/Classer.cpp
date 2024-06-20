#pragma hdrstop
#include "Classer.h"
#include "uFunctions.h"
#include "PA.h"
#pragma package(smart_init)
Classer* Classer::Instance = NULL;

Classer::Classer(void)
{
	LoadSettings0();
}

void Classer::LoadSettings0(void)
{
	PA pa("Colors");
	brack = (TColor)pa.Item("eBrak").Int();
	class2 = (TColor)pa.Item("eClass2").Int();
	good = (TColor)pa.Item("eClass1").Int();
	dead = (TColor)pa.Item("eNotMeasured").Int();
}

TColor Classer::ClassColor0(int _class)
{
	if (_class == 0)
		return (brack);
	else if (_class == 1)
		return (class2);
	else if (_class == 2)
		return (good);
	else
		return (dead);
}
AnsiString Classer::ClassString0(int _class)
{
	if (_class == 0)
		return ("Брак");
	else if (_class == 1)
		return ("Класс 2");
	else if (_class == 2)
		return ("Годно");
	else
		return ("Не измерено");
}
char Classer::ClassChar0(int _class)
{
	if (_class == 0)
		return ('Б');
	else if (_class == 1)
		return ('2');
	else if (_class == 2)
		return ('Г');
	else
		return ('?');
}

int Classer::Class(double _level, double* _borders)
{
	if (_level < 0)
		_level = -_level;
	int cl = 0;
	if (_borders[1] == 0)
	{
		if (_level < _borders[0])
			cl = 2;
		else
			cl = 0;

	}
	else
	{
		if (_level < _borders[1])
			cl = 2;
		else if (_level < _borders[0])
			cl = 1;
		else
			cl = 0;
	}
	return (cl);
}

int Classer::ClassThick(double _level, double* _borders)
{
	if (_level == 10.0)
		return -1;
	if (_borders[1] == 0)
	{
		if (_level > _borders[0])
			return (2);
		return (0);
	}
	else
	{
		if (_level > _borders[0])
			return (2);
		if (_level > _borders[1])
			return (1);
		return (0);
	}
}

int Classer::Check(double _level)
{
	int ret = (int)_level;
	if (ret < -1 || ret > 2)
		FATAL("Classer::Check: не корректный класс");
	return (ret);
}

void Classer::Dispose(void)
{
	if (Instance != NULL)
		delete Instance;
	Instance = NULL;
}

void Classer::LoadSettings(void)
{
	if (Instance == NULL)
		Instance = new Classer();
	Instance->LoadSettings0();
}

TColor Classer::ClassColor(int _class)
{
	if (Instance == NULL)
		Instance = new Classer();
	return (Instance->ClassColor0(_class));
}

TColor Classer::ClassColor(double _level, double* _borders)
{
	return (ClassColor(_level, _borders, false));
}

TColor Classer::ClassColor(double _level, double* _borders, bool _dead)
{
	if (Instance == NULL)
		Instance = new Classer();
	if (_dead)
		return (Instance->dead);
	return (Instance->ClassColor0(Class(_level, _borders)));
}

AnsiString Classer::ClassString(int _class)
{
	if (Instance == NULL)
		Instance = new Classer();
	return (Instance->ClassString0(_class));
}
char Classer::ClassChar(int _class)
{
	if (Instance == NULL)
		Instance = new Classer();
	return (Instance->ClassChar0(_class));
}

TColor Classer::Dead()
{
	if (Instance == NULL)
		Instance = new Classer();
	return (Instance->dead);
}

TColor Classer::Brack()
{
	if (Instance == NULL)
		Instance = new Classer();
	return (Instance->brack);
}

TColor Classer::Class2()
{
	if (Instance == NULL)
		Instance = new Classer();
	return (Instance->class2);
}

TColor Classer::Good()
{
	if (Instance == NULL)
		Instance = new Classer();
	return (Instance->good);
}
