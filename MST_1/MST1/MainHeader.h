#pragma once
#include <iostream>
#ifndef DEBUG
#define DEBUG true

using namespace std;

template <typename T>
void safe_delete(T*& p)
{
	if (p == NULL)
		return;
	delete(p);
	p = NULL;
}

#define debug_print(fmt, ...) \
            do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

#endif