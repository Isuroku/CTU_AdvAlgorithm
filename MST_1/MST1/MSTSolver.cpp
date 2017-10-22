#include <cstring>
#include "MainHeader.h"

#include "MSTSolver.h"
#include "Vertex.h"
#include "Edge.h"
#include <functional>
#include <algorithm>
#include <queue>

//struct proritycomp { bool operator() (const int& lhs, const int& rhs) const	{ return lhs<rhs; } };

CMSTSolver::CMSTSolver(const int v_count, const int e_count): _v_count(v_count), _e_count(e_count)
{
	_vertices = new CVertex*[_v_count];
	memset(_vertices, 0, _v_count * sizeof(CVertex*));
	_edges.resize(e_count);
}


CMSTSolver::~CMSTSolver()
{
	for (int i = 0; i < _v_count; i++)
		safe_delete(_vertices[i]);
	safe_delete(_vertices);

	_edges.clear();

	for (map< int, vector<int>*, greater<int> >::iterator it = _priority_len_tbls.begin(); it != _priority_len_tbls.end(); ++it)
		safe_delete(it->second);
}

void CMSTSolver::add_edge(const int index, const int vid1, const int vid2, const int length)
{
	CVertex* pv1 = get_vertex(vid1 - 1);
	CVertex* pv2 = get_vertex(vid2 - 1);
	_edges[index].init(pv1, pv2, length);

	int pr = _len_priority_tbls[length] + 1;
	_len_priority_tbls[length] = pr;
}

CVertex* CMSTSolver::get_vertex(const int vid) const
{
	CVertex* pv = _vertices[vid];
	if (!pv)
	{
		pv = new CVertex(vid);
		_vertices[vid] = pv;
	}
	return pv;
}

vector<int>* CMSTSolver::set_len_by_pr(int len, int pr)
{
	vector<int>* lens = _priority_len_tbls[pr];
	if (lens == NULL)
	{
		lens = new vector<int>();
		_priority_len_tbls[pr] = lens;
	}
	const vector<int>::iterator place_it = lower_bound(lens->begin(), lens->end(), len);
	lens->insert(place_it, len);

	return lens;
}

void CMSTSolver::create_tbls(vector<CLPriority>& out_vec)
{
	out_vec.resize(_len_priority_tbls.size());

	int i = 0;
	for (map< int, int, greater<int> >::iterator it = _len_priority_tbls.begin(); it != _len_priority_tbls.end(); ++it)
	{
		int len = it->first;
		int pr = it->second;

		out_vec[i].set_values(len, pr);
		i++;

		cerr << len << ": " << pr << endl;
		if (pr > 1)
			set_len_by_pr(len, pr);
	}

	sort(out_vec.begin(), out_vec.end(), lpriorcomp());

	cerr << "PriorityVec: " << endl;
	for (vector<CLPriority>::iterator it = out_vec.begin(); it != out_vec.end(); ++it)
		cerr << it->name() << "; ";
	cerr << endl;

	/*cerr << "PriorityTbl: " << endl;
	for (map< int, vector<int>*, greater<int> >::iterator it = _priority_len_tbls.begin(); it != _priority_len_tbls.end(); ++it)
	{
		cerr << "p: " << it->first << ", len: ";

		if (it->second == NULL)
			cerr << "1";
		else
		{
			for (vector<int>::iterator itq = it->second->begin(); itq != it->second->end(); ++itq)
				cerr << *itq << ", ";
		}
	}
	cerr << endl;*/
}

struct SEdgeComp
{
	SEdgeComp(const int best_length): _best_length(best_length) {}

	int _best_length;

	bool operator() (const CEdge* lhs, const CEdge* rhs) const	
	{
		const int pr_lhs = lhs->length() == _best_length ? 1 : 0;
		const int pr_rhs = rhs->length() == _best_length ? 1 : 0;

		if(pr_lhs == pr_rhs)
			return lhs->length() > rhs->length(); 
		return pr_lhs < pr_rhs;
	}
};

int CMSTSolver::solve()
{
	vector<CLPriority> vec_prs;

	create_tbls(vec_prs);

	bool passed;
	int tree_len;
	do
	{
		passed = solve_pass(vec_prs, tree_len);
	} while (!passed);

	return tree_len;
}

bool CMSTSolver::solve_pass(vector<CLPriority>& in_vecPriorities, int& out_tree_len)
{
	vector<CEdge*> heap;
	heap.reserve(_edges.size());

	CLPriority& curr_best_priority = in_vecPriorities[0];
	const SEdgeComp edge_comp(curr_best_priority.length());

	//priority_queue<CEdge*, vector<CEdge*>, edgecomp> edge_queue;

	for (vector<CEdge>::iterator it = _edges.begin(); it != _edges.end(); ++it)
	{
		CEdge* edge = &(*it);

		if (!edge->is_bad())
		{
			const vector<CEdge*>::iterator place_it = lower_bound(heap.begin(), heap.end(), edge, edge_comp);
			heap.insert(place_it, edge);

			/*(*it)->set_priority(_len_priority_tbls[(*it)->length()]);
			edge_queue.push(*it);*/
		}
	}

	/*cerr << "sort edges: "  << endl;
	while (!edge_queue.empty())
	{
		CEdge* edge = edge_queue.top();
		cerr << edge->name() << endl;
		edge_queue.pop();
	}
	cerr << endl;*/

	int f_cout = _v_count;

	map<int, int> f_len;

	bool good = true;

	while (f_cout > 1 && good && !heap.empty())
	{
		vector<CEdge*>::iterator last = --heap.end();
		CEdge* edge = *last;
		heap.erase(last);
		//edge_queue.pop();

		int fid_l = edge->get_vertex(true)->get_fid();
		int fid_r = edge->get_vertex(false)->get_fid();

		if (fid_l != fid_r)
		{
			f_cout--;

			edge->get_vertex(false)->set_parent(edge->get_vertex(true)->get_frag());
			
			f_len[fid_l] = f_len[fid_l] + f_len[fid_r] + edge->length();
		}
		else
		{
			if (best_len == edge->length())
			{
				vector<CLPriority>::iterator pr_it_fail = in_vecPriorities.begin();
				CLPriority lpr_fail = *pr_it_fail;
				in_vecPriorities.erase(pr_it_fail);

				lpr_fail.set_priority(lpr_fail.priority() - 1);
				pr_it_fail = lower_bound(in_vecPriorities.begin(), in_vecPriorities.end(), lpr_fail, lpriorcomp());
				in_vecPriorities.insert(pr_it_fail, lpr_fail);

				good = pr_it_fail == in_vecPriorities.begin();
			}
			/*edge->set_bad(true);

			int edge_len = edge->length();
			const int old_pr = _len_priority_tbls[edge_len];
			const int new_pr = old_pr - 1;
			_len_priority_tbls[edge_len] = new_pr;

			if (old_pr > 1)
			{
				vector<int>* old_lens = _priority_len_tbls[old_pr];

				const vector<int>::iterator next_len_it = old_lens->erase(old_lens->begin());

				vector<int>* new_lens = set_len_by_pr(edge_len, new_pr);

				good = next_len_it == old_lens->end() && new_lens->at(0) == edge_len;
			}*/
		}
	}

	if(good)
		out_tree_len = f_len[_vertices[0]->get_fid()];
	else
	{
		for (int i = 0; i < _v_count; i++)
			_vertices[i]->reset_fid();
	}

	return good;
}