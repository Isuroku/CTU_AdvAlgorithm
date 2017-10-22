
#include "MainHeader.h"
#include <string>
#include <stdio.h>
#include "IOSwitcher.h"


int main()
{
	CIOSwitcher IOSwitcher(false, "Pd/pub01.in");

	string line;

	int vertex_count, link_count;
	IOSwitcher.getline(line);
	if (sscanf(line.c_str(), "%d %d", &vertex_count, &link_count) != 2)
	{
		cerr << "read first line was wrong!";
		return 1;
	}

	int count = 0;
	int v1, v2, l;
	while (count < link_count && IOSwitcher.getline(line))  //input from the file in.txt
	{
		if (sscanf(line.c_str(), "%d %d %d", &v1, &v2, &l) != 3)
		{
			cerr << "read line " << count << " was wrong!";
			return 1;
		}
		count++;
	}

	cout << count;

    return 0;
}

