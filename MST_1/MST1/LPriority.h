#ifndef LPRIORITY_H
#define LPRIORITY_H

#include <sstream>
#include <limits>

class CLPriority
{
public:

	CLPriority(): _length(0), _priority(0), _result(INT_MAX) {}
	//CLPriority(const int length) : _length(length), _priority(0) {}
	//CLPriority(const int length, const int priority) : _length(length), _priority(priority) {}

	int length() const { return _length; }
	int priority() const { return _priority; }
	int result() const { return _result; }

	void set_values(const int length, const int priority) { _length = length; _priority = priority;	}
	void set_priority(const int value) { _priority = value; }
	void set_result(const int value) { _result = value; }

	string name() const
	{
		ostringstream ss;
		ss << "pr" <<_priority << " - " <<  "len" << _length;
		return ss.str();
	}

private:
	int _length;
	int _priority;
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
