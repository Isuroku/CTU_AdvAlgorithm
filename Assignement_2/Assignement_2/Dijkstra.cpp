#include "VertexC.h"
#include "Dijkstra.h"
#include <algorithm>

SWeightComp2 comp;
CHeap _heap(&comp);

size_t FindPathLength(CVertexC* inStartVertex)
{
	if (inStartVertex->dest)
		return inStartVertex->weight;

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

			if (n->dest)
			{
				size_t sz = n->weight + v->wave_length;
				res = max(res, sz);
			}
			else if(n->result)
			{
				if (n->result_length > 0)
				{
					size_t sz = n->result_length + v->wave_length;
					res = max(res, sz);
				}
			}
			else
			{
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
	}

	return res;
}
