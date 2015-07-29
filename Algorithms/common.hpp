// common.hpp
//
// Common utility functions
//
// Gabriel Ortega

#pragma once

template<class T>
inline void exchange(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}