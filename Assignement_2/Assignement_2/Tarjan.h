#pragma once
#include "Vertex.h"
#include <stack>
#include <map>
using namespace std;

class CTarjan
{
public:

	void solve(vector<CVertexT>& vertices);
	size_t GetComponentsCount() const { return _scc.size(); }
	size_t GetComponentWeight(size_t index) const { return _scc[index].size(); }
	int GetComponentLowLink(size_t index) const { return _scc[index].at(0)->lowlink; }
	size_t GetComponentIndex(int lowlink) const { return _lowlink_componentindex.at(lowlink); }
	const vector<CVertexT*>& GetComponent(size_t index) const { return _scc[index]; }
	void printscr() const;

private:
	vector<vector<CVertexT*>> _scc;

	void reset_find_SCC();
	void find_SCC(CVertexT& v);
	void find_SCC2(CVertexT& v);

	CVertexT* pop(CVertexT* v);
	void push(CVertexT& v);
	

	int _index;
	int _max_level;
	CVertexT* _S;
	size_t _curr_scc_index;
	map<int, size_t> _lowlink_componentindex;


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


