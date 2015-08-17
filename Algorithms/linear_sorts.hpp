// linear_sorts.hpp
//
// Linear Sort Algorithms
//
// Gabriel Ortega

#pragma once 
#include "common.hpp"
#include <stdio.h>

#include <iostream>
#include <bitset>
#include <climits>
#include <stdint.h>

namespace cliqCity
{
	namespace algorithm
	{
		// Counting Sort: Uses auxiliary storage to count elements in array t. The counter maintains the number of elements in rank with each index. 
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
		
		template<class T, class K>
		void uint32_RadixSort(T* const t, T* const output, const K& uint32_Key, const int& length, SortOrder order)
		{
			// Range * Number of Counters * Bytes Per Location
			uint32_t counter[256 * 4];
			memset(counter, 0, 256 * 4 * sizeof(uint32_t));

			uint32_t* c0 = &counter[0];		// LSB
			uint32_t* c1 = &counter[256];
			uint32_t* c2 = &counter[512];
			uint32_t* c3 = &counter[768];	// MSB

			// Counting Pass
			uint8_t* byte = NULL;
			for (int i = 0; i < length; i++) {
				byte = (uint8_t*)uint32_Key(t, i);

				// Split key into individual bytes and count in each list
				c0[*byte]++;
				c1[*(byte + 1)]++;
				c2[*(byte + 2)]++;
				c3[*(byte + 3)]++;
			}

			// Offset Pass
			if (order == SortOrderDescending) {
				// Set counter[i] to number of elements greater than or equal to I
				for (int i = 254; i >= 0; i--) {
					c0[i] += c0[i + 1];
					c1[i] += c1[i + 1];
					c2[i] += c2[i + 1];
					c3[i] += c3[i + 1];
				}
			}
			else {
				// Set counter[i] to number of elements less than or equal to i
				for (int i = 1; i < 256; i++) {
					c0[i] += c0[i - 1];
					c1[i] += c1[i - 1];
					c2[i] += c2[i - 1];
					c3[i] += c3[i - 1];
				}
			}

			size_t size = sizeof(T) * length;
			T* swap = new T[length];
			memcpy_s(swap, size, t, size);

			// Radix Passes
			uint32_t* c = NULL;
			for (int pass = 0; pass < 4; pass++) {

				c = &counter[(pass << 8)];
				for (int tIndex = length - 1; tIndex >= 0; tIndex--) {
					uint8_t* radix = ((uint8_t*)uint32_Key(swap, tIndex)) + pass;
					output[c[*(radix)] - 1] = swap[tIndex];
					c[*(radix)]--;
				}

				// Copy output back to swap for next pass
				memcpy_s(swap, size, output, size);
			}

			delete[] swap;
		}
	}
}