#pragma once
#include <vector>
#include <algorithm>

using namespace std;

class CTransition
{
	vector<pair<char, int> > _list;

	static bool icmp(const pair<char, int>& elem1, const pair<char, int>& elem2)
	{
		return elem1.first - elem2.first < 0;
	}

public:

	void Add(const char k, const int val)
	{
		const pair<char, int> p(k, val);
		const vector<pair<char, int> >::iterator it = lower_bound(_list.begin(), _list.end(), p, icmp);
		_list.insert(it, p);
	}

	int GetNewStates(const char k, vector<int>& out_vecDest)
	{
		const pair<char, int> p(k, 0);
		vector<pair<char, int> >::iterator it = lower_bound(_list.begin(), _list.end(), p, icmp);

		int count = 0;
		while(it != _list.end() && it->first == k)
		{
			out_vecDest.push_back(it->second);
			count++;
			++it;
		}
		return count;
	}
};

class CTransitionTable
{
	CTransition** _transitions;
	int _transition_count;

public:

	CTransitionTable(const int inStateCount)
	{
		_transition_count = inStateCount;
		_transitions = new CTransition*[_transition_count];
		//for(int i = 0; i < )
		memset(_transitions, 0, sizeof(CTransition*) * _transition_count);
	}

	~CTransitionTable()
	{
		for (int i = 0; i < _transition_count; ++i)
			if (_transitions[i] != NULL)
				delete(_transitions[i]);
		delete(_transitions);
		_transitions = NULL;
	}

	void AddTransition(const int from, const char k, const int to) const
	{
		CTransition* tr = _transitions[from];
		if(tr == NULL)
		{
			tr = new CTransition();
			_transitions[from] = tr;
		}

		tr->Add(k, to);
	}

	int GetNewStates(const int from, const char k, vector<int>& out_vecDest) const
	{
		CTransition* tr = _transitions[from];
		if (tr == NULL)
			return 0;

		return tr->GetNewStates(k, out_vecDest);
	}
};
