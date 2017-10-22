#pragma once
#include "MainHeader.h"

class CIOSwitcher
{
public:
	CIOSwitcher(bool inFromFile, const string inFileName);
	~CIOSwitcher();

	bool CIOSwitcher::get_line(string& out_string) const;

private:
	bool _from_file;
	istream* _pfile_stream;
};

