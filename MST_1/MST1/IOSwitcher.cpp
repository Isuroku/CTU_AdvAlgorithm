#include "IOSwitcher.h"
#include <fstream>
#include <string>


CIOSwitcher::CIOSwitcher(const bool inFromFile, const string inFileName): _from_file(inFromFile)
{
	if(_from_file)
		_pfile_stream = new ifstream(inFileName);
	else
		_pfile_stream = &cin;
}

bool CIOSwitcher::getline(string& out_string)
{
	::getline(*_pfile_stream, out_string);
	return !_pfile_stream->eof();
}


CIOSwitcher::~CIOSwitcher()
{
	if (_from_file)
	{
		ifstream* fs = static_cast<ifstream*>(_pfile_stream);
		if (fs->is_open())
			fs->close();
		delete(_pfile_stream);
	}
}