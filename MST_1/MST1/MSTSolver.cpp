#include <cstring>
#include "MainHeader.h"

#include "MSTSolver.h"
#include "Vertex.h"
#include "Edge.h"
#include <functional>
#include <algorithm>
#include <queue>
#include <unordered_map>

//#include "DFS.h"

//struct proritycomp { bool operator() (const int& lhs, const int& rhs) const	{ return lhs<rhs; } };

CMSTSolver::CMSTSolver(const int v_count, const int e_count)
{
	_edges.resize(e_count);
	_heap_edges.reserve(e_count);

	for (size_t i = 0; i < _edges.size(); ++i)
		_heap_edges.push_back(&_edges[i]);

	_vertices.resize(v_count);
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
	CEdge* edge = &_edges[index];

	CVertex* pv1 = &_vertices[vid1 - 1];
	CVertex* pv2 = &_vertices[vid2 - 1];
	edge->init(pv1, pv2, length);

	pv1->add_neighbour(pv2);
	pv2->add_neighbour(pv1);

	
	CLPriority* pr = _len_priority_tbls[length];
	if (pr == NULL)
	{
		pr = new CLPriority(length);
		_vec_priorities.push_back(pr);
		_len_priority_tbls[length] = pr;
	}
	pr->inc_priority();

	_len_edges_tbls[length].push_back(edge);
}

struct SEdgeComp
{
	SEdgeComp(CLPriority* curr_priority): _curr_priority(curr_priority) {}

	CLPriority* _curr_priority;

	bool operator() (CEdge* lhs, CEdge* rhs) const	
	{
		
		const int pr_lhs = _curr_priority->is_priority_edge(lhs) ? 1 : 0;
		const int pr_rhs = _curr_priority->is_priority_edge(rhs) ? 1 : 0;

		if(pr_lhs == pr_rhs)
			return lhs->length() < rhs->length(); 
		return pr_lhs > pr_rhs;
	}
};

void CMSTSolver::insert_priority_to_table(CLPriority* pr)
{
	const vector<CLPriority*>::iterator new_place = lower_bound(_vec_priorities.begin(), _vec_priorities.end(), pr, plpriorcomp());
	_vec_priorities.insert(new_place, pr);
}

void CMSTSolver::reset_vertices()
{
	for (size_t i = 0; i < _vertices.size(); i++)
		_vertices[i].reset();
}

int CMSTSolver::solve()
{
	sort(_vec_priorities.begin(), _vec_priorities.end(), plpriorcomp());
	/*cerr << "PriorityVec: " << endl;
	for (vector<CLPriority>::iterator it = out_vec.begin(); it != out_vec.end(); ++it)
	cerr << it->name() << "; ";
	cerr << endl;*/

	bool passed = true;
	int best_result = max_int;
	int best_priority = 0;
	
	do
	{
		if (!passed)
			reset_vertices();

		CLPriority* test_pr = _vec_priorities.back();
		_vec_priorities.pop_back();

		passed = test_pr->priority() < best_priority;

		if (!passed && test_pr != NULL)
		{
			solve_pass(best_result, test_pr);

			CLPriority* next_pr = _vec_priorities.back();
			if (next_pr->priority() > test_pr->priority())
			{
				insert_priority_to_table(test_pr);
				passed = false;
			}
			else
			{
				if (test_pr->priority() >= best_priority && best_result > test_pr->result())
				{
					best_result = test_pr->result();
					best_priority = test_pr->priority();
				}

				passed = next_pr->priority() < test_pr->priority();
			}
		}
	} while (!passed);

	return best_result;
}

void CMSTSolver::solve_pass(const int in_max_length, CLPriority* ioPriority)
{
	if (ioPriority->result() != max_int)
		return;

	const SEdgeComp edge_comp(ioPriority);
	
	sort(_heap_edges.begin(), _heap_edges.end(), edge_comp);

	size_t f_cout = _vertices.size();

	//map<int, int> f_len;

	bool frag_len_less_max = true;
	int last_res = 0;
	size_t edge_index = 0;

	while (f_cout > 1 && frag_len_less_max && edge_index < _heap_edges.size())
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
				frag_p->inc_rank();
				frag_c->set_parent(frag_p);
			}
		}
		else if (ioPriority->length() == edge->length() && !ioPriority->in_bad_edge_list(edge))
		{
			vector<CLPriority*> vec_copies;
			ioPriority->set_bad_edge(edge, vec_copies, _len_edges_tbls);

			for(vector<CLPriority*>::iterator it = vec_copies.begin(); it != vec_copies.end(); ++it)
				insert_priority_to_table(*it);
		}
	}

	ioPriority->set_result(last_res);
}

void CLPriority::set_bad_edge(CEdge* edge, vector<CLPriority*>& vec_copies, unordered_map< int, vector<CEdge*> >& len_edges_tbls)
{
	_priority--;

	vector<CEdge*> vec_edges = len_edges_tbls[_length];

	for (vector<CEdge*>::iterator it = vec_edges.begin(); it != vec_edges.end(); ++it)
	{
		CEdge* brother = *it;
		if (!in_bad_edge_list(brother) && edge != brother)
		{
			CLPriority* new_rec = new CLPriority(*this);
			new_rec->_bad_edges.insert(brother);
			vec_copies.push_back(new_rec);
		}
	}

	_bad_edges.insert(edge);
}

bool CLPriority::is_priority_edge(CEdge* edge) const
{
	return edge->length() == _length && !in_bad_edge_list(edge);
}
