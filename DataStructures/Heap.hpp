#pragma once 
#ifndef HEAP_H
#define HEAP_H

namespace cliqCity
{
	template <class T, class C>
	class Heap
	{
	public:
		Heap(T* t, int heapSize, int length, SortOrder order) : t(t), comparator(C()), heapSize(heapSize), length(length), order(order)
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
		SortOrder order;
	};
}

#endif