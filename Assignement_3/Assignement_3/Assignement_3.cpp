
#include "stdafx.h"
#include "IOSwitcher.h"
#include <vector>
#include "Vertex.h"
#include "GraphSaver.h"
#include <sstream>
#include <algorithm>

const string arr_file_names[] =
{
	"Pd/pub01.in", //1 2
	"Pd/pub02.in", //1 1
	"Pd/pub03.in", //3
	"Pd/pub04.in", //1 2 2
	"Pd/pub05.in", //3 5 
	"Pd/pub06.in", //2 4 4 5
	"Pd/pub07.in", //31 39
	"Pd/pub08.in", //5 7 10 12 12 14
	"Pd/pub09.in", //1 2 2 2 2 3 3 4 5 6
	"Pd/pub10.in", //4 6 6 8 11 12 14 14 17 18
};

bool ReadSources(const int test_n, const bool inSaveGraphToFile, vector<vector<CVertex>>& outAllData)
{
	CIOSwitcher IOSwitcher(true, arr_file_names[test_n]);

	string line;
	IOSwitcher.getline(line);
	int molecule_count, vertex_count, edge_count;

	if (sscanf(line.c_str(), "%d %d %d", &vertex_count, &edge_count, &molecule_count) != 3)
	{
		cerr << "read first line was wrong!";
		return false;
	}

	outAllData.resize(molecule_count);

	CGraphSaver sg;

	for (size_t m = 0; m < static_cast<size_t>(molecule_count); m++)
	{
		vector<CVertex>& mol_vec = outAllData[m];
		mol_vec.resize(vertex_count);

		for (size_t e = 0; e < static_cast<size_t>(edge_count); e++)
		{
			IOSwitcher.getline(line);

			int ind1, ind2;
			if (sscanf(line.c_str(), "%d %d", &ind1, &ind2) != 2)
			{
				cerr << "read " << m * molecule_count + e + 1 << " line was wrong!";
				return false;
			}

			CVertex& v1 = mol_vec[ind1 - 1];
			v1.set_id(ind1);
			CVertex& v2 = mol_vec[ind2 - 1];
			v2.set_id(ind2);

			v1.neighbours.push_back(&v2);
			v2.neighbours.push_back(&v1);
		}

		if (inSaveGraphToFile)
		{
			stringstream lbl;
			lbl << "m" << m << ".grafa";
			sg.save_txt_file(mol_vec, lbl.str());
		}
	}
	return true;
}

struct SMolClasses
{
	string Cert;
	size_t Count;

	SMolClasses(): Cert(""), Count(0) {	}
	SMolClasses(const string& inCert) : Cert(inCert), Count(1) {	}

	static bool cmp(const SMolClasses& elem1, const SMolClasses& elem2)
	{
		return elem1.Count < elem2.Count;
	}
};



struct SFindRes
{
	string cert;

	SFindRes(const string& incert): cert(incert) {}

	bool operator()(const SMolClasses& other) const
	{
		return strcmp(cert.c_str(), other.Cert.c_str()) == 0;
	}
};

void CollectChilds(vector<CVertex>& in_vertices, vector<vector<CVertex*>>& out_childs, vector<size_t>& out_indices)
{
	for_each(in_vertices.begin(), in_vertices.end(), [&](CVertex& v)
	{
		size_t sz = v.neighbours.size();
		if (sz != 1)
			return;

		size_t index = v.neighbours[0]->vec_index();
		out_childs[index].push_back(&v);

		vector<size_t>::iterator it = lower_bound(out_indices.begin(), out_indices.end(), index);
		if(it == out_indices.end() || *it != index)
			out_indices.insert(it, index);
	});
}

void MergeChilds(vector<size_t>& indices, vector<CVertex>& in_vertices, vector<vector<CVertex*>>& io_childs)
{
	for_each(indices.begin(), indices.end(), [&](size_t index)
	{
		vector<CVertex*>& childs = io_childs[index];
		CVertex& parent = in_vertices[index];
		parent.MergeCert(childs);
		childs.clear();
	});
}

void InsertNewCert(const string& inCert, vector<SMolClasses>& outResult)
{
	const vector<SMolClasses>::iterator it = find_if(outResult.begin(), outResult.end(), SFindRes(inCert));
	if (outResult.end() != it)
		it->Count++;
	else
		outResult.push_back(SMolClasses(inCert));
}

int main()
{
	vector<vector<CVertex>> molecules;
	if (!ReadSources(9, false, molecules))
		return 1;

	vector<SMolClasses> result;

	vector<size_t> indices;
	vector<vector<CVertex*>> childs;

	for_each(molecules.begin(), molecules.end(), [&](vector<CVertex>& mol)
	{
		childs.resize(mol.size());
		indices.clear();

		for_each(mol.begin(), mol.end(), [](CVertex& v) { v.CollapseTriangle(); });

		CollectChilds(mol, childs, indices);

		while(indices.size() > 2)
		{
			MergeChilds(indices, mol, childs);

			indices.clear();
			CollectChilds(mol, childs, indices);
		}

		MergeChilds(indices, mol, childs);

		string cert;
		if(indices.size() == 1)
		{
			cert = mol[indices[0]].cert;
		}
		else
		{
			stringstream lbl;
			string& ch_cert1 = mol[indices[0]].cert;
			string& ch_cert2 = mol[indices[1]].cert;
			if (CVertex::icmp(&ch_cert1, &ch_cert2))
				lbl << ch_cert1 << ch_cert2;
			else
				lbl << ch_cert2 << ch_cert1;
			cert = lbl.str();
		}

		InsertNewCert(cert, result);
	});

	sort(result.begin(), result.end(), SMolClasses::cmp);

	cout << result[0].Count;
	for(size_t i = 1; i < result.size(); ++i)
		cout << " " << result[i].Count;

    return 0;
}



