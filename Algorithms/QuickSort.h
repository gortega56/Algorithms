#pragma once
#ifndef QUICKSORT_H
#define QUICKSORT_H

#ifndef ALGO_INTERNAL_H
#include "algo_internal.h"
#endif

namespace algorithm
{
    template<class Type>
    class Quick
    {
    public:
        Quick(Type* const in, const int& length) : in(in), length(length)
        {

        }

        Quick(std::vector<Type>& in) : Quick::Quick(in.data(), (int)in.size())
        {

        }

        template<class Functor = lessThanEqual<Type>>
        Quick& Sort(Functor func = lessThanEqual<Type>())
        {
            sort(in, 0, length, func);
            return *this;
        }

    private:
        Type* in;
        int length;

        // Quick Sort: Recursively sorts using Partition subroutine. Runs in worst case quadratic time, and nlgn expected time. Asymptotic performance can be improved via randomization
        // TO DO: Optimize using tail recursive sort.
        template<class Functor>
        void sort(Type* const in, const int& begin, const int& end, Functor func)
        {
            if (end - begin > 1)
            {
                exchange(in[end - 1], in[begin + (rand() % (end - begin))]);
                int p = partition(in, begin, end, func);
                sort(in, begin, p, func);
                sort(in, p + 1, end, func);
            }
        }

        // Partition: A subroutine used by Quick Sort. Partitions array t into subarrays of values less than and greater than the partition element. Always uses last element as partition.
        // TO DO: Optimize for non distinct elements by returning a partition range. Median of 3 partition.
        template<class Functor>
        int partition(Type* const t, const int& begin, const int& end, Functor func)
        {
            int partition = end - 1;
            int right = begin - 1;

            // Sort elements based on comparison with partition element
            for (int left = begin; left < partition; left++)
            {
                if (func(in[left], in[partition]))
                {
                    exchange(in[++right], in[left]);
                }
            }

            // Swap partition with first element of right sub array
            exchange(in[++right], in[partition]);

            return right;
        }
    };
}

#endif
