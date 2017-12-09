#pragma once
#include "Transition.h"


class CAutomaton
{
	vector<int>			_states1;
	vector<int>			_states2;

	vector<int>*		_states[2];
	size_t				_cur_states;

	CTransitionTable	_table;

	vector<int>			_final_states;

	vector<int>& GetCurrentStates() { return *_states[_cur_states];}
	vector<int>& GetNewStates() { return *_states[(_cur_states + 1) % 2]; }
	void SwitchCurrentStates() { _cur_states = (_cur_states + 1) % 2; }

public:

	CAutomaton(const int inStateCount): _table(inStateCount) 
	{
		Reset();
	}

	void Reset()
	{
		_states1.clear();
		_states2.clear();

		_cur_states = 0;
		_states[0] = &_states1;
		_states[1] = &_states2;

		GetCurrentStates().push_back(0);
	}

	void AddTransition(const int from, const char k, const int to) const
	{
		_table.AddTransition(from, k, to);
	}

	void AddFinalState(const int state)
	{
		const vector<int>::iterator it = lower_bound(_final_states.begin(), _final_states.end(), state);
		_final_states.insert(it, state);
	}

	void ChangeState(const char k)
	{
		GetNewStates().clear();

		for_each(GetCurrentStates().begin(), GetCurrentStates().end(), [&](int st)
		{
			_table.GetNewStates(st, k, GetNewStates());
		});

		SwitchCurrentStates();
	}

	bool IsInFinalState()
	{
		return find_if(GetCurrentStates().begin(), GetCurrentStates().end(), [&](int st) 
		{
			const vector<int>::iterator it = lower_bound(_final_states.begin(), _final_states.end(), st);
			return it != _final_states.end() && *it == st;
		}) != GetCurrentStates().end();
	}

	bool CheckWord(const string& cs)
	{
		Reset();

		for_each(cs.begin(), cs.end(), [this](char st)
		{
			ChangeState(st);
		});

		return IsInFinalState();
	}
};
