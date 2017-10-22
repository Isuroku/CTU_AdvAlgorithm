#pragma once
#include <iostream>
using namespace std;

template <typename T>
void safe_delete(T*& p)
{
	if (p == NULL)
		return;
	delete(p);
	p = NULL;
}