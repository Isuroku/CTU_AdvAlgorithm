#pragma once
#include <vector>

class CVertex;
class CEdge;

class CMSTSolver
{
public:
	CMSTSolver(const int v_count, const int e_count);
	~CMSTSolver();

	void add_edge(int vid1, int vid2, int length);

private:
	int _v_count;
	int _e_count;

	CVertex** _vertices;
	std::vector<CEdge*> _edges;

	CVertex* get_vertex(const int vid) const;
};

