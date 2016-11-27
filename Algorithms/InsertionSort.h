#pragma once
#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#ifndef ALGO_INTERNAL_H
#include "algo_internal.h"
#endif

namespace algorithm
{
    template<class Type>
    class Insertion
    {
    public:
        Insertion(Type* const in, const int& length) : in(in), length(length)
        {

        }

        Insertion(std::vector<Type>& in) : Insertion::Insertion(in.data(), (int)in.size())
        {

        }

        template<class Functor = lessThan<Type>>
        Insertion& Sort(Functor func = lessThan<Type>())
        {
            for (int j = 1; j < length; j++) 
            {
                Type temp = in[j];
                int i = j - 1;
                while (i >= 0 && func(temp, in[i]))
                {
                    in[i + 1] = in[i];
                    i--;
                }

                in[i + 1] = temp;
            }

            return *this;
        }

    private:
        Type* in;
        int length;
    };
}

#endif
