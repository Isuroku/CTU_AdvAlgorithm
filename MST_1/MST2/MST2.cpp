#include <iostream>
#include <string>
#include <stdio.h>
#include "IOSwitcher.h"
#include "MSTSolver.h"

using namespace std;

const string arr_file_names[] =
{
	"Pd/pub01.in",
	"Pd/pub02.in",
	"Pd/pub03.in",
	"Pd/pub09.in",
	"Pd/pub10.in",
};

const int arr_file_res[] =
{
	15,
	7,
	19,
	1600933,
	797967939
};


int main()
{
	const int test_n = 0;
	CIOSwitcher IOSwitcher(true, arr_file_names[test_n]);

	string line;

	int vertex_count, edge_count;
	IOSwitcher.getline(line);
	if (sscanf(line.c_str(), "%d %d", &vertex_count, &edge_count) != 2)
	{
		cerr << "read first line was wrong!";
		return 1;
	}

	CMSTSolver solver(vertex_count, edge_count);

	int count = 0;
	int v1, v2, l;
	while (IOSwitcher.getline(line))  //input from the file in.txt
	{
		if (sscanf(line.c_str(), "%d %d %d", &v1, &v2, &l) != 3)
		{
			cerr << "read line " << count << " was wrong!";
			return 1;
		}

		solver.add_edge(count, v1, v2, l);

		count++;
	}

	int res = solver.solve();

	int check = arr_file_res[test_n];
	bool done = check == res;

	cout << res;

    return 0;
}

