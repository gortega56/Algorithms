#pragma once
#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#ifndef ALGO_INTERNAL_H
#include "algo_internal.h"
#endif

namespace algorithm
{
    template<class Type>
    class Bubble
    {
    public:
        Bubble(Type* const in, const int& length) : in(in), length(length)
        {

        }

        Bubble(std::vector<Type>& in) : Bubble::Bubble(in.data(), (int)in.size())
        {

        }

        // Bubble Sort: Stable algorithm that sorts elements in place. Quadratic complexity.
        template<class Functor = lessThan<Type>>
        Bubble& Sort(Functor func = lessThan<Type>())
        {
            for (int i = 0; i < length; i++) 
            {
                for (int j = length - 1; j > 0; j--) 
                {
                    if (func(in[j], in[j - 1])) 
                    {
                        exchange(in[j], in[j - 1]);
                    }
                }
            }

            return *this;
        }

    private:
        Type* in;
        int length;
    };
}

#endif
