#pragma once
#include <sstream>

class CVertex;

class CEdge
{
public:
	CEdge() : _length(0)
	{
		_v[0] = NULL;
		_v[1] = NULL;
	}

	CEdge(CVertex* v1, CVertex* v2, const int length): _length(length)
	{
		_v[0] = v1;
		_v[1] = v2;
	}

	void init(CVertex* v1, CVertex* v2, const int length)
	{
		_length = length;
		_v[0] = v1;
		_v[1] = v2;
	}

	int length() const { return _length; }
	int priority() const { return _priority; }

	void set_priority(const int value) { _priority = value; }

	string name() const 
	{ 
		ostringstream ss;
		ss << _v[0]->get_id() + 1 << "-" << _v[1]->get_id() + 1;
		return ss.str();
	}

	CVertex* get_vertex(const bool left) { return left ? _v[0] : _v[1]; }

private:
	CVertex* _v[2];

	int _length;
	int _priority;
};

