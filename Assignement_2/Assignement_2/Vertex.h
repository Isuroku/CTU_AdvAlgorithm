#pragma once
#include <cstddef>
#include <vector>

using namespace std;

class CVertexT
{

public:
	int _id;
	int index;
	int lowlink;
	bool isDestination;
	CVertexT* pred;
	bool instack;
	int wayfarer_count;
	size_t comp_index;
	vector<CVertexT*> neighbours;
	

	CVertexT(): _id(0), index(0), lowlink(0), isDestination(false), pred(NULL), instack(false), wayfarer_count(0), comp_index(-1) {}
	/*CVertexTT(int in_id) : index(0), lowlink(0), pred(NULL), instack(false), _id(in_id) {}*/


	int GetID() const { return _id; }
	void SetID(int in_id) { _id = in_id; }
	void SetNeighbours(CVertexT* in_n)	{	neighbours.push_back(in_n);	}
};