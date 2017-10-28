#pragma once
#include "Vertex.h"
#include <stack>
#include <map>
using namespace std;

class CTarjan
{
public:

	void solve(vector<CVertex>& vertices);
	size_t GetComponentsCount() const { return _scc.size(); }
	size_t GetComponentWeight(size_t index) const { return _scc[index].size(); }
	int GetComponentLowLink(size_t index) const { return _scc[index].at(0)->lowlink; }
	size_t GetComponentIndex(int lowlink) const { return _lowlink_componentindex.at(lowlink); }
	const vector<CVertex*>& GetComponent(int index) const { return _scc[index]; }
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
	map<int, size_t> _lowlink_componentindex;


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


