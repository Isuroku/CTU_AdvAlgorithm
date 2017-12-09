#pragma once

#include <cstring>
#include <string>
#include <vector>

using namespace std;

class SStringGen
{
	string _alphabet;
	vector<size_t> _current;

	char* _out_buff;
	size_t _buff_len;

	bool Inc()
	{
		for(size_t i = _current.size() - 1; i < _current.size(); i--)
		{
			size_t val = _current[i];
			val++;
			bool norm = val < _alphabet.length();
			if(norm)
			{
				_current[i] = val;
				return true;
			}
			val = 0;
			_current[i] = val;
		}

		return false;
	}

public:
	SStringGen(const string alphabet):_alphabet(alphabet)
	{
		_buff_len = 1000;
		_out_buff = new char[_buff_len];
	}

	string GetNext()
	{
		if(!Inc())
			_current.push_back(0);

		if(_current.size() + 1 > _buff_len)
		{
			delete[] _out_buff;
			_buff_len *= 2 + 1000;
			_out_buff = new char[_buff_len];
		}

		for(size_t i = 0; i < _current.size(); i++)
		{
			_out_buff[i] = _alphabet[_current[i]];
		}
		_out_buff[_current.size()] = 0;

		return string(_out_buff);
	}
};
