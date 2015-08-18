#include "comparison_sorts.hpp"
#include "linear_sorts.hpp"
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include "functors.h"

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
	bool exit = false;
	while (!exit) {
		bool _signed = false;
		printf("Signed?\n");
		std::cin >> _signed;

		int arrayLength;
		printf("Enter number of elements: ");
		std::cin >> arrayLength;

		srand((unsigned int)time(NULL));
		printf("Array Length: %i \n", arrayLength);

		void* t = NULL;
		if (_signed) {
			printf("Unsorted Int: ");
			t = new int[arrayLength];
			for (int i = 0; i < arrayLength; i++) {
				((int*)t)[i] = rand() % 100;
				printf("%i ", ((int*)t)[i]);
			}
			printf("\n");
		}
		else {
			printf("Unsorted Int: ");
			t = new unsigned int[arrayLength];
			for (int i = 0; i < arrayLength; i++) {
				((unsigned int*)t)[i] = rand() % 100;
				printf("%u ", ((unsigned int*)t)[i]);
			}
			printf("\n");
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
			(_signed) ? insertionSort((int*)t, comparator, arrayLength, order) : insertionSort((unsigned int*)t, unsignedComparator, arrayLength, order);
			break;
		case 1:
			(_signed) ? bubbleSort((int*)t, comparator, arrayLength, order) : bubbleSort((unsigned int*)t, unsignedComparator, arrayLength, order);
			break;
		case 2:
			(_signed) ? mergeSort((int*)t, comparator, 0, arrayLength, order) : mergeSort((unsigned int*)t, unsignedComparator, 0, arrayLength, order);
			break;
		case 3:
			(_signed) ? quickSort((int*)t, comparator, 0, arrayLength, order) : quickSort((unsigned int*)t, unsignedComparator, 0, arrayLength, order);
			break;
		case 4:
			(_signed) ? randomizedQuickSort((int*)t, comparator, 0, arrayLength, order) : randomizedQuickSort((unsigned int*)t, unsignedComparator, 0, arrayLength, order);
			break;
		case 5:
			(_signed) ? heapSort((int*)t, comparator, arrayLength, order) : heapSort((unsigned int*)t, unsignedComparator, arrayLength, order);
			break;
		case 6:
		{
			if (_signed) {
				int* s = new int[arrayLength];
				int min, max;
				cliqCity::minMaxIndices((int*)t, &min, &max, comparator, arrayLength);
				countingSort((int*)t, s, rank, ((int*)t)[min], ((int*)t)[max], arrayLength, order);
				delete[] t;
				t = s;
			}
			else {
				unsigned int* s = new unsigned int[arrayLength];
				int k = cliqCity::maxIndex((unsigned int*)t, comparator, arrayLength);
				countingSort((unsigned int*)t, s, unsignedRank, ((unsigned int*)t)[k], arrayLength, order);
				delete[] t;
				t = s;
			}
			break;
		}
		case 7:
		{
			unsigned int* s = new unsigned int[arrayLength];
			uint32_RadixSort((unsigned int*)t, s, unsignedKey, arrayLength, order);
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
				correct = (_signed) ? (comparator(((int*)t)[i - 1], ((int*)t)[i]) <= 0) : (comparator(((unsigned int*)t)[i - 1], ((unsigned int*)t)[i]) <= 0);
			}
			else {
				correct = (_signed) ? (comparator(((int*)t)[i - 1], ((int*)t)[i]) >= 0) : (comparator(((unsigned int*)t)[i - 1], ((unsigned int*)t)[i]) >= 0);
			}
		
			if (!correct) {
				printf("ERROR: Sort output is incorrect \n");
				break;
			}
		}

		printf("Sorted Int: ");
		for (int i = 0; i < arrayLength; i++) {
			(_signed) ? printf("%i ", ((int*)t)[i]) : printf("%u ", ((unsigned int*)t)[i]);
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