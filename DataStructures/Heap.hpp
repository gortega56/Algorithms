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
		Heap(T* t, const C& comparator, int heapSize, int length, algorithm::SortOrder order) : t(t), comparator(comparator), heapSize(heapSize), length(length), order(order)
		{
			algorithm::buildHeap(t, comparator, heapSize, length, order);
		}

		inline T& getParent(int index) const
		{
			return t[(index - 1) >> 1];
		}

		inline T& getLeft(int index) const
		{
			return t[(index << 1) + 1];
		}

		inline T& getRight(int index) const
		{
			return t[(index << 1) + 2];
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
		algorithm::SortOrder order;
	};
}