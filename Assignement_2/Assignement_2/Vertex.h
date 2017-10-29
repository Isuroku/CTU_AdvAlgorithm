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
	bool isDestination;
	CVertexT* pred;
	bool instack;
	int wayfarer_count;
	size_t comp_index;
	vector<CVertexT*> neighbours;
	vector<CVertexT*> rear_neighbours;
	

	CVertexT(): _id(0), index(0), lowlink(0), isDestination(false), pred(NULL), instack(false), wayfarer_count(0), comp_index(-1) {}
	/*CVertexTT(int in_id) : index(0), lowlink(0), pred(NULL), instack(false), _id(in_id) {}*/


	size_t id() const { return _id; }
	void set_id(const size_t in_id) { _id = in_id; }

	size_t vec_index() const { return _id - 1; }
};