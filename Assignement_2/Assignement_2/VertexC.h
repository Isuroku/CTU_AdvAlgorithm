#pragma once
#include <cstddef>
#include <vector>
#include "Heap.h"

using namespace std;

class CVertexC: public CHeapElem
{
public:
	int _id;
	
	size_t wayfarer_count;
	size_t weight;

	bool dest;

	vector<CVertexC*> neighbours;
	vector<CVertexC*> rear_neighbours;

	size_t _heap_index;
	size_t wave_length;

	CVertexC() : _id(0), wayfarer_count(0), weight(1), dest(false), _heap_index(-1), wave_length(0) {}

	int GetID() const { return _id; }
	void SetID(const int in_id) { _id = in_id; }

	float heap_weight() const override { return static_cast<float>(wave_length); }
	void set_heap_index(const size_t index) override { _heap_index = index; }
	size_t get_heap_index() const override { return _heap_index; }
	
};

struct SWeightComp2: public SWeightComp
{
	virtual ~SWeightComp2() {};

	bool better(const float weight1, const float weight2) override
	{
		return weight1 > weight2;
	};
};