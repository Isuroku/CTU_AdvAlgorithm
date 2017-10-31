#include "VertexC.h"
#include "Dijkstra.h"
#include <algorithm>
#include <queue>

SWeightComp2 comp;
CHeap _heap(&comp);

struct SVertexInfo1
{
	bool wave_passed;
	size_t wave_length;
	size_t closed_count;

	SVertexInfo1(): wave_passed(false), wave_length(0), closed_count(0) {}
};

size_t FindPathLength(CVertexC* inStartVertex, const size_t vertex_count)
{
	if (inStartVertex->dest)
		return inStartVertex->weight;

	vector<SVertexInfo1> vinfo(vertex_count);

	_heap.clear();

	inStartVertex->wave_length = inStartVertex->weight;
	_heap.insert(*inStartVertex);

	size_t res = 0;

	while (!_heap.IsEmpty())
	{
		CVertexC* v = static_cast<CVertexC*>(_heap.Heap_Extract_Max());

		for (size_t i = 0; i < v->neighbours.size(); ++i)
		{
			CVertexC* n = v->neighbours[i];

			if (n->state != vsClosed)
			{
				if (n->dest)
				{
					size_t sz = n->weight + v->wave_length;
					res = max(res, sz);
				}
				else if (n->state == vsPassed)
				{
					if (n->result_length > 0)
					{
						size_t sz = n->result_length + v->wave_length;
						res = max(res, sz);
					}
				}
				else
				{
					//if(!vinfo[n->vec_index()].wave_passed)
					if (n->get_heap_index() == static_cast<size_t>(-1))
					{
						n->wave_length = n->weight + v->wave_length;
						_heap.insert(*n);
					}
					else if (SWeightComp2::waight_better(n->weight + v->wave_length, n->wave_length))
					{
						n->wave_length = n->weight + v->wave_length;
						_heap.up(n);
					}
				}
			}
			else
				vinfo[v->vec_index()].closed_count++;
		}

		if (vinfo[v->vec_index()].closed_count == v->neighbours.size() && !v->dest)
			v->state = vsClosed;
	}

	return res;
}

enum EFindResult { frUnknown, frNothing, frFound };

struct SWayFarerCheck
{
	vector<bool> wayfarers;
	size_t finded_count;
	bool checked;
	size_t length;

	SWayFarerCheck(const size_t wfcount) : wayfarers(wfcount, false), finded_count(0), checked(false), length(0) {}
};


size_t request(CVertexC* v, vector<SWayFarerCheck>& wayfarers_check)
{
	SWayFarerCheck& my_check = wayfarers_check[v->vec_index()];
	if (my_check.checked)
		return my_check.length;

	size_t child_len = 0;

	const size_t wfcount = my_check.wayfarers.size();
	bool all_found = false;

	for(size_t i = 0; i < v->rear_neighbours.size(); i++)
	{
		CVertexC* n = v->rear_neighbours[i];
		size_t len = request(n, wayfarers_check);
		
		SWayFarerCheck& child_check = wayfarers_check[n->vec_index()];

		if(child_check.finded_count == wfcount)
		{
			child_len = max(child_len, len);
			all_found = true;
		}
		else if (!all_found)
		{
			for (size_t w = 0; w < my_check.wayfarers.size(); w++)
			{
				if (child_check.wayfarers[w])
					my_check.wayfarers[w] = true;
			}
		}
	}

	if(all_found)
	{
		my_check.finded_count = wfcount;
	}
	else
	{
		for (size_t w = 0; w < v->wayfarers.size(); w++)
			my_check.wayfarers[v->wayfarers[w]] = true;

		for (size_t w = 0; w < my_check.wayfarers.size(); w++)
			if (my_check.wayfarers[w])
				my_check.finded_count++;

		all_found = my_check.finded_count == wfcount;
	}

	if (all_found)
		my_check.length = v->weight + child_len;

	my_check.checked = true;

	return my_check.length;
}

size_t FindDFS(CVertexC* inDestVertex, const size_t inVertexCount, const size_t inWayFarerCount)
{
	const SWayFarerCheck fc(inWayFarerCount);
	vector<SWayFarerCheck> wayfarers_check(inVertexCount, fc);

	return request(inDestVertex, wayfarers_check);
}
