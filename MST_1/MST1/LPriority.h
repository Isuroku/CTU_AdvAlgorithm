#ifndef LPRIORITY_H
#define LPRIORITY_H

#include <sstream>

class CEdge;

class CLPriority
{
public:

	CLPriority(): _length(0), _priority(0) {}
	CLPriority(const int length) : _length(length), _priority(0) {}
	CLPriority(const int length, const int priority) : _length(length), _priority(priority) {}

	int length() const { return _length; }
	int priority() const { return _priority; }
	int result() const { return _result; }
	CEdge* bad_edge() const { return _bad_edge; }

	void set_values(const int length, const int priority) { _length = length; _priority = priority;	}
	void set_priority(const int value) { _priority = value; }
	void set_result(const int value) { _result = value; }
	void set_bad_edge(CEdge* bad_edge) { _bad_edge = bad_edge; }


	string name() const
	{
		ostringstream ss;
		ss << "pr" <<_priority << " - " <<  "len" << _length;
		return ss.str();
	}

private:
	int _length;
	int _priority;
	CEdge* _bad_edge;
	int _result;
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

#endif // LPRIORITY_H
