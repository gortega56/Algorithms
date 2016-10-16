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

		// Radix Sort (32 bit unsigned integers): Sorts t by sorting each byte of an unsigned integer key. 
		// The keys are assumed to be of type uint32_t which requires 4 passes (1 per byte). Runs in O(n * 4).
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

	template<class T, class K>
	void int32_RadixSort(T* const t, T* const output, const K& key, const int& length, SortOrder order)
	{
		// Range * Number of Counters * Bytes Per Location
		uint32_t counter[256 * 4];
		memset(counter, 0, 256 * 4 * sizeof(uint32_t));

		uint32_t negativeLength = 0;
		uint32_t* c0 = &counter[0];		// LSB
		uint32_t* c1 = &counter[256];
		uint32_t* c2 = &counter[512];
		uint32_t* c3 = &counter[768];	// MSB
		uint8_t* byte = NULL;

		// Counting Pass
		for (int i = 0; i < length; i++) {
			byte = (uint8_t*)key(t, i);

			// Split key into individual bytes and count in each list
			c0[*byte]++;
			c1[*(byte + 1)]++;
			c2[*(byte + 2)]++;
			c3[*(byte + 3)]++;


			if (*(byte + 3) > 127) {
				negativeLength++;
			}
		}

		// Offset Pass
		if (order == SortOrderDescending) {
			// Set positive counter[i] to number of elements greater than or equal to i
			for (int i = 254; i > 0; i--) {
				c0[i] += c0[i + 1];
				c1[i] += c1[i + 1];
				c2[i] += c2[i + 1];
			}

			// The MSB counter handles positive (<127) and negative (>127) values

			for (int i = 126; i >= 0; i--) {
				c3[i] += c3[i + 1];
				printf("%i    :    %u\n", i, c3[i]);
			}

			// Set negative counter[i] to number of elements greater than or equal to i
			c3[128] += c3[0];
			for (int i = 129; i < 256; i++) {
				c3[i] += c3[i - 1];
				printf("%i    :    %u\n", i, c3[i]);
			}
		}
		else {
			// Set positive counter[i] to number of elements less than or equal to i
			for (int i = 1; i < 256; i++) {
				c0[i] += c0[i - 1];
				c1[i] += c1[i - 1];
				c2[i] += c2[i - 1];
			}

			// The MSB counter handles positive (<127) and negative (>127) values

			// Add negativeLenth to the number of elements less than or equal to 0
			c3[0] += negativeLength;
			for (int i = 1; i < 128; i++) {
				c3[i] += c3[i - 1];
			//	printf("%i    :    %u\n", i, c3[i]);
			}

			// Set negative counter[i] to number of elements less than or equal to i
			// Iterate in reverse because negative values are ascending
			for (int i = 254; i > 127; i--) {
				c3[i] += c3[i + 1];
				printf("%i    :    %u\n", i, c3[i]);
			}
		}

		size_t size = sizeof(T) * length;
		T* swap = new T[length];
		memcpy_s(swap, size, t, size);
		uint32_t* c = NULL;

		// Radix Passes	
		for (int pass = 0; pass < 4; pass++) {
			printf("Pass: %i\n", pass);
			// Get the counter for the current pass
			c = &counter[(pass << 8)];

			// Index back into the output array using the counter and key
			// NOTE: THE PROBLEM HERE IS THAT EVEN THOUGH THE OFFSET IS CALCULATED CORRECTLY WE APPLY THEM INCORRECTLY. FOR EXAMPLE THE MSB FOR VALUES -1 > N >= -5 EVALUATES TO 192.
			// THE COUNTER WILL HAVE A VALUE OF 4 AT INDEX 192. BECAUSE WE REVERSE ITERATE THE SWAP ARRAY AND THE PREVIOUS 3 RADICES WERE SORTED AS POSITIVE NUMBERS THE FIRST NEGATIVE VALUE 
			// ENCOUNTERED IS -5 WHICH GETS PLACED AT OUTPUT[COUNTER[192] - 1]] = OUTPUT[4 - 1] = OUTPUT[3]. THEN COUNTER[192] IS DECREMENTED. WHAT WE WANT TO HAPPEN FOR NEGATIVE VALUE OFFSET
			// TO CONTAIN THE INFORMATION TO INVERSE THE COUNTING SORT.

			// 4 OUTPUT[COUNTER[191] - 1]] = OUTPUT[5 - 1] = OUTPUT[4] -1
			// 3 OUTPUT[COUNTER[192] - 1]] = OUTPUT[4 - 1] = OUTPUT[3] -5
			// 2 OUTPUT[COUNTER[192] - 1]] = OUTPUT[3 - 1] = OUTPUT[2] -4
			// 1 OUTPUT[COUNTER[192] - 1]] = OUTPUT[2 - 1] = OUTPUT[1] -3
			// 0 OUTPUT[COUNTER[192] - 1]] = OUTPUT[1 - 1] = OUTPUT[0] -2

			// 4 OUTPUT[COUNTER[191] - 1]] = OUTPUT[5] = OUTPUT[4] -1
			// 3 OUTPUT[COUNTER[192] - 1]] = OUTPUT[4] = OUTPUT[0] -5
			// 2 OUTPUT[COUNTER[192] - 1]] = OUTPUT[3] = OUTPUT[1] -4
			// 1 OUTPUT[COUNTER[192] - 1]] = OUTPUT[2] = OUTPUT[2] -3
			// 0 OUTPUT[COUNTER[192] - 1]] = OUTPUT[1] = OUTPUT[3] -2

			for (int i = length - 1; i >= 0; i--) {
					byte = ((uint8_t*)key(swap, i)) + pass;
					output[c[*(byte)] - 1] = swap[i];
					std::cout << c[*(byte)] - 1 << " : " << swap[i] << " : " << static_cast<unsigned>(*(byte)) << " : " << std::bitset<8>(*(byte)) << std::endl;
					c[*(byte)]--;
			}

			// Copy output back to swap for next pass NOTE: EXTRA COPY AT PASS 3
			memcpy_s(swap, size, output, size);
		}

		delete[] swap;
	}
}