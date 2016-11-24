#include <Windows.h>
#include <ctime>
#include <climits>

#include "comparison_sorts.hpp"
#include "RadixSort.hpp"
#include "../SortingSample/SortingSample/functors.h"

using namespace cliqCity::algorithm;

static const int ARRAY_LENGTH = 10000;

void resetArrays(uint32_t* a1, int32_t* a2, float* a3, const int& length)
{
	for (int i = 0; i < ARRAY_LENGTH; i++) {
		a1[i] = rand() % RAND_MAX;
		a2[i] = (rand() % RAND_MAX) - (RAND_MAX);
		a3[i] = ((float)rand() / (float)(RAND_MAX)) * 5.0f;
	}
}

int main(int argc, int* argv[])
{
	srand((uint32_t)time(NULL));

	uint32_t a1[ARRAY_LENGTH];
	int32_t a2[ARRAY_LENGTH];
	float a3[ARRAY_LENGTH];

	resetArrays(a1, a2, a3, ARRAY_LENGTH);

	LARGE_INTEGER frequency;
	LARGE_INTEGER counterStart;
	LARGE_INTEGER counterTime;
	float elapsedTime;

	QueryPerformanceFrequency(&frequency);

	QueryPerformanceCounter(&counterStart);
	randomizedQuickSort(a1, unsignedComparator, 0, ARRAY_LENGTH, cliqCity::SortOrderAscending);
	QueryPerformanceCounter(&counterTime);
	elapsedTime = (float)(counterTime.QuadPart - counterStart.QuadPart) / frequency.QuadPart;
	printf("Randomized Quick Sort: Elements: %i Time: %f\n", ARRAY_LENGTH, elapsedTime);

	resetArrays(a1, a2, a3, ARRAY_LENGTH);

	QueryPerformanceCounter(&counterStart);
	mergeSort(a1, unsignedComparator, 0, ARRAY_LENGTH, cliqCity::SortOrderAscending);
	QueryPerformanceCounter(&counterTime);
	elapsedTime = (float)(counterTime.QuadPart - counterStart.QuadPart) / frequency.QuadPart;
	printf("Merge Sort: Elements: %i Time: %f\n", ARRAY_LENGTH, elapsedTime);

	resetArrays(a1, a2, a3, ARRAY_LENGTH);

	QueryPerformanceCounter(&counterStart);
	insertionSort(a1, unsignedComparator, ARRAY_LENGTH, cliqCity::SortOrderAscending);
	QueryPerformanceCounter(&counterTime);
	elapsedTime = (float)(counterTime.QuadPart - counterStart.QuadPart) / frequency.QuadPart;
	printf("Insertion Sort: Elements: %i Time: %f\n", ARRAY_LENGTH, elapsedTime);

	getchar();
}