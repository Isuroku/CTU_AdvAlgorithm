#pragma once

class CVertex
{
public:
	CVertex(const int id)
	{
		_id = id;
		_parent = NULL;
	}

	int get_id() const { return _id; }

	int get_fid() const
	{
		if(_parent == NULL)
			return _id;

		return _parent->get_fid();
	}

	CVertex* get_frag()
	{
		if (_parent == NULL)
			return this;

		return _parent->get_frag();
	}

	void set_parent(CVertex* parent) { _parent = parent; }
	void reset_fid() { _parent = NULL; }

private:
	int _id;
	CVertex* _parent;
};

