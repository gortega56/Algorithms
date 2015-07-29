// Heap.hpp
//
//
// Gabriel Ortega

#pragma once 
#include "../Algorithms/comparison_sorts.hpp"

namespace cliqCity
{
	template <class T, class C>
	class Heap
	{
	public:
		Heap(T* t, const C& comparator, int heapSize, int length) : t(t), comparator(comparator), heapSize(heapSize), length(length)
		{
			algorithm::buildHeap(t, comparator, heapSize, length);
		}

		inline T& getParent(int index) const
		{
			return t[index >> 1];
		}

		inline T& getLeftIndex(int index) const
		{
			return t[index << 1];
		}

		inline T& getRightIndex(int index) const
		{
			return t[(index << 1) + 1];
		}

		inline int getHeapSize() const
		{
			return heapSize;
		}

		inline int getLength() const
		{
			return length;
		}

	private:
		T* t;
		C comparator;
		int heapSize;
		int length;
	};
}