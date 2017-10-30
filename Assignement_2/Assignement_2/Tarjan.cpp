#include "Tarjan.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include "VertexT.h"


using namespace std;

void CTarjan::solve(vector<CVertexT>& vertices, bool reqursion)
{
	reset_find_SCC();
	for_each(vertices.begin(), vertices.end(), [this, reqursion](CVertexT& v)
	{
		if (v.index == 0)
		{
			if(reqursion)
				find_SCC(v);
			else
				find_SCC2(v);
		}
	});
}

void CTarjan::reset_find_SCC()
{
	_index = 0;
	_S = NULL;
	_curr_scc_index = 0;
	_max_level = 0;
}

void CTarjan::push(CVertexT& v)
{
	v.pred = _S;
	v.instack = true;
	_S = &v;
}

CVertexT* CTarjan::pop(CVertexT* v)
{
	_S = v->pred;
	v->instack = false;
	v->pred = NULL;
	return v;
}



void CTarjan::find_SCC(CVertexT& v)
{
	v.index = v.lowlink = ++_index;
	push(v);

	for each (CVertexT* w in v.neighbours)
	{
		if(w->index == 0)
		{
			find_SCC(*w);
			v.lowlink = min(v.lowlink, w->lowlink);
		}
		else if(w->instack)
		{
			v.lowlink = min(v.lowlink, w->index);
		}
	} 

	check_vertex_collect_scc(v);
}

void CTarjan::check_vertex_collect_scc(CVertexT& v)
{
	if (v.lowlink == v.index)
	{
		CVertexT* x;
		do
		{
			x = pop(_S);

			if (_curr_scc_index == _scc.size())
				_scc.push_back(vector<CVertexT*>());

			vector<CVertexT*>& comp = _scc[_curr_scc_index];
			comp.insert(lower_bound(comp.begin(), comp.end(), x), x);
			//comp.push_back(x);
			x->comp_index = _curr_scc_index;

		} while (x != &v);

		_curr_scc_index++;
	}
}

void CTarjan::printscr() const
{
	for each(vector<CVertexT*> vec in _scc)
	{
		for each(CVertexT* v in vec)
		{
			cout << v->id() << " ";
		}
		cout << endl;
	}
}

CTarjan::CStackInfo CTarjan::set_curr(CVertexT* v)
{
	v->index = v->lowlink = ++_index;
	push(*v);

	return CStackInfo(v);
}

void CTarjan::find_SCC2(CVertexT& v)
{
	_curr = set_curr(&v);

	while(!_stack.empty() || _curr.vertex() != NULL)
	{
		CVertexT* w = _curr.GetNextNeighbour();
		if(w != NULL && w->index == 0)
		{
			_stack.push(_curr);
			_curr = set_curr(w);
		}
		else if(w != NULL && w->instack)
		{
			_curr.vertex()->lowlink = min(_curr.vertex()->lowlink, w->index);
		}
		else
		{
			check_vertex_collect_scc(*_curr.vertex());

			if(_stack.empty())
				_curr.reset();
			else
			{
				CStackInfo pred = _stack.top();
				pred.vertex()->lowlink = min(pred.vertex()->lowlink, _curr.vertex()->lowlink);

				_curr = pred;
				_stack.pop();
			}
		}
	}
}