#ifndef ClasserH
#define ClasserH
#include <Graphics.hpp>
/* TODO : Классер перегружать перед каждой трубой */
class Classer
{
private:
	static Classer* Instance;

	Classer(void);

	TColor dead;
	TColor brack;
	TColor class2;
	TColor good;

	void LoadSettings0(void);
	TColor ClassColor0(int _class);
	AnsiString ClassString0(int _class);
	char ClassChar0(int _class);

public:
	static int Class(double _level, double* _borders);
	static int ClassThick(double _level, double* _borders);
	static int Check(double _level);
	static void Dispose(void);
	static TColor ClassColor(int _class);
	static TColor ClassColor(double _level, double* _borders);
	static TColor ClassColor(double _level, double* _borders, bool _dead);
	static AnsiString ClassString(int _class);
	static char ClassChar(int _class);
	static void LoadSettings(void);
	static TColor Dead();
	static TColor Brack();
	static TColor Class2();
	static TColor Good();
};
#endif
