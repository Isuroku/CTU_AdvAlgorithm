#pragma once
#include "StronglyConnectedComponents.h"

class CSimpleSCC: public CStronglyConnectedComponents
{
public:
	CSimpleSCC();
	~CSimpleSCC();

	void solve(vector<CVertexT>& vertices);
};

