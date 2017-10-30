#include "save_txt_file.h"
#include <fstream>

void CSaveGraph::save_txt_file(const vector<CVertexT>& graph, const string& file_name)
{
	const size_t count = graph.size();

	x_len = static_cast<size_t>(sqrt(count));
	wide = (screen_wide - start_x) / x_len;
	height = (screen_height - start_y) / x_len;

	vector<pair<string, pair<size_t, size_t>>> out_labels;
	collect_labels(graph, out_labels);

	ofstream out(file_name); // "out.grafa");

	out << "[Main]" << endl;
	out << "IsOrint=1" << endl;
	out << "IsHaveCost=0" << endl;
	out << "PointCount=" << graph.size() << endl;
	out << "GrafTitleType=0" << endl;
	out << "Version=1" << endl;
	out << "CountLabel=" << out_labels.size() << endl;
	
	out << "[Matrix]" << endl;

	vector<size_t> adj_m(count * count, 0);

	for (size_t i = 0; i < count; ++i)
	{
		const CVertexT& v = graph[i];
		for (size_t n = 0; n < v.neighbours.size(); ++n)
		{
			CVertexT* nv = v.neighbours[n];
			const size_t p = (nv->_id - 1) * count + (v._id - 1);
			adj_m[p] = 1;
		}
	}

	for(size_t i = 0; i < count; ++i)
		for (size_t j = 0; j < count; ++j)
		{
			const size_t p = i * count + j;
			out << "From" << i + 1 << "To" << j + 1 << "=" << adj_m[p] << endl;
		}

	out << "[GrafPosition]" << endl;
	for (size_t i = 0; i < count; ++i)
	{
		const CVertexT& v = graph[i];
		const pair<size_t, size_t> pr = screen_pos(i);
		out << "X" << v.id() << "=" << pr.first << endl;
		out << "Y" << v.id() << "=" << pr.second << endl;
	}

	out << "[Labels]" << endl;
	int label_index = 1;
	for (size_t i = 0; i < out_labels.size(); ++i)
	{
		out << "LabelText" << label_index << "=" << out_labels[i].first << endl;
		out << "X" << label_index << "=" << out_labels[i].second.first << endl;
		out << "Y" << label_index << "=" << out_labels[i].second.second << endl;
		label_index++;
	}

	out << "[GrafTitle]" << endl;
	out << "BeginNumber=1" << endl;
}

pair<size_t, size_t> CSaveGraph::screen_pos(const size_t index) const
{
	const size_t row = index / x_len;
	const size_t col = index - row * x_len;

	const size_t x = col * wide + start_x;
	const size_t y = row * height + start_y;

	return pair<size_t, size_t>(x, y);
}

void CSaveGraph::collect_labels(const vector<CVertexT>& graph, vector<pair<string, pair<size_t, size_t>>>& out_labels)
{
	for (size_t i = 0; i < graph.size(); ++i)
	{
		pair<size_t, size_t> pos = screen_pos(i);

		pos.second += 30;

		const CVertexT& v = graph[i];
		if (v.dest)
			out_labels.push_back(pair<string, pair<size_t, size_t>>("Dest", pos));
		if (v.get_wayfarer_count() > 0)
		{
			stringstream lbl;
			lbl << v.get_wayfarer_count() << " WF";
			out_labels.push_back(pair<string, pair<size_t, size_t>>(lbl.str(), pos));
		}
	}
}
