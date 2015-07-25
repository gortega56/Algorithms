// InsertionSort.hpp
//
//
// Gabriel Ortega

#include <cmath>
#include <climits>
#include <stdio.h>

namespace cliqCity
{
	namespace algorithm
	{	
		// Insertion Sort: Sort array of type T in place. Insertion sort is stable and has quadratic complexity.
		template<class T> 
		void insertionSort(T* t, int length, int(*compare)(const void*, const void*))
		{
			for (int j = 1; j < length; j++) {
				T temp = t[j];
				int i = j - 1;
				while (i >= 0 && compare(&t[i], &temp) == 1) {
					t[i + 1] = t[i];
					i--;
				}
				t[i + 1] = temp;
			}
		}

		template<class T>
		inline void exchange(T& a, T& b)
		{
			T t = a;
			a = b;
			b = t;
		}

		// Bubble Sort: Stable algorithm that sorts elements in place. Quadratic complexity.
		template<class T>
		void bubbleSort(T* t, int length, int(*compare)(const void*, const void*))
		{
			for (int i = 0; i < length; i++) {
				for (int j = length - 1; j > 0; j--) {
					if (compare(&t[j], &t[j - 1]) == -1) {
						exchange(t[j], t[j - 1]);
					}
				}
			}
		}

		// Merge: A subroutine used by Merge Sort. Uses auxiliary storage to merge to sorted arrays. Has linear complexity
		// Note: r is the exclusive last index of array t. It is NOT the length.
		template<class T>
		void merge(T* t, int p, int q, int r, int(*compare)(const void*, const void*))
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
		
			left[n1]	= INT_MAX;
			right[n2]	= INT_MAX;

			i = 0;
			j = 0;

			for (int k = p; k < r; k++) {
				if (compare(&left[i], &right[j]) <= 0) {
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
		template<class T>
		void mergeSort(T* t, int p, int r, int(*compare)(const void*, const void*))
		{
			if (r - p > 1) {
				int q = (p + r) / 2;
				mergeSort(t, p, q, compare);
				mergeSort(t, q, r, compare);
				merge(t, p, q, r, compare);
			}
		}

		// Partition: A subroutine used by Quick Sort. Partitions array t into subarrays of values less than and greater than the partition element. Always uses last element as partition.
		// TO DO: Optimize for non distinct elements by returning a partition range. Median of 3 partition.
		template<class T>
		int partition(T* t, int p, int r, int(*compare)(const void*, const void*))
		{
			int last = r - 1;
			int i = p - 1;
			for (int j = p; j < last; j++) {
				if (compare(&t[j], &t[last]) <= 0) {
					exchange(t[++i], t[j]);
				}
			}
			exchange(t[++i], t[last]);
			return i;
		}

		// Quick Sort: Recursively sorts using Partition subroutine. Runs in worst case quadratic time, and nlgn expected time. Asymptotic performance can be improved via randomization
		// TO DO: Optimize using tail recursive sort.
		template<class T>
		void quickSort(T* t, int p, int r, int(*compare)(const void*, const void*))
		{
			if (r - p > 1) {
				int q = partition(t, p, r, compare);
				quickSort(t, p, q, compare);
				quickSort(t, q + 1, r, compare);
			}
		}

		// Randomized Quick Sort: Quick Sort with a randomly selected partition element.
		template<class T>
		void randomizedQuickSort(T *t, int p, int r, int(*compare)(const void*, const void*))
		{
			if (r - p > 1) {
				exchange(t[r - 1], t[rand() % (r - 1)]);
				int q = partition(t, p, r, compare);
				quickSort(t, p, q, compare);
				quickSort(t, q + 1, r, compare);
			}
		}
	}
}