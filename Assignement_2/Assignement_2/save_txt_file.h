#pragma once
#include <vector>
#include "VertexC.h"

class CSaveGraph
{
public:
	void save_txt_file(const vector<CVertexT>& graph, const string& file_name);


	CSaveGraph(): start_x(50), x_len(0), wide(0), start_y(50), height(0), screen_wide(1200), screen_height(600) {}
private:

	pair<size_t, size_t> screen_pos(const size_t index) const;

	void collect_labels(const vector<CVertexT>& graph, vector<pair<string, pair<size_t, size_t>>>& out_labels);

	size_t start_x;
	size_t x_len;
	size_t wide;
	size_t start_y;
	size_t height;

	size_t screen_wide;
	size_t screen_height;
};