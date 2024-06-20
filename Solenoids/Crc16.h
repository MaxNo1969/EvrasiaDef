#ifndef Crc16H
#define Crc16H

class Crc16
{
private:
	static unsigned short CrcTable[];

public:
	static unsigned short Compute(unsigned char* _data, int _length);
	static void Add(unsigned char* _data, int _length);
	static bool Check(unsigned char* _data, int _length);
		// {
		// ushort crc=Compute(_data, _data.Length-2);
		// _data[_data.Length - 1] = Convert.ToByte(crc >> 8);
		// _data[_data.Length - 2] = Convert.ToByte(crc & 0xff);
		// }
		// public static bool Check(byte[] _data)
		// {
		// ushort crc = Compute(_data, _data.Length - 2);
		// if (_data[_data.Length - 1] != Convert.ToByte(crc >> 8))
		// return (false);
		// if(_data[_data.Length - 2] != Convert.ToByte(crc & 0xff))
		// return (false);
		// return (true);
		// }
		//
	};
#endif
