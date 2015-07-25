#include "ComparisonSort.hpp"
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <iostream>

using namespace cliqCity::algorithm;

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

		srand(time(NULL));
		printf("Array Length: %i \n", arrayLength);
		printf("Unsorted Int: ");
		int* t = new int[arrayLength];
		for (int i = 0; i < arrayLength; i++) {
			t[i] = rand() % arrayLength;
			printf("%i ", t[i]);
		}
		printf("\n");

		int sortType;
		printf("Choose Sort: \n 0: Insertion Sort\n 1: Bubble Sort\n 2: Merge Sort\n 3: Quick Sort\n 4: Randomized Quick Sort\n");
		std::cin >> sortType;

		switch (sortType)
		{
		case 0:
			insertionSort(t, arrayLength, compareInt);
			break;
		case 1:
			bubbleSort(t, arrayLength, compareInt);
			break;
		case 2:
			mergeSort(t, 0, arrayLength, compareInt);
			break;
		case 3:
			quickSort(t, 0, arrayLength, compareInt);
		case 4:
			randomizedQuickSort(t, 0, arrayLength, compareInt);
		default:
			break;
		}

		bool correct = true;
		for (int i = 1; i < arrayLength; i++) {
			correct = (compareInt(&t[i - 1], &t[i]) <= 0);
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