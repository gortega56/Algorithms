#pragma once
#ifndef HEAP_H
#define HEAP_H

#ifndef ALGO_INTERNAL_H
#include "algo_internal.h"
#endif

namespace algorithm
{
    template <class Type>
    class Heap
    {
    public:
        Heap(Type* in, int heapSize, int length) : in(in), heapSize(heapSize), length(length)
        {
            buildHeap(in, heapSize, length, lessThan<Type>());
        }

        inline Type& getParent(int index) const
        {
            return in[(index - 1) >> 1];
        }

        inline Type& getLeft(int index) const
        {
            return in[(index << 1) + 1];
        }

        inline Type& getRight(int index) const
        {
            return in[(index << 1) + 2];
        }

        inline int getHeapSize() const
        {
            return heapSize;
        }

        inline int getLength() const
        {
            return length;
        }

    private:
        Type* in;
        int heapSize;
        int length;

        // Build Heap: Uses subroutine to construct a heap given array t, and has linear Complexity
        template<class Functor>
        static void buildHeap(Type* const in, const int& length, Functor func)
        {
            int heapSize = length;
            for (int i = (length / 2); i >= 0; i--) 
            {
                heapify(in, i, heapSize, func);
            }
        }

        // Heapify: Sorts an array in place to statisfy a heap property defined by comparator and sort order. Runs in logarithmic complexity
        template<class Functor>
        void heapify(Type* const in, const int& index, const int& heapSize, Functor func)
        {
            // Get left and right child.
            int left = (index << 1) + 1;
            int right = (index << 1) + 2;

            // Find target value (min or max).
            int target;
            if (left < heapSize && func(in[left], in[index])) 
            {
                target = left;
            }
            else 
            {
                target = index;
            }

            if (right < heapSize && func(in[right], in[target])) 
            {
                target = right;
            }

            // Swap if either child is greater/smaller and heapify the target.
            if (target != index) 
            {
                exchange(in[index], in[target]);
                heapify(in, target, heapSize, func);
            }
        }

        // Heap Sort: Sorts array in place by constructing a heap. This sort is stable and runs in O(nlgn) complexity.
        template<class Functor>
        static void Sort(Type* const in, const int& length, Functor func)
        {
            int heapSize = length;
            buildHeap(in, length, func);
            for (int i = length - 1; i > 0; i--) 
            {
                exchange(in[0], in[i]);
                heapSize--;
                heapify(in, 0, heapSize, func);
            }
        }
    };
}

#endif
