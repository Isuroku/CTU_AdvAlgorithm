#pragma once
#include <sstream>

class CVertex;

class CEdge
{

	int begin_vertex;
	int end_vertex;

public:
	CEdge()
	{
		begin_vertex = -1;
		end_vertex = -1;
	}

	CEdge(int v1, int v2)
	{
		begin_vertex = v1;
		end_vertex = v2;
	}

	void init(int v1, int v2)
	{
		begin_vertex = v1;
		end_vertex = v2;
	}



	int get_begin_vertex() { return begin_vertex; }
	int get_end_vertex() { return end_vertex; }

};

