#pragma once

#include <stack>
#include <map>

#include "StronglyConnectedComponents.h"


class CTarjan : public CStronglyConnectedComponents
{
public:

	void solve(vector<CVertexT>& vertices, bool reqursion);
	void printscr() const;

private:
	void reset_find_SCC();
	void find_SCC(CVertexT& v);
	void find_SCC2(CVertexT& v);

	CVertexT* pop(CVertexT* v);
	void push(CVertexT& v);
	

	int _index;
	int _max_level;
	CVertexT* _S;
	size_t _curr_scc_index;

	class CStackInfo
	{
	public:
		CStackInfo() : _vertex(NULL), _neighbour(-1) {}
		CStackInfo(CVertexT* in_vertex): _vertex(in_vertex), _neighbour(-1) {}

		CVertexT* GetNextNeighbour()
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

		CVertexT* vertex() const { return _vertex; }

	private:
		CVertexT* _vertex;
		size_t _neighbour;
	};

	stack<CStackInfo> _stack;
	CStackInfo _curr;

	CStackInfo set_curr(CVertexT* v);
	void check_vertex_collect_scc(CVertexT& v);
};


