// Assignement2.cpp: определяет точку входа для консольного приложения.
//
#include "IOSwitcher.h"
#include <sstream>
#include <cstdarg>
#include <vector>
#include <algorithm>
//#include "Edge.h"
#include "VertexT.h"
#include "Assignement2.h"
#include "Tarjan.h"

#include <fstream>
#include "VertexC.h"
#include "Dijkstra.h"
#include "SimpleSCC.h"
#include "save_txt_file.h"

#pragma warning( disable : 4996 ) //copy


const string arr_file_names[] =
{
	"Pd/pub01.in", //3
	"Pd/pub02.in", //3
	"Pd/pub03.in", //8
	"Pd/pub04.in", //8
	"Pd/pub05.in", //16 
	"Pd/pub06.in", //82 - 5
	"Pd/pub07.in", //30
	"Pd/pub08.in", //4417
	"Pd/pub09.in", //5
	"Pd/pub10.in", //131282
};

const size_t arr_file_res[] = { 3,	3, 8, 8, 16, 82, 30, 4417, 5, 131282 };

void split(const string& instr, const string& delimeter, vector<string>& out_strings)
{
	const size_t delim_size = delimeter.length();
	const size_t buf_size = instr.length() + 1;
	char* buffer = new char[buf_size];
	size_t prev_pos = 0;
	size_t pos = instr.find(delimeter, prev_pos);
	while(pos < instr.length())
	{
		size_t length = instr.copy(buffer, pos - prev_pos, prev_pos);
		buffer[length] = '\0';

		out_strings.push_back(string(buffer));

		prev_pos = pos + delim_size;
		pos = instr.find(delimeter, prev_pos);
		if(pos == string::npos)
		{
			length = instr.copy(buffer, instr.length() - prev_pos, prev_pos);
			buffer[length] = '\0';

			out_strings.push_back(string(buffer));
		}
	}
}

bool check_component_vertices(const vector<CVertexC>& component_vertices, const size_t wayfarers_count)
{
	size_t wf = 0;
	bool dest = false;

	for (size_t i = 0; i < component_vertices.size(); i++)
	{
		if (!component_vertices[i].check())
			return false;

		if(component_vertices[i].dest)
		{
			if(dest)
			{
				cerr << "repeat dest" << endl;
				return false;
			}

			dest = true;
			cout << " Dest in " << component_vertices[i]._id << endl;
		}

		if(component_vertices[i].get_wayfarer_count() > 0)
			cout << component_vertices[i].get_wayfarer_count() << " WF in " << component_vertices[i]._id << endl;

		wf += component_vertices[i].get_wayfarer_count();
	}

	if (wayfarers_count != wf)
	{
		cerr << "wayfarers sum error" << endl;
		return false;
	}

	if (!dest)
	{
		cerr << "dest error" << endl;
		return false;
	}

	return true;
}

