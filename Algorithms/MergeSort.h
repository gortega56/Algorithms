#pragma once
#ifndef MERGESORT_H
#define MERGESORT_H

namespace cliqCity
{
    namespace algorithm
    {
        template<class Type>
        struct LessThan
        {
            bool operator()(const Type& lhs, const Type& rhs)
            {
                return lhs < rhs;
            }
        };

        template<class Type>
        class Merge
        {
        public:
            Merge(Type* const in, const int& length) : in(in), length(length)
            {
                aux = new Type[length];
            }

            ~Merge()
            {
                delete[] aux;
            }

            Merge& Sort()
            {
                sort(in, 0, length);
                return *this;
            }

        private:
            Type* in;
            Type* aux;
            int length;

            // Merge Sort: Recursively splits array into tow subarrays of n/2 length. Uses Merge subroutine. Has complexity O(nlgn)
            // Note: r is the exclusive last index of array t.
            void sort(Type* const in, const int& p, const int& r)
            {
                if (r - p > 1) 
                {
                    int q = static_cast<int>((p + r) * 0.5f);
                    sort(in, p, q);
                    sort(in, q, r);
                    merge(in, p, q, r);
                }
            }

            // Merge: A subroutine used by Merge Sort. Uses auxiliary storage to merge to sorted arrays. Has linear complexity
            // Note: r is the exclusive last index of array t. It is NOT the length.
            void merge(Type* const in, const int& p, const int& q, const int& r)
            {
                int n1 = q - p;
                int n2 = r - q;
                Type* left = &aux[p];
                Type* right = &aux[q];

                int i = 0;
                for (; i < n1; i++) 
                {
                    left[i] = in[p + i];
                }

                int j = 0;
                for (; j < n2; j++) 
                {
                    right[j] = in[q + j];
                }

                i = 0;
                j = 0;

                LessThan<Type> lt;

                for (int k = p; k < r; k++)
                {
                    if (i >= n1)
                    {
                        in[k] = right[j];
                        j++;
                        continue;
                    }
                    else if (j >= n2)
                    {
                        in[k] = left[i];
                        i++;
                        continue;
                    }

                    if (lt(left[i], right[j]))
                    {
                        in[k] = left[i];
                        i++;
                    }
                    else
                    {
                        in[k] = right[j];
                        j++;
                    }
                }
            }
        };
    }
}

#endif