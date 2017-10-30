#pragma once
#include <cstddef>
#include <vector>

using namespace std;

class CVertexT
{

public:
	size_t _id;
	int index;
	int lowlink;
	bool dest;
	CVertexT* pred;
	bool instack;
	size_t comp_index;
	vector<CVertexT*> neighbours;
	vector<CVertexT*> rear_neighbours;
	vector<size_t> wayfarers;

	size_t get_wayfarer_count() const { return wayfarers.size(); };

	CVertexT() : _id(0), index(0), lowlink(0), dest(false), pred(NULL), instack(false), comp_index(-1) {}
	/*CVertexTT(int in_id) : index(0), lowlink(0), pred(NULL), instack(false), _id(in_id) {}*/


	size_t id() const { return _id; }
	void set_id(const size_t in_id) { _id = in_id; }

	size_t vec_index() const { return _id - 1; }
};