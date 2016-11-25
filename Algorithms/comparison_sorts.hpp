// comparison_sorts.hpp
//
// Comparison Sort Algorithms
//
// Gabriel Ortega

#pragma once
#include <cmath>
#include <climits>
#include <stdio.h>
#include "common.hpp"

namespace cliqCity
{
	namespace algorithm
	{	
		// Insertion Sort: Sort array of type T in place. Insertion sort is stable and has quadratic complexity.
		template<class T, class C> 
		void insertionSort(T* const t, const C& comparator, const int& length, const SortOrder order)
		{
			for (int j = 1; j < length; j++) {
				T temp = t[j];
				int i = j - 1;
				while (i >= 0 && comparator(t[i], temp) == order) {
					t[i + 1] = t[i];
					i--;
				}
				t[i + 1] = temp;
			}
		}

		// Bubble Sort: Stable algorithm that sorts elements in place. Quadratic complexity.
		template<class T, class C>
		void bubbleSort(T* const t, const C& comparator, const int& length, SortOrder order)
		{
			for (int i = 0; i < length; i++) {
				for (int j = length - 1; j > 0; j--) {
					if (comparator(t[j - 1], t[j]) == order) {
						exchange(t[j], t[j - 1]);
					}
				}
			}
		}

		// Partition: A subroutine used by Quick Sort. Partitions array t into subarrays of values less than and greater than the partition element. Always uses last element as partition.
		// TO DO: Optimize for non distinct elements by returning a partition range. Median of 3 partition.
		template<class T, class C>
		int partition(T* const t, const C& comparator, const int& begin, const int& end, SortOrder order)
		{
			int partition = end - 1;
			int right = begin - 1;

			// Sort elements based on comparison with partition element
			for (int left = begin; left < partition; left++) {
				int comparison = comparator(t[left], t[partition]);
				if ((comparison <= 0 && order == SortOrderAscending) || (comparison >= 0 && order == SortOrderDescending)) {
					exchange(t[++right], t[left]);
				}
			}

			// Swap partition with first element of right sub array
			exchange(t[++right], t[partition]);

			return right;
		}

		// Quick Sort: Recursively sorts using Partition subroutine. Runs in worst case quadratic time, and nlgn expected time. Asymptotic performance can be improved via randomization
		// TO DO: Optimize using tail recursive sort.
		template<class T, class C>
		void quickSort(T* const t, const C& comparator, const int& begin, const int& end, SortOrder order)
		{
			if (end - begin > 1) {
				int p = partition(t, comparator, begin, end, order);
				quickSort(t, comparator, begin, p, order);
				quickSort(t, comparator, p + 1, end, order);
			}
		}

		// Randomized Quick Sort: Quick Sort with a randomly selected partition element.
		template<class T, class C>
		void randomizedQuickSort(T* const t, const C& comparator, const int& begin, const int& end, SortOrder order)
		{
			if (end - begin > 1) {
				exchange(t[end - 1], t[rand() % (end - 1)]);
				int p = partition(t, comparator, begin, end, order);
				randomizedQuickSort(t, comparator, begin, p, order);
				randomizedQuickSort(t, comparator, p + 1, end, order);
			}
		}

		// Build Heap: Uses subroutine to construct a heap given array t, and has linear Complexity
		template<class T, class C>
		void buildHeap(T* const t, const C& comparator, const int& length, SortOrder order)
		{
			int heapSize = length;
			for (int i = (length / 2); i >= 0; i--) {
				heapify(t, comparator, i, heapSize, order);
			}
		}

		// Heapify: Sorts an array in place to statisfy a heap property defined by comparator and sort order. Runs in logarithmic complexity
		template<class T, class C>
		void heapify(T* const t, const C& comparator, const int& index, const int& heapSize, SortOrder order)
		{
			// Get left and right child.
			int left	= (index << 1) + 1;
			int right	= (index << 1) + 2;

			// Find target value (min or max).
			int target;
			if (left < heapSize && comparator(t[left], t[index]) == order) {
				target = left;
			}
			else {
				target = index;
			}

			if (right < heapSize && comparator(t[right], t[target]) == order) {
				target = right;
			}

			// Swap if either child is greater/smaller and heapify the target.
			if (target != index) {
				exchange(t[index], t[target]);
				heapify(t, comparator, target, heapSize, order);
			}
		}

		// Heap Sort: Sorts array in place by constructing a heap. This sort is stable and runs in O(nlgn) complexity.
		template<class T, class C>
		void heapSort(T* const t, const C& comparator, const int& length, SortOrder order)
		{
			int heapSize = length;
			buildHeap(t, comparator, length, order);
			for (int i = length - 1; i > 0; i--) {
				exchange(t[0], t[i]);
				heapSize--;
				heapify(t, comparator, 0, heapSize, order);
			}
		}
	}
}