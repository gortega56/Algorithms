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

namespace cliqCity
{
	namespace algorithm
	{
		// Counting Sort: Uses auxiliary storage to count elements in array t. The counter maintains the number of elements in rank with each index. 
		// The counter is then used to index back into the output array. Runs in linear time if max <= length^2.
		template<class T, class R>
		void countingSort(T* const t, T* const output, const R& rank, const int& max, const int& length, SortOrder order)
		{
			// Initialize counter and set to zero.
			unsigned int* counter = new unsigned int[max + 1];
			memset(counter, 0, sizeof(unsigned int) * (max + 1));

			// Set counter[j] to number of elements equal to j
			for (int j = 0; j < length; j++) {
				counter[rank(t[j])]++;
			}

			if (order == SortOrderDescending) {
				// Set counter[i] to number of elements greater than or equal to j
				for (int i = max - 1; i >= 0; i--) {
					counter[i] += counter[i + 1];
				}
			}
			else {
				// Set counter[i] to number of elements less than or equal to j
				for (int i = 1; i <= max; i++) {
					counter[i] += counter[i - 1];
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

		typedef unsigned __int32	UInt32;
		typedef unsigned char		UByte;
		
		template<class T, class K>
		void radixSort(T* const t, T* const output, const K& uint32Key, const int& length, SortOrder order)
		{
			// Range * Number of Counters * Bytes Per Location
			UInt32 counter[256 * 4];
			memset(counter, 0, 256 * 4 * sizeof(UInt32));

			UInt32* c0 = (UInt32*)&counter[0];		// LSB
			UInt32* c1 = (UInt32*)&counter[256];
			UInt32* c2 = (UInt32*)&counter[512];
			UInt32* c3 = (UInt32*)&counter[768];	// MSB

			// Counting Pass
			UByte* byte = NULL;
			for (int i = 0; i < length; i++) {
				byte = (UByte*)uint32Key(t, i);

				c0[*byte]++;
				c1[*(byte + 1)]++;
				c2[*(byte + 2)]++;
				c3[*(byte + 3)]++;

				std::cout << *uint32Key(t, i) << " : " << std::bitset<8>(*byte) << "     " << std::bitset<8>(*(byte + 1)) << "     " << std::bitset<8>(*(byte + 2)) << "     " << std::bitset<8>(*(byte + 3)) << std::endl;
			}

			// Offset Pass
			for (int i = 1; i < 256; i++) {
				c0[i] += c0[i - 1];
				c1[i] += c1[i - 1];
				c2[i] += c2[i - 1];
				c3[i] += c3[i - 1];
			}

			// Radix Passes
			// Figure out the swap!!! Almost there!
			T* swap = new T[length];
			size_t size = sizeof(T) * length;
			memcpy_s(swap, size, t, size);

			UInt32* c = NULL;
			for (int pass = 0; pass < 4; pass++) {
				c = reinterpret_cast<UInt32*>(&counter[(pass << 8)]);
				printf("Pass %i\n", pass + 1);
				UInt32 *k = NULL;
				for (int tIndex = length - 1; tIndex >= 0; tIndex--) {
					k = uint32Key(swap, tIndex);
					UByte* radix = ((UByte*)k) + pass;
					output[c[*(radix)] - 1] = swap[tIndex];
					printf("%i : %u\n", c[*(radix)] - 1, output[c[*(radix)] - 1]);
					c[*(radix)]--;
				}

				memcpy_s(swap, size, output, size);

				printf("\n");
			}

			delete[] swap;
		}
	}
}