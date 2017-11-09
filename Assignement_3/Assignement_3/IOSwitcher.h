#pragma once
#include <iostream>

class CIOSwitcher
{
public:
	CIOSwitcher(bool inFromFile, const string inFileName);
	~CIOSwitcher();

	bool getline(string& out_string) const;

private:
	bool _from_file;
	istream* _pfile_stream;
};

