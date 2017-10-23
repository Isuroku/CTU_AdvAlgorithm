//#include "Constants.h"
//#include "Vertex.h"
//#include <deque>
//#include <unordered_set>
//
//int wave_num = 0;
//
//std::deque<CVertex*> to_visit;
//std::unordered_set<CVertex*> _visited;
//
//bool find_circle_in_linked_graph(CVertex* vert)
//{
//	to_visit.clear();
//	_visited.clear();
//
//	bool was_circle = false;
//
//	to_visit.push_back(vert);
//	vert->set_parent(NULL);
//
//	while (!was_circle && !to_visit.empty())
//	{
//		CVertex* v = to_visit.back();
//		to_visit.pop_back();
//
//		_visited.insert(v);
//
//		size_t nc = v->get_neighbour_count();
//		for (size_t i = 0; i < nc; ++i)
//		{
//			CVertex* n = v->get_neighbour(i);
//			if (_visited.find(n) == _visited.end())
//			{
//				to_visit.push_back(n);
//				n->set_parent(v);
//			}
//			else
//				was_circle = n != v->get_parent();
//		}
//	}
//
//	return was_circle;
//}
