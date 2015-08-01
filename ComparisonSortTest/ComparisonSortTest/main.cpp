#include "comparison_sorts.hpp"
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <iostream>

using namespace cliqCity::algorithm;

struct Comparator
{
	int operator()(const int& first, const int& second) const
	{
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
} comparator;

int compareInt(const void* a, const void* b)
{
	int first = *(int*)a;
	int second = *(int*)b;
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
		int arrayLength;
		printf("Enter number of elements: ");
		std::cin >> arrayLength;

		srand((unsigned int)time(NULL));
		printf("Array Length: %i \n", arrayLength);
		printf("Unsorted Int: ");
		int* t = new int[arrayLength];
		for (int i = 0; i < arrayLength; i++) {
			t[i] = rand() % arrayLength;
			printf("%i ", t[i]);
		}
		printf("\n");

		int sortAlgorithm;
		printf("Choose Sort: \n 0: Insertion Sort\n 1: Bubble Sort\n 2: Merge Sort\n 3: Quick Sort\n 4: Randomized Quick Sort\n 5: Heap Sort\n");
		std::cin >> sortAlgorithm;

		int sortOrder;
		printf("Choose Sort Order: \n 0: Descending\n 1: Ascending\n");
		std::cin >> sortOrder;

		SortOrder order;
		switch (sortOrder)
		{
		case 0:
			order = SortOrderDescending;
			break;
		case 1:
			order = SortOrderAscending;
			break;
		default:
			order = SortOrderDescending;
			break;
		}

		switch (sortAlgorithm)
		{
		case 0:
			insertionSort(t, comparator, arrayLength, order);
			break;
		case 1:
			bubbleSort(t, comparator, arrayLength, order);
			break;
		case 2:
			mergeSort(t, comparator, 0, arrayLength, order);
			break;
		case 3:
			quickSort(t, comparator, 0, arrayLength, order);
			break;
		case 4:
			randomizedQuickSort(t, comparator, 0, arrayLength, order);
			break;
		case 5:
			heapSort(t, comparator, arrayLength, order);
		default:
			break;
		}

		bool correct = true;
		for (int i = 1; i < arrayLength; i++) {
			if (order == SortOrderAscending) {
				correct = (compareInt(&t[i - 1], &t[i]) <= 0);
			}
			else {
				correct = (compareInt(&t[i - 1], &t[i]) >= 0);
			}
			if (!correct) {
				printf("ERROR: Sort output is incorrect \n");
				break;
			}
		}

		printf("Sorted Int: ");
		for (int i = 0; i < arrayLength; i++) {
			printf("%i ", t[i]);
		}

		printf("\n");

		char input;
		do
		{
			printf("Continue? (Y/N)");
			std::cin >> input;
			exit = (input == 'n' || input == 'N');
		} while (input != 'y' && input != 'Y' && input != 'N' && input != 'n');
	}
}