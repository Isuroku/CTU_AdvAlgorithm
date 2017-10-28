#include "Tarjan.h"
#include <algorithm>
#include <vector>
#include <iostream>


using namespace std;

void CTarjan::solve(vector<CVertex>& vertices)
{
	reset_find_SCC();
	for_each(vertices.begin(), vertices.end(), [this](CVertex& v)
	{
		if (v.index == 0)
			find_SCC2(v);
	});
}

void CTarjan::reset_find_SCC()
{
	_index = 0;
	_S = NULL;
	_curr_scc_index = 0;
	_max_level = 0;
}

void CTarjan::push(CVertex& v)
{
	v.pred = _S;
	v.instack = true;
	_S = &v;
}

CVertex* CTarjan::pop(CVertex* v)
{
	_S = v->pred;
	v->instack = false;
	v->pred = NULL;
	return v;
}



void CTarjan::find_SCC(CVertex& v)
{
	v.index = v.lowlink = ++_index;
	push(v);

	for each (CVertex* w in v.neighbours)
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

void CTarjan::check_vertex_collect_scc(CVertex& v)
{
	if (v.lowlink == v.index)
	{
		CVertex* x;
		do
		{
			x = pop(_S);

			if (_curr_scc_index == _scc.size())
			{
				_lowlink_componentindex.insert(pair<int,size_t>(v.lowlink, _scc.size()));
				_scc.push_back(vector<CVertex*>());
			}

			_scc[_curr_scc_index].push_back(x);
		} while (x != &v);

		_curr_scc_index++;
	}
}

void CTarjan::printscr() const
{
	for each(vector<CVertex*> vec in _scc)
	{
		for each(CVertex* v in vec)
		{
			cout << v->GetID() << " ";
		}
		cout << endl;
	}
}

CTarjan::CStackInfo CTarjan::set_curr(CVertex* v)
{
	v->index = v->lowlink = ++_index;
	push(*v);

	return CStackInfo(v);
}

void CTarjan::find_SCC2(CVertex& v)
{
	_curr = set_curr(&v);

	while(!_stack.empty() || _curr.vertex() != NULL)
	{
		CVertex* w = _curr.GetNextNeighbour();
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