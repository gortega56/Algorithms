#include "comparison_sorts.hpp"
#include "linear_sorts.hpp"
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include "functors.h"
#include "counting_sort.h"
#include <random>

using namespace cliqCity::algorithm;

class SortableObject
{
public:
	int key;

	SortableObject(int key) : key(key) {};
	SortableObject() : key(0) {};
};

int compareObject(const void* a, const void* b)
{
	int first = (*(SortableObject*)a).key;
	int second = (*(SortableObject*)b).key;
	if (first < second) {
		return -1;
	}
	else if (first == second) {
		return 0;
	}
	else {
		return 1;
	}
}

int main(int argc, int* argv[])
{
	std::default_random_engine gen;
	std::uniform_int_distribution<int> dist(-1, 1);

	bool exit = false;
	while (!exit) {
		bool useFloats = false;
		printf("Floating point?\n");
		std::cin >> useFloats;

		bool _signed = false;
		if (useFloats)
		{
			_signed = true;
		}
		else
		{
			printf("Signed?\n");
			std::cin >> _signed;
		}

		int arrayLength;
		printf("Enter number of elements: ");
		std::cin >> arrayLength;

		srand((unsigned int)time(NULL));
		printf("Array Length: %i \n", arrayLength);

		void* t = NULL;
			
		printf("Unsorted: ");
		if (useFloats) {
			t = new float[arrayLength];
			for (int i = 0; i < arrayLength; i++) {
				((float*)t)[i] = /*-(int)(i + 1);*/ (i % 2 == 0) ? (float)i : -(float)i;// *0.75f;// ((float)rand() / (float)(RAND_MAX)) * -5.0f;
				printf("%f ", ((float*)t)[i]);
			}
			printf("\n");

	/*		for (int i = 0; i < arrayLength; i++) {
				printf("%u ", cliqCity::flip(((uint32_t*)t)[i]));
			}*/
			printf("\n");
		}
		else {
			if (_signed)
			{
				t = new int[arrayLength];
				for (int i = 0; i < arrayLength; i++) {
					((int*)t)[i] = rand() % RAND_MAX * dist(gen);
					printf("%d ", ((int*)t)[i]);
				}
				printf("\n");
			}
			else
			{
				t = new unsigned int[arrayLength];
				for (int i = 0; i < arrayLength; i++) {
					((unsigned int*)t)[i] = rand() % RAND_MAX;
					printf("%u ", ((unsigned int*)t)[i]);
				}
				printf("\n");
			}
			
		}

		int sortAlgorithm;
		printf("Choose Sort: \n 0: Insertion Sort\n 1: Bubble Sort\n 2: Merge Sort\n 3: Quick Sort\n 4: Randomized Quick Sort\n 5: Heap Sort\n 6: Counting Sort\n 7: Radix Sort\n");
		std::cin >> sortAlgorithm;

		int sortOrder;
		printf("Choose Sort Order: \n 0: Descending\n 1: Ascending\n");
		std::cin >> sortOrder;

		cliqCity::SortOrder order;
		switch (sortOrder)
		{
		case 0:
			order = cliqCity::SortOrderDescending;
			break;
		case 1:
			order = cliqCity::SortOrderAscending;
			break;
		default:
			order = cliqCity::SortOrderDescending;
			break;
		}

		switch (sortAlgorithm)
		{
		case 0:
			(_signed) ? insertionSort((float*)t, comparator, arrayLength, order) : insertionSort((unsigned int*)t, unsignedComparator, arrayLength, order);
			break;
		case 1:
			(_signed) ? bubbleSort((float*)t, comparator, arrayLength, order) : bubbleSort((unsigned int*)t, unsignedComparator, arrayLength, order);
			break;
		case 2:
			(_signed) ? mergeSort((float*)t, comparator, 0, arrayLength, order) : mergeSort((unsigned int*)t, unsignedComparator, 0, arrayLength, order);
			break;
		case 3:
			(_signed) ? quickSort((float*)t, comparator, 0, arrayLength, order) : quickSort((unsigned int*)t, unsignedComparator, 0, arrayLength, order);
			break;
		case 4:
			(_signed) ? randomizedQuickSort((float*)t, comparator, 0, arrayLength, order) : randomizedQuickSort((unsigned int*)t, unsignedComparator, 0, arrayLength, order);
			break;
		case 5:
			(_signed) ? heapSort((float*)t, comparator, arrayLength, order) : heapSort((unsigned int*)t, unsignedComparator, arrayLength, order);
			break;
		case 6:
		{
			if (_signed) {
				float* s = new float[arrayLength];
				int min, max;
				cliqCity::minMaxIndices((float*)t, &min, &max, comparator, arrayLength);
				countingSort((float*)t, s, rank, rank(((float*)t)[min]), rank(((float*)t)[max]), arrayLength, order);
				delete[] t;
				t = s;
			}
			else {
				unsigned int* s = new unsigned int[arrayLength];
				int k = cliqCity::maxIndex((unsigned int*)t, unsignedComparator, arrayLength);
				countingSort((unsigned int*)t, s, unsignedRank, ((unsigned int*)t)[k], arrayLength, order);
				delete[] t;
				t = s;
			}
			break;
		}
		case 7:
		{

			void* s;
			if (useFloats) {
				s = new float[arrayLength];
				RadixSort<float, float>()((float*)t, arrayLength, (float*)s, [](f32 n) { return n; });
			}
			else {
				if (_signed)
				{
					s = new int[arrayLength];
					//RadixSort<unsigned int, unsigned int>()((unsigned int*)t, (unsigned int*)s, uKey, arrayLength);
					RadixSort<i32, i32>()((i32*)t, arrayLength, (i32*)s, [](i32 n) { return n; });
				}
				else
				{
					s = new unsigned int[arrayLength];
					//RadixSort<unsigned int, unsigned int>()((unsigned int*)t, (unsigned int*)s, uKey, arrayLength);
					RadixSort<u32, u32>()((u32*)t, arrayLength, (u32*)s, [](u32 n) { return n; });
				}
			}

			delete[] t;
			t = s;
			break;
		}
		default:
			break;
		}

		bool correct = true;
		for (int i = 1; i < arrayLength; i++) {
			if (order == cliqCity::SortOrderAscending) {
				correct = (useFloats) ? (comparator(((float*)t)[i - 1], ((float*)t)[i]) <= 0) : (_signed) ? (icomp(((int*)t)[i - 1], ((int*)t)[i]) <= 0) : (ucomp(((unsigned int*)t)[i - 1], ((unsigned int*)t)[i]) <= 0);
			}
			else {
				correct = (useFloats) ? (comparator(((float*)t)[i - 1], ((float*)t)[i]) >= 0) : (_signed) ? (icomp(((int*)t)[i - 1], ((int*)t)[i]) <= 0) : (ucomp(((unsigned int*)t)[i - 1], ((unsigned int*)t)[i]) >= 0);
			}
		
			if (!correct) {
				printf("ERROR: Sort output is incorrect \n");
				break;
			}
		}

		printf("Sorted: ");
		for (int i = 0; i < arrayLength; i++) {
			(useFloats) ? printf("%f ", ((float*)t)[i]) : (_signed) ? printf("%d ", ((int*)t)[i]) : printf("%u ", ((unsigned int*)t)[i]);
		}

		printf("\n");

		char input;
		do
		{
			printf("Continue? (Y/N)");
			std::cin >> input;
			exit = (input == 'n' || input == 'N');
		} while (input != 'y' && input != 'Y' && input != 'N' && input != 'n');

		delete[] t;
	}
}