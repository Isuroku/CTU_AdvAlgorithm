// Assignement2.cpp: определяет точку входа для консольного приложения.
//
#include "IOSwitcher.h"
#include <sstream>


const string arr_file_names[] =
{
	"Pd/pub01.in",
	"Pd/pub02.in",
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

int main()
{
	int test_n = 0;
	CIOSwitcher IOSwitcher(true, arr_file_names[test_n]);

	string line;


	IOSwitcher.getline(line);
	int vertex_count, edge_count, wayfarers_count, destination_index;

	if (sscanf(line.c_str(), "%d %d %d %d", &vertex_count, &edge_count, &wayfarers_count, &destination_index) != 4)
	{
		cerr << "read first line was wrong!";
		return 1;
	}
	stringstream os;
	for (int i = 0; i < wayfarers_count; i++)
		os << "%d ";

	int* a = new int[wayfarers_count];
	
	if (sscanf(line.c_str(), os.str().c_str(), a) != wayfarers_count)
	{
		cerr << "read first line was wrong!";
		return 1;
	}
    return 0;
}

