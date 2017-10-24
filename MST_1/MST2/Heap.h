#pragma once
#include "Vertex.h"

struct SWeightComp
{
	virtual ~SWeightComp() {};

	virtual bool better(const int weight1, const int weight2) = 0;
};

class CHeap
{
public:

	CHeap(const size_t count, SWeightComp* comp):
		_array_size(0),
		_array(count, NULL),
		_comp(comp)
	{
	}

	void insert(CVertex* in_pLeaf)
	{
		_array_size++;
		if (_array_size>_array.size())
			_array.resize(_array_size * 2 + 100, NULL);

		int dwI = _array_size;
		while (dwI > 1 && _comp->better(in_pLeaf->heap_weight(), _array[GetHeapParent(dwI) - 1]->heap_weight()))
		{
			_array[dwI - 1] = _array[GetHeapParent(dwI) - 1];
			_array[dwI - 1]->set_heap_index(dwI);
			dwI = GetHeapParent(dwI);
		}
		_array[dwI - 1] = in_pLeaf;
		_array[dwI - 1]->set_heap_index(dwI);
	}

	CVertex* Heap_Extract_Max()
	{
		//assert_andrey_ex(_array_size > 0, L"ѕопытка вытащить лист из пустой кучи!");
		CVertex* max = _array[0];
		_array[0] = _array[_array_size - 1];
		_array[0]->set_heap_index(1);
		_array_size--;
		if (_array_size)
			Heapify(1);
		max->set_heap_index(-1);
		return max;
	}

	void up(const int in_heap_index)
	{
		int dwI = in_heap_index;
		if (dwI > 1 && _comp->better(_array[dwI - 1]->heap_weight(), _array[GetHeapParent(dwI) - 1]->heap_weight()))
		{
			CVertex* p = _array[dwI - 1];
			_array[dwI - 1] = _array[GetHeapParent(dwI) - 1];
			_array[dwI - 1]->set_heap_index(dwI);
			dwI = GetHeapParent(dwI);
			_array[dwI - 1] = p;
			_array[dwI - 1]->set_heap_index(dwI);
			up(dwI);
		}
	}

	bool IsEmpty() const
	{
		return _array_size == 0;
	}

	void Heapify(size_t in_dwInd)
	{
		//assert_andrey(_array_size);
		size_t l = GetHeapLeft(in_dwInd);
		size_t r = GetHeapRight(in_dwInd);
		size_t largest = in_dwInd;

		if (l <= _array_size && _comp->better(_array[l - 1]->heap_weight(), _array[in_dwInd - 1]->heap_weight()))
			largest = l;
		if (r <= _array_size && _comp->better(_array[r - 1]->heap_weight(), _array[largest - 1]->heap_weight()))
			largest = r;
		if (largest != in_dwInd)
		{
			CVertex *p = _array[largest - 1];
			_array[largest - 1] = _array[in_dwInd - 1];
			_array[largest - 1]->set_heap_index(largest);
			_array[in_dwInd - 1] = p;
			_array[in_dwInd - 1]->set_heap_index(in_dwInd);
			Heapify(largest);
		}
	}

	size_t	GetHeapRight(size_t in_dwInd) { return 2 * in_dwInd + 1; }
	size_t	GetHeapLeft(size_t in_dwInd) { return 2 * in_dwInd; }
	size_t	GetHeapParent(size_t in_dwInd) { return in_dwInd / 2; }

private:
	size_t	 _array_size;
	vector<CVertex*> _array;
	SWeightComp* _comp;
};
