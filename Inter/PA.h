//---------------------------------------------------------------------------
#ifndef PAH
#define PAH
#include <Forms.hpp>

//---------------------------------------------------------------------------
class PA
{
private:
	AnsiString path;
	static AnsiString Parce(TStringList* _L,bool* _ret);
	static void CheckError(AnsiString _cmd,AnsiString _result);
	static AnsiString Val(AnsiString _cmd,AnsiString _result);
public:
	PA();
	PA(AnsiString _path);
	PA Item(AnsiString _path);
	bool Bool(void);
	int Int(void);
	float Float(void);
	double Double(void);
	AnsiString String(void);

	void Write(Variant _val);
	AnsiString ToString();
	void LoadFormPos(TForm* _form);
	void SaveFormPos(TForm* _form);
	int GetCount(void);
	bool IsNull(void);
	PA operator[](int _index);
	PA operator[](AnsiString _name);
	bool Exist(void);
	static void Dispose(void);
	static bool GetSignal(AnsiString _name);
	static void SetSignal(AnsiString _name,bool _val);
	static DWORD RemoteGetTickCount(void);
};
//---------------------------------------------------------------------------
#endif
