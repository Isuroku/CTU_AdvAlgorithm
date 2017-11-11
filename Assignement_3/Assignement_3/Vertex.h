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

	CVertex() : cert("ab"), _id(0)
	{
	}

	size_t id() const { return _id; }
	void set_id(const size_t in_id) { _id = in_id; }

	size_t vec_index() const { return _id - 1; }

	string get_debuf_info() const { return ""; }

	bool is_leaf() const { return neighbours.size() == 1; };

	static bool icmp(const string* elem1, const string* elem2)
	{
		return _stricmp(elem1->c_str(), elem2->c_str()) < 0;
	}

	void MergeCert(vector<CVertex*>& childs)
	{
		vector<string*> crts;
		crts.reserve(childs.size() + 1);

		string part;
		if (cert.length() > 2)
		{
			part = cert.substr(1, cert.length() - 2);
			crts.push_back(&part);
		}

		for (size_t j = neighbours.size() - 1; j != size_t(-1); j--)
		{
			CVertex* n = neighbours[j];
			if (count(childs.begin(), childs.end(), n) > 0)
			{
				vector<string*>::iterator it = lower_bound(crts.begin(), crts.end(), &n->cert, icmp);
				crts.insert(it, &n->cert);

				n->neighbours.clear();

				neighbours.erase(neighbours.begin() + j);
			}
		}

		stringstream lbl;
		lbl << "a";
		for_each(crts.begin(), crts.end(), [&](const string* s) { lbl << *s; });
		lbl << "b";

		cert = lbl.str();
	}

protected:
	size_t _id;
};
