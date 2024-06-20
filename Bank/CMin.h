#ifndef CMinH
#define CMinH
class CMin
{
private:
	bool was;
	int val;
public:
	CMin(void);
	void Add(int _val);

	inline int Val(void)
	{
		return (val);
	}

	inline bool Was(void)
	{
		return (was);
	}
};
#endif
