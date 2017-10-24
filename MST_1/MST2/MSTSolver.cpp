#include <cstring>
#include "MSTSolver.h"
#include "Vertex.h"
#include "Edge.h"
#include <functional>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include "LPriority.h"
#include "Heap.h"

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

	pv1->add_neighbour(pv2, length);
	pv2->add_neighbour(pv1, length);

	
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

struct SSimpleWeightComp: SWeightComp
{

	SSimpleWeightComp(const int priority_weight): _priority_weight(priority_weight) {}

	int _priority_weight;

	int priority_weight() const { return  _priority_weight; }

	bool better(const int weight1, const int weight2) override
	{
		const int pr_lhs = weight1 == _priority_weight ? 0 : 1;
		const int pr_rhs = weight2 == _priority_weight ? 0 : 1;

		if (pr_lhs == pr_rhs)
			return weight1 < weight2;
		return pr_lhs < pr_rhs;
	}
};

int CMSTSolver::solve()
{
	sort(_vec_priorities.begin(), _vec_priorities.end(), plpriorcomp());
	/*cerr << "PriorityVec: " << endl;
	for (vector<CLPriority>::iterator it = out_vec.begin(); it != out_vec.end(); ++it)
	cerr << it->name() << "; ";
	cerr << endl;*/

	CLPriority* best_pr = NULL;

	for (vector<CLPriority*>::iterator it = _vec_priorities.begin(); it != _vec_priorities.end(); ++it)
	{
		CLPriority* pr = *it;

		if (best_pr == NULL ||
			pr->priority() == best_pr->priority())
		{
			SSimpleWeightComp comp(pr->length());
			int penalty;
			int result = prim(&comp, penalty);

			pr->set_priority(pr->priority() - penalty);
			pr->set_result(result);


			if (best_pr == NULL ||
				pr->priority() > best_pr->priority() ||
				pr->priority() == best_pr->priority() && pr->result() < best_pr->result())
			{
				best_pr = pr;
			}
		}
	}

	return best_pr->result();
}


int CMSTSolver::prim(SSimpleWeightComp* in_comparer, int& out_penalty)
{
	int best_result = 0;
	out_penalty = 0;

	//vector<CVertex*> p(_vertices.size(), NULL);

	CHeap queue(_vertices.size(), in_comparer);
	for (size_t i = 0; i < _vertices.size(); i++)
	{
		_vertices[i].reset();
		queue.insert(&_vertices[i]);
	}

	CVertex* r = &_vertices[0];
	r->set_heap_weight(0);

	while (!queue.IsEmpty())
	{
		CVertex* v = queue.Heap_Extract_Max();

		for (size_t i = 0; i < v->get_neighbour_count(); i++)
		{
			CVertex* u = v->get_neighbour(i);
			const int dist = v->get_neighbour_dist(i);

			const bool step_backward = u->heap_index() == -1;
			const bool light_weight = in_comparer->better(dist, u->heap_weight());

			if (!step_backward && light_weight)
			{
				//p[u->get_index()] = v;
				u->set_heap_weight(dist);

				queue.up(u->heap_index());
			}
			else if(!step_backward && !light_weight && dist == in_comparer->priority_weight())
			{
				out_penalty++;
			}
		}
	}

	for (size_t i = 0; i < _vertices.size(); i++)
		best_result += _vertices[i].heap_weight();

	return best_result;
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
