#pragma once
#include <vector>
#include "Vertex.h"
#include <fstream>
#include <math.h>

class CSaveGraph
{
public:
	template<typename T>
	void save_txt_file(const vector<T>& graph, const string& file_name)
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
			const T& v = graph[i];
			for (size_t n = 0; n < v.neighbours.size(); ++n)
			{
				T* nv = v.neighbours[n];
				const size_t p = (nv->vec_index()) * count + (v.vec_index());
				adj_m[p] = 1;
			}
		}

		for (size_t i = 0; i < count; ++i)
			for (size_t j = 0; j < count; ++j)
			{
				const size_t p = i * count + j;
				out << "From" << i + 1 << "To" << j + 1 << "=" << adj_m[p] << endl;
			}

		out << "[GrafPosition]" << endl;
		for (size_t i = 0; i < count; ++i)
		{
			const T& v = graph[i];
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


	CSaveGraph(): start_x(50), x_len(0), wide(0), start_y(50), height(0), screen_wide(1000), screen_height(400) {}
private:

	pair<size_t, size_t> screen_pos(const size_t index) const;

	template<typename T>
	void collect_labels(const vector<T>& graph, vector<pair<string, pair<size_t, size_t>>>& out_labels) const
	{
		for (size_t i = 0; i < graph.size(); ++i)
		{
			pair<size_t, size_t> pos = screen_pos(i);

			pos.second += 30;

			const T& v = graph[i];
			string s = v.get_debuf_info();

			if (!s.empty())
				out_labels.push_back(pair<string, pair<size_t, size_t>>(s, pos));
		}
	}

	size_t start_x;
	size_t x_len;
	size_t wide;
	size_t start_y;
	size_t height;

	size_t screen_wide;
	size_t screen_height;
};
