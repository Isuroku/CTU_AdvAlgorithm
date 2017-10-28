#pragma once
#include "Vertex.h"
#include <stack>

class CTarjan
{
public:

	void solve(vector<CVertex>& vertices);

	void printscr() const;

private:
	vector<vector<CVertex*>> _scc;

	void reset_find_SCC();
	void find_SCC(CVertex& v);
	void find_SCC2(CVertex& v);

	CVertex* pop(CVertex* v);
	void push(CVertex& v);

	int _index;
	int _max_level;
	CVertex* _S;
	size_t _curr_scc_index;

	class CStackInfo
	{
	public:
		CStackInfo() : _vertex(NULL), _neighbour(-1) {}
		CStackInfo(CVertex* in_vertex): _vertex(in_vertex), _neighbour(-1) {}

		CVertex* GetNextNeighbour()
		{
			_neighbour++;
			if (_neighbour >= _vertex->neighbours.size())
				return NULL;
			return _vertex->neighbours[_neighbour];
		}

		void reset()
		{
			_vertex = NULL;
			_neighbour = -1;
		}

		CVertex* vertex() const { return _vertex; }

	private:
		CVertex* _vertex;
		size_t _neighbour;
	};

	stack<CStackInfo> _stack;
	CStackInfo _curr;

	CStackInfo set_curr(CVertex* v);
	void check_vertex_collect_scc(CVertex& v);
};


