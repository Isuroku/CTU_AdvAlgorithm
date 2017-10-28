#pragma once
#include <cstddef>
#include <vector>

using namespace std;

class CVertexT
{

public:
	int index;
	int lowlink;
	bool isDestination;
	CVertexT* pred;
	bool instack;
	int wayfarer_count;
	vector<CVertexT*> neighbours;

	CVertexT(): index(0), lowlink(0), isDestination(false), pred(NULL), instack(false), wayfarer_count(0), _id(0) {}
	/*CVertexTT(int in_id) : index(0), lowlink(0), pred(NULL), instack(false), _id(in_id) {}*/


	int GetID() const { return _id; }
	void SetID(int in_id) { _id = in_id; }
	void SetNeighbours(CVertexT* in_n)	{	neighbours.push_back(in_n);	}

private:
	int _id;
};