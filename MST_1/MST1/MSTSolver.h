#pragma once
#include <vector>
#include <map>
#include <functional>
#include "LPriority.h"
#include <unordered_map>

class CVertex;
class CEdge;

class CMSTSolver
{
public:
	CMSTSolver(const int v_count, const int e_count);
	~CMSTSolver();

	void add_edge(int index, int vid1, int vid2, int length);

	int solve();

private:
	vector<CEdge> _edges;
	vector<CVertex> _vertices;
	vector<CEdge*> _heap_edges;

	vector<CLPriority*> _vec_priorities;

	unordered_map<int, CLPriority*> _len_priority_tbls;
	unordered_map< int, vector<CEdge*> > _len_edges_tbls;

	void solve_pass(int max_length, CLPriority* ioPriority);
	void insert_priority_to_table(CLPriority* pr);

	void reset_vertices();
};

