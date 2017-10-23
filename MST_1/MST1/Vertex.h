#pragma once

class CVertex
{
public:
	CVertex()
	{
		_id = 0;
		_parent = NULL;
		_frag_length = 0;
		_frag_rank = 1;
	}

	void Init(const int id)
	{
		_id = id;
		_frag_length = 0;
		_frag_rank = 1;
		_parent = NULL;
	}

	int get_id() const { return _id; }

	int get_fid() const
	{
		if(_parent == NULL)
			return _id;

		return _parent->get_fid();
	}

	int get_frag_length() const
	{
		if (_parent == NULL)
			return _frag_length;

		return _parent->get_frag_length();
	}

	int get_frag_rank() const
	{
		if (_parent == NULL)
			return _frag_rank;

		return _parent->get_frag_rank();
	}

	CVertex* get_frag()
	{
		if (_parent == NULL)
			return this;

		return _parent->get_frag();
	}

	void set_parent(CVertex* parent)
	{
		if (_parent != NULL)
		{
			cerr << "error set_parent: already have parent!" << endl;
			return;
		}
		_parent = parent;
	}

	void set_frag_length(const int frag_length)
	{
		if (_parent != NULL)
		{
			cerr << "error set_frag_length: vertex has parent!" << endl;
			return;
		}
		_frag_length = frag_length;
	}

	void set_frag_rank(const int frag_rank)
	{
		if (_parent != NULL)
		{
			cerr << "error set_frag_rank: vertex has parent!" << endl;
			return;
		}
		_frag_rank = frag_rank;
	}

	void reset()
	{
		_frag_length = 0;
		_frag_rank = 1;
		_parent = NULL;
	}

private:
	int _id;
	int _frag_length;
	int _frag_rank;
	CVertex* _parent;
};

