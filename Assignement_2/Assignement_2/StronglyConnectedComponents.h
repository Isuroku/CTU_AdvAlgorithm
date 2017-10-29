#pragma once

#include "Vertex.h"
#include "VertexC.h"

using namespace std;

class CStronglyConnectedComponents
{
public:
	const vector<CVertexT*>& GetComponent(const size_t index) const { return _scc[index]; }
	size_t GetComponentsCount() const { return _scc.size(); }

	static bool compare_scc(const CStronglyConnectedComponents& scc1, const CStronglyConnectedComponents& scc2)
	{
		bool res = true;

		const size_t components_count_t = scc1.GetComponentsCount();
		const size_t components_count_s = scc2.GetComponentsCount();

		if (components_count_t != components_count_s)
		{
			cerr << "scc is wrong! [comps count]" << endl;
			res = false;
		}
		else
		{
			for (size_t i = 0; i < components_count_t; ++i)
			{
				const vector<CVertexT*>& comp_t = scc1.GetComponent(i);
				const vector<CVertexT*>& comp_s = scc2.GetComponent(i);
				if (comp_t.size() != comp_s.size())
				{
					cerr << "scc is wrong! [comp " << i << " count]" << endl;
					res = false;
				}
				else
				{
					for (size_t e = 0; e < comp_t.size(); ++e)
					{
						if (comp_t[e] != comp_s[e])
						{
							cerr << "scc is wrong! [comp " << i << " elem " << e << "]" << endl;
							res = false;
						}

						if (comp_t[e]->comp_index != comp_s[e]->comp_index)
						{
							cerr << "scc is wrong! [comp index " << i << " elem " << e << "]" << endl;
							res = false;
						}
					}
				}
			}
		}

		return res;
	}

	static void reduct_graph(const CStronglyConnectedComponents& inSCC, vector<CVertexC>& out_component_vertices)
	{
		out_component_vertices.resize(inSCC.GetComponentsCount());

		for (size_t i = 0; i < out_component_vertices.size(); i++)
		{
			CVertexC& var_c = out_component_vertices[i];

			const vector<CVertexT*>& comp = inSCC.GetComponent(i);

			var_c.weight = comp.size();

			for (size_t j = 0; j < comp.size(); j++)
			{
				CVertexT* var_t = comp[j];
				var_c.included.push_back(var_t);

				for (size_t k = 0; k < var_t->neighbours.size(); k++)
				{
					CVertexT* n = var_t->neighbours[k];
					const size_t n_comp_index = n->comp_index;
					if (n_comp_index != var_t->comp_index)
					{
						CVertexC& cn = out_component_vertices[n_comp_index];
						if (find(var_c.neighbours.begin(), var_c.neighbours.end(), &cn) == var_c.neighbours.end())
						{
							var_c.neighbours.push_back(&cn);
							cn.rear_neighbours.push_back(&var_c);
						}
					}
				}

				var_c.wayfarer_count += var_t->wayfarer_count;
				if (var_t->isDestination)
					var_c.dest = true;

				const size_t id = var_t->id();
				var_c.set_id(id);
			}
		}
	}

protected:
	vector<vector<CVertexT*>> _scc;
};

