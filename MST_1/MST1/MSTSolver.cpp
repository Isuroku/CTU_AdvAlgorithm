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
	_edges.resize(e_count);
	_heap_edges.reserve(e_count);

	for (size_t i = 0; i < _edges.size(); ++i)
		_heap_edges.push_back(&_edges[i]);

	_vertices.resize(_v_count);
	for (size_t i = 0; i < _vertices.size(); ++i)
		_vertices[i].Init(i + 1);
}

CMSTSolver::~CMSTSolver()
{
	_vertices.clear();
	_edges.clear();
}

void CMSTSolver::add_edge(const int index, const int vid1, const int vid2, const int length)
{
	CVertex* pv1 = &_vertices[vid1 - 1];
	CVertex* pv2 = &_vertices[vid2 - 1];
	_edges[index].init(pv1, pv2, length);

	const int pr = _len_priority_tbls[length] + 1;
	_len_priority_tbls[length] = pr;
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
	}

	sort(out_vec.begin(), out_vec.end(), lpriorcomp());

	/*cerr << "PriorityVec: " << endl;
	for (vector<CLPriority>::iterator it = out_vec.begin(); it != out_vec.end(); ++it)
		cerr << it->name() << "; ";
	cerr << endl;*/
}

struct SEdgeComp
{
	SEdgeComp(const int best_length): _best_length(best_length) {}

	int _best_length;

	bool operator() (const CEdge* lhs, const CEdge* rhs) const	
	{
		const int pr_lhs = lhs->length() == _best_length && !lhs->is_bad() ? 1 : 0;
		const int pr_rhs = rhs->length() == _best_length && !rhs->is_bad() ? 1 : 0;

		if(pr_lhs == pr_rhs)
			return lhs->length() < rhs->length(); 
		return pr_lhs > pr_rhs;
	}
};

int CMSTSolver::solve()
{
	vector<CLPriority> vec_prs;

	create_tbls(vec_prs);

	bool passed = true;
	CLPriority best_passed;
	
	do
	{
		if (!passed)
		{
			for (int i = 0; i < _v_count; i++)
				_vertices[i].reset();
		}

		passed = solve_pass(best_passed.result(), vec_prs);
		if(passed)
		{
			CLPriority passed_pr = vec_prs[0];
			vec_prs.erase(vec_prs.begin());

			if (best_passed.result() > passed_pr.result())
				best_passed = passed_pr;

			passed = best_passed.priority() > vec_prs.begin()->priority();
		}
	} while (!passed);

	return best_passed.result();
}

bool CMSTSolver::solve_pass(const int in_max_length, vector<CLPriority>& io_vecPriorities)
{
	const SEdgeComp edge_comp(io_vecPriorities[0].length());
	
	sort(_heap_edges.begin(), _heap_edges.end(), edge_comp);

	size_t f_cout = _vertices.size();

	//map<int, int> f_len;

	bool good = true;
	bool frag_len_less_max = true;
	int last_res = 0;
	size_t edge_index = 0;

	while (f_cout > 1 && frag_len_less_max && good && edge_index < _heap_edges.size())
	{
		CEdge* edge = _heap_edges[edge_index];
		edge_index++;

		CVertex* frag_l = edge->get_vertex(true)->get_frag();
		CVertex* frag_r = edge->get_vertex(false)->get_frag();

		if (frag_l != frag_r)
		{
			f_cout--;

			CVertex* frag_p;
			CVertex* frag_c;

			if (frag_l->get_frag_rank() > frag_r->get_frag_rank())
			{
				frag_p = frag_l;
				frag_c = frag_r;
			}
			else
			{
				frag_p = frag_r;
				frag_c = frag_l;
			}

			last_res = frag_p->get_frag_length() + frag_c->get_frag_length() + edge->length();

			frag_len_less_max = last_res < in_max_length;

			if (frag_len_less_max)
			{
				frag_p->set_frag_length(last_res);
				frag_p->set_frag_rank(frag_p->get_frag_rank() + frag_c->get_frag_rank());
				frag_c->set_parent(frag_p);
			}
		}
		else
		{
			if (io_vecPriorities[0].length() == edge->length() && !edge->is_bad())
			{
				CLPriority curr_best_priority = io_vecPriorities[0];

				edge->set_bad(true);

				io_vecPriorities.erase(io_vecPriorities.begin());

				curr_best_priority.set_priority(curr_best_priority.priority() - 1);
				const vector<CLPriority>::iterator new_place = lower_bound(io_vecPriorities.begin(), io_vecPriorities.end(), curr_best_priority, lpriorcomp());
				io_vecPriorities.insert(new_place, curr_best_priority);

				good = io_vecPriorities.begin()->length() == curr_best_priority.length();
			}
		}
	}

	if (good)
		io_vecPriorities[0].set_result(last_res);

	return good;
}