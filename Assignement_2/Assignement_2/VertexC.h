#pragma once
#include <cstddef>
#include <vector>

using namespace std;

class CVertexTC
{
public:
	int _id;
	
	size_t wayfarer_count;
	size_t weight;

	bool dest;

	vector<CVertexTC*> neighbours;
	vector<CVertexTC*> rear_neighbours;

	CVertexTC() : _id(0), wayfarer_count(0), weight(1), dest(false) {}

	int GetID() const { return _id; }
	void SetID(const int in_id) { _id = in_id; }
	
};
