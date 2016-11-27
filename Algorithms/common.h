#pragma once
#ifndef COMMON_H
#define COMMON_H

enum SortOrder
{
    SortOrderDescending = -1,
    SortOrderEqual = 0,
    SortOrderAscending = 1
};

template<class T>
inline void exchange(T& a, T& b)
{
    T t = a;
    a = b;
    b = t;
}

namespace algorithm
{
    template<class Type>
    struct lessThan
    {
        bool operator()(const Type& lhs, const Type& rhs)
        {
            return lhs < rhs;
        }
    };

    template<class Type>
    struct lessThanEqual
    {
        bool operator()(const Type& lhs, const Type& rhs)
        {
            return lhs <= rhs;
        }
    };
}

#endif