int main()
{
	int test_n = 8;

	CIOSwitcher IOSwitcher(false, arr_file_names[test_n]);

	string line;

	IOSwitcher.getline(line);
	size_t vertex_count, edge_count, wayfarers_count, destination_index;

	if (sscanf(line.c_str(), "%zu %zu %zu %zu", &vertex_count, &edge_count, &wayfarers_count, &destination_index) != 4)
	{
		cerr << "read first line was wrong!";
		return 1;
	}

	IOSwitcher.getline(line);

	vector<string> strings;
	split(line, string(" "), strings);

	vector<int> wayfarers_vertex; //вертексы ходоков 

	for_each(strings.begin(), strings.end(), [&wayfarers_vertex](const string& s)
	{
		int val;
		if (sscanf(s.c_str(), "%d", &val) != 1)
			cerr << "read wayfarers_vertex line was wrong!";
		else
			wayfarers_vertex.push_back(val);
	});

	//vector<CEdge> edges(edge_count);
	vector<CVertexT> vertices(vertex_count);
	vertices[destination_index - 1].dest = true;
	int v1, v2;
	int i = 0;
	while (IOSwitcher.getline(line))  //input from the file in.txt
	{
		if (sscanf(line.c_str(), "%d %d", &v1, &v2) != 2)
		{
			cerr << "read edge line " << i + 3 << " was wrong!";
			return 1;
		}

		//edges[i].init(v1, v2);
		CVertexT& V1 = vertices[v1 - 1];
		CVertexT& V2 = vertices[v2 - 1];

		V1.set_id(v1);
		V2.set_id(v2);

		V1.neighbours.push_back(&V2);

#ifdef MY_TEST
		V2.rear_neighbours.push_back(&V1);
#endif // MY_TEST

		i++;
	}

	size_t wayfarers_ids = 0;
	for_each(wayfarers_vertex.begin(), wayfarers_vertex.end(), [&wayfarers_ids, &vertices](int w_t_i)
	{
		vertices[w_t_i - 1].wayfarers.push_back(wayfarers_ids++);
	});

#ifdef MY_TEST
	CSimpleSCC simple_scc;
	simple_scc.solve(vertices);
#endif //MY_TEST

	/*CSaveGraph sg;
	sg.save_txt_file(vertices, "out.grafa");
	return 0;*/
	
	CTarjan tarjan;
	tarjan.solve(vertices, false);

#ifdef MY_TEST
	if(!CStronglyConnectedComponents::compare_scc(tarjan, simple_scc))
	{
		cerr << "scc is wrong! out!" << endl;
		return 1;
	}
#endif //MY_TEST

	const size_t components_count_t = tarjan.GetComponentsCount();

	vector<CVertexC> component_vertices(components_count_t);

	CStronglyConnectedComponents::reduct_graph(static_cast<CStronglyConnectedComponents>(tarjan), component_vertices);

	cout << 10;

	return 0;

#ifdef MY_TEST
	if(!check_component_vertices(component_vertices, wayfarers_count))
	{
		cerr << "reduct scc is wrong! out!" << endl;
		return 1;
	}
#endif //MY_TEST

	/*CSaveGraph sg;
	sg.save_txt_file(component_vertices, "out.grafa");
	return 0;*/

	deque<CVertexC*> vstack;

	size_t max_res = 0;

	for (size_t i = 0; i < component_vertices.size(); i++)
	{
		vstack.clear();

		vector<size_t> wayfarer_finded(wayfarers_count, false);

		CVertexC& var_c = component_vertices[i];
		size_t find_w = 0;
		
		//for each(size_t wf in var_c.wayfarers)
		for_each(var_c.wayfarers.begin(), var_c.wayfarers.end(), [&find_w, &wayfarer_finded](size_t wf)
		{
			if (!wayfarer_finded[wf])
			{
				wayfarer_finded[wf] = true;
				find_w++;
			}
		});

		vstack.push_back(&var_c);

		while(!vstack.empty() && find_w < wayfarers_count)
		{
			CVertexC* v = vstack.back();
			vstack.pop_back();

			//for each(CVertexC* rn in v->rear_neighbours)
			for_each(v->rear_neighbours.begin(), v->rear_neighbours.end(), [&find_w, &wayfarer_finded, &vstack](CVertexC* rn)
			{
				for_each(rn->wayfarers.begin(), rn->wayfarers.end(), [&find_w, &wayfarer_finded](size_t wf)
				{
					if (!wayfarer_finded[wf])
					{
						wayfarer_finded[wf] = true;
						find_w++;
					}
				});

				vstack.push_back(rn);
			});
		}

		if (find_w == wayfarers_count)
		{
			size_t res = FindPathLength(&var_c);

//#ifdef MY_TEST
			cerr << var_c.id() << "/" << component_vertices.size() << ": res " << res << "; max " << max_res << endl;
//#endif //MY_TEST

			var_c.result = true;
			var_c.result_length = res;

			max_res = max(max_res, res);
		}
	}

	cout << max_res;

	bool done = max_res == arr_file_res[test_n];
    return done ? 0 : 1;
}

