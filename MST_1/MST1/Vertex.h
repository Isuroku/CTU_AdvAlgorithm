#pragma once

#include <vector>
using namespace std;

class CVertex
{
public:
	CVertex()
	{
		_id = 0;
		_parent = NULL;
		_frag_length = 0;
		_frag_rank = 1;
		_wave_num = 0;
	}

	void Init(const int id)
	{
		_id = id;
		_frag_length = 0;
		_frag_rank = 1;
		_parent = NULL;
		_wave_num = 0;
	}

	int get_id() const { return _id; }
	int get_wave_num() const { return _wave_num; }

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

		CVertex* frag = _parent->get_frag();

		if (frag != _parent)
			_parent = frag;

		return frag;
	}

	CVertex* get_parent() { return _parent;	}

	void set_parent(CVertex* parent) { _parent = parent; }

	void set_frag_length(const int frag_length)
	{
		_frag_length = frag_length;
	}

	void inc_rank()
	{
		_frag_rank++;
	}

	void reset()
	{
		_frag_length = 0;
		_frag_rank = 1;
		_parent = NULL;
	}

	void add_neighbour(CVertex* vertex)
	{
		_neighbours.push_back(vertex);
	}

	void set_wave_num(const int wave_num) { _wave_num = wave_num; }
	void inc_wave_num() { _wave_num++; }

	size_t get_neighbour_count() { return _neighbours.size(); }
	CVertex* get_neighbour(size_t index) { return _neighbours[index]; }

private:
	int _id;
	int _frag_length;
	int _frag_rank;
	CVertex* _parent;

	vector< CVertex* > _neighbours;

	int _wave_num;
};

