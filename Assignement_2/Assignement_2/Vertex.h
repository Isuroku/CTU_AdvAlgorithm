#pragma once
#include <cstddef>
#include <vector>

using namespace std;

class CVertex
{
public:
	vector<CVertex*> neighbours;
	vector<CVertex*> rear_neighbours;

	CVertex(): _id(0) {}

	size_t id() const { return _id; }
	void set_id(const size_t in_id) { _id = in_id; }

	size_t vec_index() const { return _id - 1; }

	virtual string get_debuf_info() const { return string(""); }

protected:
	size_t _id;
};