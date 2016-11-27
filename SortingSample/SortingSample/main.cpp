#include "MergeSort.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "RadixSort.h"
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include "functors.h"
#include "CountingSort.h"
#include <random>
#include <string>

using namespace algorithm;
namespace algorithm
{
    template<>
    struct lessThan<Custom<float>>
    {
        bool operator()(const Custom<float>& lhs, const Custom<float>& rhs)
        {
            return lhs.key < rhs.key;
        }
    };

    template<>
    struct lessThan<Custom<int>>
    {
        bool operator()(const Custom<int>& lhs, const Custom<int>& rhs)
        {
            return lhs.key < rhs.key;
        }
    };

    template<>
    struct lessThan<Custom<unsigned int>>
    {
        bool operator()(const Custom<unsigned int>& lhs, const Custom<unsigned int>& rhs)
        {
            return lhs.key < rhs.key;
        }
    };

    template<>
    struct lessThanEqual<Custom<float>>
    {
        bool operator()(const Custom<float>& lhs, const Custom<float>& rhs)
        {
            return lhs.key <= rhs.key;
        }
    };

    template<>
    struct lessThanEqual<Custom<int>>
    {
        bool operator()(const Custom<int>& lhs, const Custom<int>& rhs)
        {
            return lhs.key <= rhs.key;
        }
    };

