#pragma once
#ifndef COUNTINGSORT_HPP
#define COUNTINGSORT_HPP

#ifndef COMMON_HPP
#include "common.hpp"
#endif

namespace cliqCity
{
	namespace algorithm
	{
        //template <class Type>
        //__interface LinearSort
        //{
        //public:
        //    template<class Functor, typename Key>
        //    void operator()(Type* const in, const int& length, Type* const out, Functor func);
        //};

        //template<class Type>
        //class CountSort : LinearSort<Type>
        //{
        //public:
        //    template <class Functor, typename Key>
        //    CountSort(Type* const in, const int& length, Type* const out, Functor func)
        //    {
        //        // Initialize counter and set to zero.
        //        uint32_t* counter = new uint32_t[max + 1];
        //        memset(counter, 0, sizeof(uint32_t) * (max + 1));

        //        // Set counter[j] to number of elements equal to j
        //        for (int j = 0; j < length; j++) {
        //            counter[uint32_Rank(t[j])]++;
        //        }

        //        if (order == SortOrderDescending) {
        //            // Set counter[i] to number of elements greater than or equal to j
        //            uint32_t* iter = &counter[max - 1];
        //            uint32_t* end = (counter - 1);
        //            while (iter != end) {
        //                *iter += *(iter + 1);
        //                iter--;
        //            }
        //        }
        //        else {
        //            // Set counter[i] to number of elements less than or equal to j
        //            uint32_t* iter = &counter[1];
        //            uint32_t* end = &counter[max + 1];
        //            while (iter != end) {
        //                *iter += *(iter - 1);
        //                iter++;
        //            }
        //        }

        //        // Index back into the output array
        //        for (int j = length - 1; j >= 0; j--) {
        //            uint32_t r = uint32_Rank(t[j]);
        //            output[counter[r] - 1] = t[j];
        //            counter[r]--;
        //        }

        //        delete[] counter;
        //    }

        //private:
        //    template<class Compare>
        //    inline int findMax(Type* const in, const Compare& compare, const int& length)
        //    {
        //        int max = 0;
        //        for (int i = 1; i < length; i++) {
        //            if (compare(t[i], t[max]) == 1) {
        //                max = i;
        //            }
        //        }

        //        return max;
        //    }

        //    template<class T, class C>
        //    inline int findMin(T* const t, const C& compare, const int& length)
        //    {
        //        int min = 0;
        //        for (int i = 1; i < length; i++) {
        //            if (compare(t[i], t[min]) == -1) {
        //                min = i;
        //            }
        //        }

        //        return min;
        //    }
        //};


		// Counting Sort: Uses auxiliary storage to count elements in array t. The counter maintains the number of elements in rank with each index. 
		// The rank of each element in t are assumed to be positive integers.
		// The counter is then used to index back into the output array. Runs in linear time if max <= length^2.
		template<class T, class R>
		void countingSort(T* const t, T* const output, const R& uint32_Rank, const uint32_t& max, const int& length, SortOrder order)
		{
			// Initialize counter and set to zero.
			uint32_t* counter = new uint32_t[max + 1];
			memset(counter, 0, sizeof(uint32_t) * (max + 1));

			// Set counter[j] to number of elements equal to j
			for (int j = 0; j < length; j++) {
				counter[uint32_Rank(t[j])]++;
			}

			if (order == SortOrderDescending) {
				// Set counter[i] to number of elements greater than or equal to j
				uint32_t* iter = &counter[max - 1];
				uint32_t* end = (counter - 1);
				while (iter != end) {
					*iter += *(iter + 1);
					iter--;
				}
			}
			else {
				// Set counter[i] to number of elements less than or equal to j
				uint32_t* iter = &counter[1];
				uint32_t* end = &counter[max + 1];
				while (iter != end) {
					*iter += *(iter - 1);
					iter++;
				}
			}

			// Index back into the output array
			for (int j = length - 1; j >= 0; j--) {
				uint32_t r = uint32_Rank(t[j]);
				output[counter[r] - 1] = t[j];
				counter[r]--;
			}

			delete[] counter;
		}

		// Counting Sort: Uses auxiliary storage to count elements in array t. The counter maintains the number of elements in rank with each index. 
		// The rank of each element in t are assumed to be signed integers.
		// The counter is then used to index back into the output array. Runs in linear time if range <= length^2.
		template<class T, class R>
		void countingSort(T* const t, T* const output, const R& signedRank, const int32_t& min, const int32_t& max, const int& length, SortOrder order)
		{
			// Initialize counter and set to zero.
			int32_t range = max - min;
			uint32_t* counter = new uint32_t[range + 1];
			memset(counter, 0, sizeof(uint32_t) * (range + 1));

			// Set counter[j] to number of elements equal to j
			for (int j = 0; j < length; j++) {
				counter[signedRank(t[j]) - min]++;
			}

			if (order == SortOrderDescending) {
				// Set counter[i] to number of elements greater than or equal to j
				uint32_t* iter = &counter[range - 1];
				uint32_t* end = (counter - 1);
				while (iter != end) {
					*iter += *(iter + 1);
					iter--;
				}
			}
			else {
				// Set counter[i] to number of elements less than or equal to i
				uint32_t* iter = &counter[1];
				uint32_t* end = &counter[range + 1];
				while (iter != end) {
					*iter += *(iter - 1);
					iter++;
				}
			}

			// Index back into the output array
			for (int j = length - 1; j >= 0; j--) {
				uint32_t r = signedRank(t[j]) - min;
				output[counter[r] - 1] = t[j];
				counter[r]--;
			}

			delete[] counter;
		}
	}
}

#endif