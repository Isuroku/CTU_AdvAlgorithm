
#include "MainHeader.h"
#include <string>
#include <stdio.h>
#include "IOSwitcher.h"
#include "MSTSolver.h"


int main()
{
	CIOSwitcher IOSwitcher(true, "Pd/pub10.in");

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

	cout << res;

    return 0;
}