    template<>
    struct lessThanEqual<Custom<unsigned int>>
    {
        bool operator()(const Custom<unsigned int>& lhs, const Custom<unsigned int>& rhs)
        {
            return lhs.key <= rhs.key;
        }
    };
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

#define NTEST 0

int main(int argc, int* argv[])
{
	std::default_random_engine gen;
	std::uniform_int_distribution<int> dist(-1, 1);


    time_t now;
    time(&now);
    srand(static_cast<unsigned int>(now));

	bool exit = false;
	while (!exit) 
    {

#if NTEST
        bool useCustom = false;
        printf("Use custom object?\n");
        std::cin >> useCustom;

		bool useFloats = true;
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
#else
        bool useCustom = 0;
        bool useFloats = 0;
        bool _signed = 1;
        int arrayLength = 25;
#endif
		void* t = NULL;

		printf("Unsorted: ");
			
        if (useCustom)
        {
            if (useFloats)
            {
                t = new Custom<float>[arrayLength];
                for (int i = 0; i < arrayLength; i++)
                {
                    float k = (float)(rand() % 100) / 5.0f - 5.0f;
                    ((Custom<float>*)t)[i].key = k;
                    ((Custom<float>*)t)[i].name = std::to_string(k);
                }
            }
            else
            {
                if (_signed)
                {
                    t = new Custom<int>[arrayLength];

                    for (int i = 0; i < arrayLength; i++)
                    {
                        int k = (int)(rand() % 100) - 50;
                        ((Custom<int>*)t)[i].key = k;
                        ((Custom<int>*)t)[i].name = std::to_string(k);
                    }
                }
                else
                {
                    t = new Custom<unsigned int>[arrayLength];

                    for (int i = 0; i < arrayLength; i++)
                    {
                        unsigned int k = (unsigned int)(rand() % 100);
                        ((Custom<unsigned int>*)t)[i].key = k;
                        ((Custom<unsigned int>*)t)[i].name = std::to_string(k);
                    }
                }
            }

        }
        else 
        {
            if (useFloats) {
                t = new float[arrayLength];
                for (int i = 0; i < arrayLength; i++) {
                    ((float*)t)[i] = (float)(rand() % 100) / 5.0f - 5.0f;
                    printf("%f ", ((float*)t)[i]);
                }
                printf("\n");

                /*		for (int i = 0; i < arrayLength; i++) {
                printf("%u ", flip(((uint32_t*)t)[i]));
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
       }

#if NTEST
		int sortAlgorithm;
		printf("Choose Sort: \n 0: Insertion Sort\n 1: Bubble Sort\n 2: Merge Sort\n 3: Quick Sort\n 4: Randomized Quick Sort\n 5: Heap Sort\n 6: Counting Sort\n 7: Radix Sort\n");
		std::cin >> sortAlgorithm;

		int sortOrder;
		printf("Choose Sort Order: \n 0: Descending\n 1: Ascending\n");
		std::cin >> sortOrder;
#else
        int sortAlgorithm = 7;
        int sortOrder = SortOrderAscending;
#endif

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
            Insertion<i32>((i32*)t, arrayLength).Sort();
			//(_signed) ? insertionSort((float*)t, comparator, arrayLength, order) : insertionSort((unsigned int*)t, unsignedComparator, arrayLength, order);
			break;
		case 1:
            Bubble<i32>((i32*)t, arrayLength).Sort();

			//(_signed) ? bubbleSort((float*)t, comparator, arrayLength, order) : bubbleSort((unsigned int*)t, unsignedComparator, arrayLength, order);
			break;
		case 2:
        {
            if (useCustom)
            {
                if (useFloats)
                {
                    Merge< Custom<float>>((Custom<float>*)t, arrayLength).Sort();
                }
                else
                {
                    if (_signed) { Merge<Custom<int>>((Custom<int>*)t, arrayLength).Sort(); }
                    else { Merge<Custom<unsigned int>>((Custom<unsigned int>*)t, arrayLength).Sort(); }
                }
            }
            else
            {
                if (useFloats)
                {
                    Merge<float>((float*)t, arrayLength).Sort();
                }
                else
                {
                    if (_signed) { Merge<int>((int*)t, arrayLength).Sort(); }
                    else { Merge<unsigned int>((unsigned int*)t, arrayLength).Sort(); }
                }
            }
            break;
        }
		case 3:
        {

            if (useCustom)
            {
                if (useFloats)
                {
                    Quick< Custom<float>>((Custom<float>*)t, arrayLength).Sort();
                }
                else
                {
                    if (_signed) { Quick<Custom<int>>((Custom<int>*)t, arrayLength).Sort(); }
                    else { Quick<Custom<unsigned int>>((Custom<unsigned int>*)t, arrayLength).Sort(); }
                }
            }
            else
            {
                if (useFloats)
                {
                    Quick<float>((float*)t, arrayLength).Sort();
                }
                else
                {
                    if (_signed) { Quick<int>((int*)t, arrayLength).Sort(); }
                    else { Quick<unsigned int>((unsigned int*)t, arrayLength).Sort(); }
                }
            }	
            break;
        }
		case 4:
			//(_signed) ? randomizedQuickSort((float*)t, comparator, 0, arrayLength, order) : randomizedQuickSort((unsigned int*)t, unsignedComparator, 0, arrayLength, order);
			break;
		case 5:
		//	(_signed) ? heapSort((float*)t, comparator, arrayLength, order) : heapSort((unsigned int*)t, unsignedComparator, arrayLength, order);
			break;
		case 6:
		{
			if (_signed) 
            {	
                Count<int, int>((int*)t, arrayLength).Sort(rank);
			}
			else 
            {
                Count<unsigned int, unsigned int>((unsigned int*)t, arrayLength).Sort(unsignedRank);
			}
			break;
		}
		case 7:
		{
			if (useFloats) 
            {
                Radix<float, float>((float*)t, arrayLength).Sort();
			}
			else {
				if (_signed)
				{
					Radix<i32, i32>((i32*)t, arrayLength).Sort();
				}
				else
				{
                    Radix<u32, u32>((u32*)t, arrayLength).Sort();
                }
			}
			break;
		}
		default:
			break;
		}

		bool correct = true;
		for (int i = 1; i < arrayLength; i++) 
        {
            if (useCustom)
            {
                correct = (useFloats) ? lessThan<float>()(((Custom<float>*)t)[i - 1].key, ((Custom<float>*)t)[i].key) : (_signed) ? lessThan<int>()(((Custom<int>*)t)[i - 1].key, ((Custom<int>*)t)[i].key) : lessThan<unsigned int>()(((Custom<unsigned int>*)t)[i - 1].key, ((Custom<unsigned int>*)t)[i].key);
            }
            else
            {
                correct = (useFloats) ? (comparator(((float*)t)[i - 1], ((float*)t)[i]) >= 0) : (_signed) ? (icomp(((int*)t)[i - 1], ((int*)t)[i]) <= 0) : (ucomp(((unsigned int*)t)[i - 1], ((unsigned int*)t)[i]) >= 0);
            }   
		}
		
        if (!correct) 
        {
            printf("ERROR: Sort output is incorrect \n");
        }

		printf("Sorted: ");
		for (int i = 0; i < arrayLength; i++) {
            if (useCustom)
            {
              (useFloats) ? printf("%f ", ((Custom<float>*)t)[i].key) : (_signed) ? printf("%d ", ((Custom<int>*)t)[i].key) : printf("%u ", ((Custom<unsigned int>*)t)[i].key);
            }
            else
            {
                (useFloats) ? printf("%f ", ((float*)t)[i]) : (_signed) ? printf("%d ", ((int*)t)[i]) : printf("%u ", ((unsigned int*)t)[i]);
            }
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