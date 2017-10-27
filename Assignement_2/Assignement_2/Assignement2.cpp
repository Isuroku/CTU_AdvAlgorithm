// Assignement2.cpp: определяет точку входа для консольного приложения.
//
#include "IOSwitcher.h"
#include <sstream>
#include <cstdarg>
#include <vector>
#include <algorithm>
#include "Edge.h"
#include "Vertex.h"
#include "Assignement2.h"
#include "Tarjan.h"

#include <fstream>

#pragma warning( disable : 4996 ) //copy


const string arr_file_names[] =
{
	"Pd/pub01.in",
	"Pd/pub02.in",
	"Pd/pub03.in",
	"Pd/pub04.in",
	"Pd/pub05.in",
	"Pd/pub06.in",
	"Pd/pub07.in",
	"Pd/pub08.in",
	"Pd/pub09.in",
	"Pd/pub10.in",
};

const int arr_file_res[] =
{
	15,
	7,
	1600933,
	797967939
};

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


int main()
{
	int test_n = 7;

	CIOSwitcher IOSwitcher(true, arr_file_names[test_n]);

	string line;

	IOSwitcher.getline(line);
	int vertex_count, edge_count, wayfarers_count, destination_index;

	if (sscanf(line.c_str(), "%d %d %d %d", &vertex_count, &edge_count, &wayfarers_count, &destination_index) != 4)
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
		{
			cerr << "read wayfarers_vertex line was wrong!";
			
		}
		else
			wayfarers_vertex.push_back(val);
	});

	vector<CEdge> edges(edge_count);
	vector<CVertex> vertices(vertex_count);
	int v1, v2;
	int i = 0;
	while (IOSwitcher.getline(line))  //input from the file in.txt
	{
		if (sscanf(line.c_str(), "%d %d", &v1, &v2) != 2)
		{
			cerr << "read edge line " << i + 3 << " was wrong!";
			return 1;
		}

		edges[i].init(v1, v2);
		CVertex& V1 = vertices[v1 - 1];
		CVertex& V2 = vertices[v2 - 1];

		V1.SetID(v1);
		V2.SetID(v2);

		V1.SetNeighbours(&V2);

		i++;
	}
	
	CTarjan tarjan;
	tarjan.solve(vertices);

	tarjan.printscr();

    return 0;
}

