#include "stdafx.h"
#include "IOSwitcher.h"
#include <fstream>
#include <memory>
#include <cstring>


CIOSwitcher::CIOSwitcher(const bool inFromFile, const string inFileName) : _from_file(inFromFile)
{
	if (_from_file)
		_pfile_stream = new ifstream(inFileName);
	else
		_pfile_stream = &cin;
}

bool CIOSwitcher::getline(string& out_string) const
{
	const int sz = 4096;

	char tmp[sz];
	tmp[0] = 0;
	//std::memset(&tmp, 0, sizeof(tmp));
	_pfile_stream->getline(tmp, sz);

	out_string.assign(tmp);

	//::getline(*_pfile_stream, &tmp);
	return _pfile_stream->good();
}


CIOSwitcher::~CIOSwitcher()
{
	if (!_from_file)
		return;

	ifstream* fs = static_cast<ifstream*>(_pfile_stream);
	if (fs->is_open())
		fs->close();
	delete(_pfile_stream);
}