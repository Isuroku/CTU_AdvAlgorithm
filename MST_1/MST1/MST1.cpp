
#include "MainHeader.h"
#include <string>
#include <stdio.h>
#include "IOSwitcher.h"
#include "MSTSolver.h"

//const string arr_file_names[] = 
//{
//	"Pd/pub01.in",
//	"Pd/pub09.in",
//};
//
//const int arr_file_res[] =
//{
//	15,
//	1600933,
//};

int main()
{
	const int test_n = 1;
	CIOSwitcher IOSwitcher(false, "Pd/pub01.in");
	//CIOSwitcher IOSwitcher(false, arr_file_names[test_n]);

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
	while (count < edge_count && IOSwitcher.getline(line))  //input from the file in.txt
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
	
	/*int check = arr_file_res[test_n];
	bool done = check == res;*/

	cout << res;

    return 0;
}

