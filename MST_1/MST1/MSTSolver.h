#pragma once
#include <vector>
#include <map>
#include <functional>
#include "LPriority.h"

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
	int _v_count;
	int _e_count;

	//CVertex** _vertices;
	vector<CEdge> _edges;
	vector<CVertex> _vertices;
	vector<CEdge*> _heap_edges;

	map< int, int, greater<int> > _len_priority_tbls;

	void create_tbls(vector<CLPriority>& out_vec);
	bool solve_pass(int max_length, vector<CLPriority>& in_vecPriorities);
};
