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
		enum SortOrder
		{
			SortOrderDescending =	-1,
			SortOrderEqual		=	0,
			SortOrderAscending	=	1
		};

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

		// Merge: A subroutine used by Merge Sort. Uses auxiliary storage to merge to sorted arrays. Has linear complexity
		// Note: r is the exclusive last index of array t. It is NOT the length.
		template<class T, class C>
		void merge(T* const t, const C& comparator, const int& p, const int& q, const int& r, SortOrder order)
		{
			int n1 = q - p;
			int n2 = r - q;
			T* left		= new T[n1 + 1];
			T* right	= new T[n2 + 1];

			int i = 0;
			for (; i < n1; i++) {
				left[i] = t[p + i];
			}

			int j = 0;
			for (; j < n2; j++) {
				right[j] = t[q + j]; 
			}
		
			int sentinel = (order == SortOrderAscending) ? INT_MAX : INT_MIN;
			left[n1] = sentinel;
			right[n2] = sentinel;
			
			i = 0;
			j = 0;

			for (int k = p; k < r; k++) {
				int result = comparator(left[i], right[j]);
				if ((result <= 0 && order == SortOrderAscending) || (result >= 0 && order == SortOrderDescending)) {
					t[k] = left[i];
					i++;
				}
				else {
					t[k] = right[j];
					j++;
				}
			}
		}

		// Merge Sort: Recursively splits array into tow subarrays of n/2 length. Uses Merge subroutine. Has complexity O(nlgn)
		// Note: r is the exclusive last index of array t.
		template<class T, class C>
		void mergeSort(T* const t, const C& comparator, const int& p, const int& r, SortOrder order)
		{
			if (r - p > 1) {
				int q = (p + r) / 2;
				mergeSort(t, comparator, p, q, order);
				mergeSort(t, comparator, q, r, order);
				merge(t, comparator, p, q, r, order);
			}
		}

		// Partition: A subroutine used by Quick Sort. Partitions array t into subarrays of values less than and greater than the partition element. Always uses last element as partition.
		// TO DO: Optimize for non distinct elements by returning a partition range. Median of 3 partition.
		template<class T, class C>
		int partition(T* const t, const C& comparator, const int& p, const int& r, SortOrder order)
		{
			int last = r - 1;
			int i = p - 1;
			for (int j = p; j < last; j++) {
				int result = comparator(t[j], t[last]);
				if ((result <= 0 && order == SortOrderAscending) || (result >= 0 && order == SortOrderDescending)) {
					exchange(t[++i], t[j]);
				}
			}
			exchange(t[++i], t[last]);
			return i;
		}

		// Quick Sort: Recursively sorts using Partition subroutine. Runs in worst case quadratic time, and nlgn expected time. Asymptotic performance can be improved via randomization
		// TO DO: Optimize using tail recursive sort.
		template<class T, class C>
		void quickSort(T* const t, const C& comparator, const int& p, const int& r, SortOrder order)
		{
			if (r - p > 1) {
				int q = partition(t, comparator, p, r, order);
				quickSort(t, comparator, p, q, order);
				quickSort(t, comparator, q + 1, r, order);
			}
		}

		// Randomized Quick Sort: Quick Sort with a randomly selected partition element.
		template<class T, class C>
		void randomizedQuickSort(T* const t, const C& comparator, const int& p, const int& r, SortOrder order)
		{
			if (r - p > 1) {
				exchange(t[r - 1], t[rand() % (r - 1)]);
				int q = partition(t, comparator, p, r, order);
				quickSort(t, comparator, p, q, order);
				quickSort(t, comparator, q + 1, r, order);
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
			int left	= (index << 1) + 1;
			int right	= (index << 1) + 2;

			int largest;
			if (left < heapSize && comparator(t[left], t[index]) == order) {
				largest = left;
			}
			else {
				largest = index;
			}

			if (right < heapSize && comparator(t[right], t[largest]) == order) {
				largest = right;
			}

			if (largest != index) {
				exchange(t[index], t[largest]);
				heapify(t, comparator, largest, heapSize, order);
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