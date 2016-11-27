#include <Windows.h>
#include <ctime>
#include <climits>
#include <algorithm>

#include "InsertionSort.h"
#include "BubbleSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "RadixSort.h"
#include "../SortingSample/SortingSample/functors.h"

using namespace algorithm;

static const int ARRAY_LENGTH = 100;

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
    Quick<int32_t>(a2, ARRAY_LENGTH).Sort();
    QueryPerformanceCounter(&counterTime);
	elapsedTime = (float)(counterTime.QuadPart - counterStart.QuadPart) / frequency.QuadPart;
	printf("Quick Sort: Elements: %i Time: %f\n", ARRAY_LENGTH, elapsedTime);

	resetArrays(a1, a2, a3, ARRAY_LENGTH);

	QueryPerformanceCounter(&counterStart);
    Merge<int32_t>(a2, ARRAY_LENGTH).Sort();
    QueryPerformanceCounter(&counterTime);
	elapsedTime = (float)(counterTime.QuadPart - counterStart.QuadPart) / frequency.QuadPart;
	printf("Merge Sort: Elements: %i Time: %f\n", ARRAY_LENGTH, elapsedTime);

	resetArrays(a1, a2, a3, ARRAY_LENGTH);

	QueryPerformanceCounter(&counterStart);
    Radix<int32_t, int32_t>(a2, ARRAY_LENGTH).Sort([](int32_t i) {return i; });
	QueryPerformanceCounter(&counterTime);
	elapsedTime = (float)(counterTime.QuadPart - counterStart.QuadPart) / frequency.QuadPart;
	printf("Radix Sort: Elements: %i Time: %f\n", ARRAY_LENGTH, elapsedTime);

    resetArrays(a1, a2, a3, ARRAY_LENGTH);

    QueryPerformanceCounter(&counterStart);
    Insertion<int32_t>(a2, ARRAY_LENGTH).Sort();
    QueryPerformanceCounter(&counterTime);
    elapsedTime = (float)(counterTime.QuadPart - counterStart.QuadPart) / frequency.QuadPart;
    printf("Insertion Sort: Elements: %i Time: %f\n", ARRAY_LENGTH, elapsedTime);

    resetArrays(a1, a2, a3, ARRAY_LENGTH);

    QueryPerformanceCounter(&counterStart);
    Bubble<int32_t>(a2, ARRAY_LENGTH).Sort();
    QueryPerformanceCounter(&counterTime);
    elapsedTime = (float)(counterTime.QuadPart - counterStart.QuadPart) / frequency.QuadPart;
    printf("Bubble Sort: Elements: %i Time: %f\n", ARRAY_LENGTH, elapsedTime);

    resetArrays(a1, a2, a3, ARRAY_LENGTH);

    QueryPerformanceCounter(&counterStart);
    std::sort(a2, a2 + ARRAY_LENGTH);
    QueryPerformanceCounter(&counterTime);
    elapsedTime = (float)(counterTime.QuadPart - counterStart.QuadPart) / frequency.QuadPart;
    printf("STL Sort: Elements: %i Time: %f\n", ARRAY_LENGTH, elapsedTime);

	getchar();
}