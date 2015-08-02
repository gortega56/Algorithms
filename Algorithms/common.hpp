// common.hpp
//
// Common utility functions
//
// Gabriel Ortega

#pragma once

namespace cliqCity
{
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

	template<class T, class C>
	inline int maxIndex(T* const t, const C& compare, const int& length)
	{
		int max = 0;
		for (int i = 1; i < length; i++) {
			if (compare(t[i], t[max]) == 1) {
				max = i;
			}
		}

		return max;
	}
}

