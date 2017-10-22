#pragma once

class CVertex;

class CEdge
{
public:
	CEdge(CVertex* v1, CVertex* v2, const int length): _length(length)
	{
		_v1[0] = v1;
		_v1[1] = v2;
	}

private:
	CVertex* _v1[2];
	int _length;
};

