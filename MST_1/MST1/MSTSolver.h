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

	CVertex** _vertices;
	vector<CEdge> _edges;

	map< int, int, greater<int> > _len_priority_tbls;
	map< int, vector<int>*, greater<int> > _priority_len_tbls;

	CVertex* get_vertex(const int vid) const;

	void create_tbls(vector<CLPriority>& out_vec);
	bool solve_pass(vector<CLPriority>& in_vecPriorities, int& out_tree_len);
	vector<int>* set_len_by_pr(int len, int pr);
};

