#pragma once
#include "Vertex.h"

class CTarjan
{
public:

	void solve(vector<CVertex>& vertices);

	void printscr() const;

private:
	vector<vector<CVertex*>> _scc;

	void reset_find_SCC();
	void find_SCC(CVertex& v, int level);

	CVertex* pop(CVertex* v);
	void push(CVertex& v);

	int _index;
	int _max_level;
	CVertex* _S;
	size_t _curr_scc_index;
};


