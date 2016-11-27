#pragma once
#ifndef COUNTINGSORT_H
#define COUNTINGSORT_H

#ifndef ALGO_INTERNAL_H
#include "algo_internal.h"
#endif

namespace algorithm
{
    template<class Type>
    class count
    {
    public:
        count(Type* const in, const int& length) : in(in), length(length)
        {
            swap = new Type[length];
        }

        count(std::vector<Type>& in) : count::count(in.data(), (int)in.size())
        {

        }

        ~count()
        {
            delete[] swap;
        }

    protected:
        Type* in;
        Type* swap;
        int length;
    };

    template<class Type, typename Key>
    class Count
    {

    };

    // Counting Sort: Uses auxiliary storage to count elements in array t. The counter maintains the number of elements in rank with each index. 
    // The rank of each element in t are assumed to be positive integers.
    // The counter is then used to index back into the output array. Runs in linear time if max <= length^2.
    template<class Type>
    class Count<Type, u32> : public count<Type>
    {
    public:
        using count<Type>::count;

        template<class Functor>
        Count& Sort(Functor func)
        {
            u32 max = 0;
            for (int i = 0; i < length; ++i)
            {
                max = std::max(func(in[i]), max);
            }

            // Initialize counter and set to zero.
            u32* counter = new u32[max + 1];
            memset(counter, 0, sizeof(u32) * (max + 1));

            // Set counter[j] to number of elements equal to j
            for (int j = 0; j < length; j++) {
                counter[func(in[j])]++;
            }

            // Set counter[i] to number of elements less than or equal to j
            u32* iter = &counter[1];
            u32* end = &counter[max + 1];
            while (iter != end) {
                *iter += *(iter - 1);
                iter++;
            }


            // Index back into the output array
            for (int j = length - 1; j >= 0; j--) {
                u32 r = func(in[j]);
                swap[counter[r] - 1] = in[j];
                counter[r]--;
            }

            size_t size = sizeof(Type) * length;
            memcpy_s(in, size, swap, size);

            delete[] counter;

            return *this;
        }
    };

    // Counting Sort: Uses auxiliary storage to count elements in array t. The counter maintains the number of elements in rank with each index. 
    // The rank of each element in t are assumed to be signed integers.
    // The counter is then used to index back into the output array. Runs in linear time if range <= length^2.
    template<class Type>
    class Count<Type, i32> : public count<Type>
    {
    public:
        using count<Type>::count;

        template<class Functor>
        Count& Sort(Functor func)
        {
            i32 max = INT32_MIN;
            i32 min = INT32_MAX;
            for (int i = 0; i < length; ++i)
            {
                max = std::max(func(in[i]), max);
                min = std::min(func(in[i]), min);
            }

            // Initialize counter and set to zero.
            i32 range = max - min;
            u32* counter = new u32[range + 1];
            memset(counter, 0, sizeof(u32) * (range + 1));

            // Set counter[j] to number of elements equal to j
            for (int j = 0; j < length; j++) {
                counter[func(in[j]) - min]++;
            }

            // Set counter[i] to number of elements less than or equal to i
            u32* iter = &counter[1];
            u32* end = &counter[range + 1];
            while (iter != end) {
                *iter += *(iter - 1);
                iter++;
            }

            // Index back into the output array
            for (int j = length - 1; j >= 0; j--) {
                u32 r = func(in[j]) - min;
                swap[counter[r] - 1] = in[j];
                counter[r]--;
            }

            size_t size = sizeof(Type) * length;
            memcpy_s(in, size, swap, size);

            delete[] counter;

            return *this;
        }
    };
}

#endif