// linear_sorts.hpp
//
// Linear Sort Algorithms
//
// Gabriel Ortega

#pragma once 
#include "common.hpp"
#include <stdio.h>

namespace cliqCity
{
	namespace algorithm
	{
		// Counting Sort: Uses external storage to count elements in array t. The counter maintains the number of elements in rank with each index. 
		// The counter is then used to index back into the output array. Runs in linear time.
		template<class T, class R>
		void countingSort(T* const t, T* const output, const R& rank, const int& max, const int& length, SortOrder order)
		{
			T* counter = new T[max + 1];

			// Set to zero
			for (int i = 0; i <= max; i++) {
				counter[i] = 0;
			}

			// Set counter[j] to number of elements equal to j
			for (int j = 0; j < length; j++) {
				counter[rank(t[j])]++;
			}

			switch (order) 
			{
				case SortOrderDescending:
				{
					// Set counter[i] to number of elements greater than or equal to j
					for (int i = max - 1; i >= 0; i--) {
						counter[i] += counter[i + 1];
					}
					break;
				}
				case SortOrderAscending:
				default:
				{
					// Set counter[i] to number of elements less than or equal to j
					for (int i = 1; i <= max; i++) {
						counter[i] += counter[i - 1];
					}
					break;
				}
			}

			// Index back into the output array
			for (int j = length - 1; j >= 0; j--) {
				int r = rank(t[j]);
				output[counter[r] - 1] = t[j];
				counter[r]--;
			}

			delete[] counter;
		}
	}
}

