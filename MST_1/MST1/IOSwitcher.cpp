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

bool CIOSwitcher::getline(string& out_string) const
{
	char tmp[128];
	memset(&tmp, 0, sizeof tmp);
	_pfile_stream->getline(tmp, 128);

	out_string.assign(tmp);

	//::getline(*_pfile_stream, &tmp);
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