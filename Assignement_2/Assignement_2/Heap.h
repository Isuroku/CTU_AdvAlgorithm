#pragma once
#include <vector>

using namespace std;

class CHeapElem;

struct SWeightComp
{
	virtual ~SWeightComp() {};

	virtual bool better(const CHeapElem& elem1, const CHeapElem& elem2) = 0;
};

class CHeapElem
{
public:
	virtual ~CHeapElem() = default;

	virtual float heap_weight() const = 0;
	virtual void set_heap_index(const size_t index) = 0;
	virtual size_t get_heap_index() const = 0;
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

	CHeap(SWeightComp* comp) :
		_array_size(0),
		_comp(comp)
	{
	}

	void insert(CHeapElem& inElem)
	{
		_array_size++;
		if (_array_size>_array.size())
			_array.resize(_array_size * 2 + 100, NULL);

		size_t dwI = _array_size;
		while (dwI > 1 && _comp->better(inElem, *_array[GetHeapParent(dwI) - 1]))
		{
			_array[dwI - 1] = _array[GetHeapParent(dwI) - 1];
			_array[dwI - 1]->set_heap_index(dwI);
			dwI = GetHeapParent(dwI);
		}
		_array[dwI - 1] = &inElem;
		_array[dwI - 1]->set_heap_index(dwI);
	}

	CHeapElem* Heap_Extract_Max()
	{
		//assert_andrey_ex(_array_size > 0, L"ѕопытка вытащить лист из пустой кучи!");
		CHeapElem* max = _array[0];
		_array[0] = _array[_array_size - 1];
		_array[0]->set_heap_index(1);
		_array_size--;
		if (_array_size)
			Heapify(1);
		max->set_heap_index(-1);
		return max;
	}

	void up(CHeapElem* inElem)
	{
		up(inElem->get_heap_index());
	}

	void up(const size_t in_heap_index)
	{
		size_t dwI = in_heap_index;
		if (dwI > 1 && _comp->better(*_array[dwI - 1], *_array[GetHeapParent(dwI) - 1]))
		{
			CHeapElem* p = _array[dwI - 1];
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

	void Heapify(const size_t in_dwInd)
	{
		//assert_andrey(_array_size);
		size_t l = GetHeapLeft(in_dwInd);
		size_t r = GetHeapRight(in_dwInd);
		size_t largest = in_dwInd;

		if (l <= _array_size && _comp->better(*_array[l - 1], *_array[in_dwInd - 1]))
			largest = l;
		if (r <= _array_size && _comp->better(*_array[r - 1], *_array[largest - 1]))
			largest = r;
		if (largest != in_dwInd)
		{
			CHeapElem *p = _array[largest - 1];
			_array[largest - 1] = _array[in_dwInd - 1];
			_array[largest - 1]->set_heap_index(largest);
			_array[in_dwInd - 1] = p;
			_array[in_dwInd - 1]->set_heap_index(in_dwInd);
			Heapify(largest);
		}
	}

	void clear()
	{
		_array_size = 0;
		_array.clear();
	}

	static size_t	GetHeapRight(const size_t in_dwInd) { return 2 * in_dwInd + 1; }
	static size_t	GetHeapLeft(const size_t in_dwInd) { return 2 * in_dwInd; }
	static size_t	GetHeapParent(const size_t in_dwInd) { return in_dwInd / 2; }

private:
	size_t	 _array_size;
	vector<CHeapElem*> _array;
	SWeightComp* _comp;
};
