#include <cstring>
#include "MainHeader.h"

#include "MSTSolver.h"
#include "Vertex.h"
#include "Edge.h"

CMSTSolver::CMSTSolver(const int v_count, const int e_count): _v_count(v_count), _e_count(e_count)
{
	_vertices = new CVertex*[_v_count];
	memset(_vertices, 0, _v_count * sizeof(CVertex*));
	_edges.reserve(e_count);
}


CMSTSolver::~CMSTSolver()
{
	for (int i = 0; i < _v_count; i++)
		safe_delete(_vertices[i]);
	safe_delete(_vertices);

	for (size_t i = 0; i < _edges.size(); i++)
		safe_delete(_edges[i]);
	_edges.clear();
}

void CMSTSolver::add_edge(const int vid1, const int vid2, const int length)
{
	CVertex* pv1 = get_vertex(vid1 - 1);
	CVertex* pv2 = get_vertex(vid2 - 1);
	CEdge* pe = new CEdge(pv1, pv2, length);
	_edges.push_back(pe);
}

CVertex* CMSTSolver::get_vertex(const int vid) const
{
	CVertex* pv = _vertices[vid];
	if (!pv)
	{
		pv = new CVertex(vid);
		_vertices[vid] = pv;
	}
	return pv;
}
