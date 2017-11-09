
#include "stdafx.h"
#include "IOSwitcher.h"
#include <vector>
#include "Vertex.h"
#include "GraphSaver.h"
#include <sstream>

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



int main()
{
	const int test_n = 0;
	CIOSwitcher IOSwitcher(true, arr_file_names[test_n]);

	string line;
	IOSwitcher.getline(line);
	size_t molecule_count, vertex_count, edge_count;

	if (sscanf(line.c_str(), "%zu %zu %zu", &vertex_count, &edge_count, &molecule_count) != 3)
	{
		cerr << "read first line was wrong!";
		return 1;
	}

	vector<vector<CVertex>> molecules(molecule_count);

	CGraphSaver sg;
	
	for(size_t m = 0; m < molecule_count; m++)
	{
		vector<CVertex> mol_vec = molecules[m];
		mol_vec.resize(vertex_count);

		for (size_t e = 0; e < edge_count; e++)
		{
			IOSwitcher.getline(line);

			size_t ind1, ind2;
			if (sscanf(line.c_str(), "%zu %zu", &ind1, &ind2) != 2)
			{
				cerr << "read " << m * molecule_count + e + 1 << " line was wrong!";
				return 1;
			}

			CVertex& v1 = mol_vec[ind1 - 1];
			v1.set_id(ind1);
			CVertex& v2 = mol_vec[ind2 - 1];
			v2.set_id(ind2);

			v1.neighbours.push_back(&v2);
			v2.neighbours.push_back(&v1);
		}
		
		stringstream lbl;
		lbl << "m" << m << ".grafa";
		sg.save_txt_file(mol_vec, lbl.str());
	}

    return 0;
}

