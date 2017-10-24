#pragma once

#include <vector>
#include "Constants.h"
using namespace std;

class CVertex
{
public:
	CVertex(): _id(0)
	{
		reset();
	}

	void Init(const int id)
	{
		_id = id;
		reset();
	}

	void reset()
	{
		_heap_weight = max_int;
		_heap_index = -1;
	}

	int get_index() const { return _id - 1; }

	int get_id() const { return _id; }

	void add_neighbour(CVertex* vertex, int dist)
	{
		sneightbour n(vertex, dist);
		_neighbours.push_back(n);
	}

	size_t get_neighbour_count() const { return _neighbours.size(); }
	CVertex* get_neighbour(size_t index) { return _neighbours[index]._v; }
	int get_neighbour_dist(size_t index) { return _neighbours[index]._dist; }

	int heap_index() const { return _heap_index; }
	int heap_weight() const { return _heap_weight; }

	void set_heap_index(int index) { _heap_index = index; }
	void set_heap_weight(int weight) { _heap_weight = weight; }

private:
	int _id;

	int _heap_weight;
	int _heap_index;

	struct sneightbour
	{
		CVertex* _v;
		int _dist;

		sneightbour(CVertex* v, int dist) : _v(v), _dist(dist) {}
	};

	vector<sneightbour> _neighbours;
};

struct SVertexWeight
{
	CVertex* vertex;
	int weight;

	SVertexWeight(const SVertexWeight& other) : vertex(other.vertex), weight(other.weight) {}
	SVertexWeight(CVertex* ivertex, int iweight) : vertex(ivertex), weight(iweight) {}
	SVertexWeight() : vertex(NULL), weight(max_int) {}

	bool operator > (const SVertexWeight& right)
	{
		return weight > right.weight;
	}

	bool operator < (const SVertexWeight& right)
	{
		return weight < right.weight;
	}

	bool operator == (const SVertexWeight& right)
	{
		return weight == right.weight;
	}
};
