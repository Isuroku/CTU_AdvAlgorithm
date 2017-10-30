#pragma once
#include <cstddef>
#include <iostream>
#include <sstream>

#include <vector>
#include "Heap.h"
#include "VertexT.h"
#include <algorithm>

using namespace std;

class CVertexC: public CHeapElem
{
public:
	size_t _id;
	size_t weight;
	bool dest;
	size_t _heap_index;
	size_t wave_length;
	
	size_t _pid;
	
	size_t result_length;
	bool result;

	size_t get_wayfarer_count() const { return wayfarers.size(); };

	size_t get_weight() const { return included.size();	};

	bool is_dest() const
	{
		return any_of(included.begin(), included.end(), [](const CVertexT* v)
		{
			return v->dest;
		});
		//for each (const CVertexT* v in included)
		/*for_each(included.begin(), included.end(), [](const CVertexT* v)
		{
			if (v->dest)
				return true;
		});
		return false;*/
	}

	CVertexC() : _id(0), weight(1), dest(false), _heap_index(-1), wave_length(0), _pid(0), result_length(0), result(false) {}

	vector<CVertexC*> neighbours;
	vector<CVertexC*> rear_neighbours;

	vector<CVertexT*> included;

	vector<size_t> wayfarers;

	size_t id() const { return _id; }
	void set_id(const size_t in_id) { _id = in_id; }

	float heap_weight() const override { return static_cast<float>(wave_length); }
	void set_heap_index(const size_t index) override { _heap_index = index; }
	size_t get_heap_index() const override { return _heap_index; }

	bool check() const
	{
		bool res = true;
		if (get_weight() != weight)
		{
			cerr << debug_info() << "weight - error!" << endl;
			res = false;
		}
		if (is_dest() != dest)
		{
			cerr << debug_info() << "dest - error!" << endl;
			res = false;
		}
		return res;
	}

	string debug_info() const
	{
		stringstream ss;
		ss << "scc vertex " << _id << ": ";
		return ss.str();
	}
};

struct SWeightComp2: public SWeightComp
{
	virtual ~SWeightComp2() {};

	bool better(const CHeapElem& elem1, const CHeapElem& elem2) override
	{
		return static_cast<const CVertexC&>(elem1).weight > static_cast<const CVertexC&>(elem2).weight;
	};

	static bool waight_better(const size_t weight1, const size_t weight2)
	{
		return weight1 > weight2;
	};
};
