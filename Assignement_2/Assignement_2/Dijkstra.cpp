#include "VertexC.h"
#include "Dijkstra.h"

SWeightComp2 comp;
CHeap _heap(&comp);

size_t FindPathLength(CVertexC* inStartVertex)
{
	_heap.clear();

	inStartVertex->wave_length = inStartVertex->weight;
	_heap.insert(inStartVertex);

	size_t res = 0;

	while (!_heap.IsEmpty())
	{
		CVertexC* v = static_cast<CVertexC*>(_heap.Heap_Extract_Max());

		if (!v->dest)
		{
			for (size_t i = 0; i < v->neighbours.size(); ++i)
			{
				CVertexC* n = v->neighbours[i];

				if (n->get_heap_index() == static_cast<size_t>(-1))
				{
					n->wave_length = n->weight + v->wave_length;
					_heap.insert(n);
				}
				else if (comp.better(static_cast<float>(n->weight + v->wave_length), static_cast<float>(n->wave_length)))
				{
					n->wave_length = n->weight + v->wave_length;
					_heap.up(n);
				}
			}
		}
		else
			res = v->wave_length;
	}

	return res;
}
