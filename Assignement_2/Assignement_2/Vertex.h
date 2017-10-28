#pragma once
#include <cstddef>
#include <vector>

using namespace std;

class CVertex
{

public:
	int index;
	int lowlink;
	bool isDestination;
	CVertex* pred;
	bool instack;
	int weight;
	vector<CVertex*> neighbours;

	CVertex(): index(0), lowlink(0), pred(NULL), instack(false), _id(0), isDestination(false), weight(1) {}
	/*CVertex(int in_id) : index(0), lowlink(0), pred(NULL), instack(false), _id(in_id) {}*/


	int GetID() const { return _id; }
	void SetID(int in_id) { _id = in_id; }
	void SetNeighbours(CVertex* in_n)	{	neighbours.push_back(in_n);	}

private:
	int _id;
};