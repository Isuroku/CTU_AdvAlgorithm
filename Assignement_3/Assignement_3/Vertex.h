#pragma once
#include <cstddef>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class CVertex
{
public:
	vector<CVertex*> neighbours;

	string cert;

	CVertex() : cert("ab"), _id(0), _a("a"), _b("b")
	{
	}

	size_t id() const { return _id; }
	void set_id(const size_t in_id) { _id = in_id; }

	size_t vec_index() const { return _id - 1; }

	string get_debuf_info() const { return ""; }

	bool is_leaf() const { return neighbours.size() == 1; };

	static bool icmp(const string* elem1, const string* elem2)
	{
		//return _stricmp(elem1->c_str(), elem2->c_str()) < 0;
		return strcmp(elem1->c_str(), elem2->c_str()) < 0;
	}

	void MergeCert(vector<CVertex*>& childs)
	{
		vector<string*> crts;
		crts.reserve(childs.size() + 1);

		size_t buff_size = 3;
		string part;
		if (cert.length() > 2)
		{
			part = cert.substr(1, cert.length() - 2);
			crts.push_back(&part);
			buff_size += cert.length() - 2;
		}

		size_t childs_count = childs.size();
		for (size_t j = neighbours.size() - 1; j != size_t(-1) && childs_count > 0; j--)
		{
			CVertex* n = neighbours[j];
			if (count(childs.begin(), childs.end(), n) > 0)
			{
				vector<string*>::iterator it = lower_bound(crts.begin(), crts.end(), &n->cert, icmp);
				crts.insert(it, &n->cert);
				buff_size += n->cert.length();

				n->neighbours.clear();

				neighbours.erase(neighbours.begin() + j);
				childs_count--;
			}
		}

		string res;
		res.reserve(buff_size);
		res.append(_a);
		for_each(crts.begin(), crts.end(), [&](const string* s) { res.append(*s); });
		res.append(_b);

		cert = res;

		/*stringstream lbl;
		lbl << _a;
		for_each(crts.begin(), crts.end(), [&](const string* s) { lbl << *s; });
		lbl << _b;

		cert = lbl.str();*/
	}

	void CollapseTriangle()
	{
		if (neighbours.size() != 3)
			return;

		const pair<CVertex*, CVertex*> ns = FindNeighbours();
		if (ns.first == NULL)
			return;

		CVertex* n1 = FindNeedNeighbour(ns.first, ns.second);
		CVertex* n2 = FindNeedNeighbour(ns.second, ns.first);
		CVertex* n3 = FindMyNeedNeighbour(ns.first, ns.second);

		neighbours.clear();
		neighbours.push_back(n1);
		n1->SwapNeighbour(ns.first, this);
		neighbours.push_back(n2);
		n2->SwapNeighbour(ns.second, this);
		neighbours.push_back(n3);

		ns.first->neighbours.clear();
		ns.second->neighbours.clear();

		cert = "AB";
		_a = "A";
		_b = "B";
	}

protected:
	size_t _id;
	string _a;
	string _b;

	void SwapNeighbour(CVertex* oldn, CVertex* newn)
	{
		vector<CVertex*>::iterator it = find(neighbours.begin(), neighbours.end(), oldn);
		neighbours.erase(it);
		neighbours.push_back(newn);
	}

	CVertex* FindNeedNeighbour(CVertex* n1, CVertex* n2)
	{
		for (size_t i = 0; i < n1->neighbours.size(); ++i)
			if (n1->neighbours[i] != n2 && n1->neighbours[i] != this)
				return n1->neighbours[i];
		return NULL;
	}

	CVertex* FindMyNeedNeighbour(CVertex* n1, CVertex* n2)
	{
		for (size_t i = 0; i < neighbours.size(); ++i)
			if (neighbours[i] != n2 && neighbours[i] != n1)
				return neighbours[i];
		return NULL;
	}

	pair<CVertex*, CVertex*> FindNeighbours()
	{
		if (IsNeighbours(neighbours[0], neighbours[1]))
			return pair<CVertex*, CVertex*>(neighbours[0], neighbours[1]);
		if (IsNeighbours(neighbours[1], neighbours[2]))
			return pair<CVertex*, CVertex*>(neighbours[1], neighbours[2]);
		if (IsNeighbours(neighbours[0], neighbours[2]))
			return pair<CVertex*, CVertex*>(neighbours[0], neighbours[2]);
		return pair<CVertex*, CVertex*>(NULL, NULL);
	}

	static bool IsNeighbours(const CVertex* v1, const CVertex* v2)
	{
		return count(v1->neighbours.begin(), v1->neighbours.end(), v2) > 0;
	}
};
