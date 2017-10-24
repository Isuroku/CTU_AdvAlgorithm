#ifndef LPRIORITY_H
#define LPRIORITY_H

#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include "Constants.h"

class CEdge;

class CLPriority
{
public:

	CLPriority(): _length(0), _priority(0), _result(max_int) {}
	explicit CLPriority(const int length) : _length(length), _priority(0), _result(max_int) {}
	explicit CLPriority(const CLPriority& other) 
		: _length(other._length), _priority(other._priority), _result(other._result), _bad_edges(other._bad_edges) {}

	int length() const { return _length; }
	int priority() const { return _priority; }
	int result() const { return _result; }

	void set_values(const int length, const int priority) { _length = length; _priority = priority;	}
	void set_priority(const int value) { _priority = value; }
	void set_result(const int value) { _result = value; }

	void inc_priority()	{ _priority++; }

	string name() const
	{
		ostringstream ss;
		ss << "pr" <<_priority << " - " <<  "len" << _length;
		return ss.str();
	}

	bool is_priority_edge(CEdge* edge) const;
	void set_bad_edge(CEdge* edge, vector<CLPriority*>& vec_copies, unordered_map< int, vector<CEdge*> >& len_edges_tbls);

	bool in_bad_edge_list(CEdge* edge) const 
	{ 
		unordered_set<CEdge*>::const_iterator it = _bad_edges.find(edge);
		return it != _bad_edges.cend();
	}

private:
	int _length;
	int _priority;
	int _result;

	unordered_set<CEdge*> _bad_edges;
};

struct lpriorcomp
{
	bool operator() (const CLPriority& lhs, const CLPriority& rhs) const
	{
		if (lhs.priority() == rhs.priority())
			return lhs.length() < rhs.length();
		return lhs.priority() > rhs.priority();
	}
};

struct plpriorcomp
{
	bool operator() (const CLPriority* lhs, const CLPriority* rhs) const
	{
		if (lhs->priority() == rhs->priority())
			return lhs->length() > rhs->length();
		return lhs->priority() < rhs->priority();
	}
};

#endif // LPRIORITY_H
