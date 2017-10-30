#include "SimpleSCC.h"
#include <algorithm>
#include <deque>


CSimpleSCC::CSimpleSCC()
{
}


CSimpleSCC::~CSimpleSCC()
{
}

void get_topsort(CVertexT& v, vector<bool>& io_marked, deque<CVertexT*>& topsort)
{
	io_marked[v.vec_index()] = true;
	//for each (CVertexT* w in v.neighbours)
	for_each(v.neighbours.begin(), v.neighbours.end(), [&io_marked, &topsort](CVertexT* w)
	{
		if (!io_marked[w->vec_index()])
			get_topsort(*w, io_marked, topsort);
	});

	topsort.push_front(&v); // подсовываем v в начало topsort
}


void get_component(CVertexT& v, vector<bool>& io_marked, vector<CVertexT*>& out_component, size_t comp_index)
{
	io_marked[v.vec_index()] = true;

#ifdef MY_TEST
	out_component.insert(lower_bound(out_component.begin(), out_component.end(), &v), &v);
#endif //MY_TEST

#ifndef MY_TEST
	out_component.push_back(&v);
#endif //MY_TEST

	v.comp_index = comp_index;

	//for each (CVertexT* x in v.rear_neighbours)
	for_each(v.rear_neighbours.begin(), v.rear_neighbours.end(), [&io_marked, &out_component, &comp_index](CVertexT* x)
	{
		if (!io_marked[x->vec_index()])
			get_component(*x, io_marked, out_component, comp_index);
	});
}


void CSimpleSCC::solve(vector<CVertexT>& vertices)
{
	deque<CVertexT*> topsort;

	vector<bool> marked = vector<bool>(vertices.size(), false); // все вершины не помечены

	for (int v = 0; v < vertices.size(); v++)
	{
		if (!marked[v])
			get_topsort(vertices[v], marked, topsort);
	}

	marked = vector<bool>(vertices.size(), false);

	for (int t = 0; t < topsort.size(); t++)
	{
		CVertexT* v = topsort[t];
		if (!marked[v->vec_index()])
		{
			vector <CVertexT*> component;
			get_component(*v, marked, component, _scc.size());
			_scc.push_back(component);
		}
	}

	reverse(_scc.begin(), _scc.end());
}
