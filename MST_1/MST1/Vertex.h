#pragma once

class CVertex
{
public:
	CVertex(const int id)
	{
		_id = id;
	}

	int get_id() const { return _id; }

private:
	int _id;
};

