#pragma once 
#ifndef RADIXSORT_H
#define RADIXSORT_H

#ifndef COMMON_HPP
#include "common.hpp"
#endif

#ifndef TYPEDEFS_H
#include "typedefs.h"
#endif

#include <vector>

namespace cliqCity
{
	namespace algorithm
	{
		template<class Type>
		class radix
		{
        public:
            radix(Type* const in, const int& length) : in(in), length(length)
            {
                swap0 = new Type[length];
                swap1 = new Type[length];              
            }

            radix(std::vector<Type>& in) : radix::radix(in.data, (int)in.size) 
            {
            
            }

            ~radix()
            {
                delete[] swap0;
                delete[] swap1;
            }

        protected:
            Type* in;
            Type* swap0;
            Type* swap1;
            int length;
		};

        template <class Type, typename Key>
        class Radix
        {

        };

        template<class Type>
        class Radix<Type, u32> : public radix<Type>
        {
        public:
            using radix<Type>::radix;

            template<class Functor>
            inline Radix& Sort(Functor func)
            {
                // Range * Number of Counters * Bytes Per Location
                u32 counter[256 * 4];
                memset(counter, 0, 256 * 4 * sizeof(u32));

                u32* c0 = &counter[0];		// LSB
                u32* c1 = &counter[256];
                u32* c2 = &counter[512];
                u32* c3 = &counter[768];	// MSB

                                            // Counting Pass
                u32 uk;
                u8* ub = nullptr;
                for (int i = 0; i < length; i++)
                {
                    uk = func(in[i]);
                    ub = reinterpret_cast<u8*>(&uk);

                    // Split key into individual bytes and count in each list
                    c0[*ub]++;
                    c1[*(ub + 1)]++;
                    c2[*(ub + 2)]++;
                    c3[*(ub + 3)]++;
                }

                // Set counter[i] to number of elements less than or equal to i
                for (int i = 1; i < 256; i++)
                {
                    c0[i] += c0[i - 1];
                    c1[i] += c1[i - 1];
                    c2[i] += c2[i - 1];
                    c3[i] += c3[i - 1];
                }

                Type* s0 = &swap0[0];
                Type* s1 = &swap1[0];

                size_t size = sizeof(Type) * length;
                memcpy_s(s0, size, in, size);

                // First 3 passes
                u32* c = nullptr;

                for (int pass = 0; pass < 3; pass++)
                {
                    c = &counter[(pass << 8)];

                    for (int i = length - 1; i >= 0; i--)
                    {
                        uk = func(s0[i]);
                        ub = reinterpret_cast<u8*>(&uk) + pass;
                        s1[c[*(ub)] - 1] = s0[i];
                        c[*(ub)]--;
                    }

                    // swap pointers
                    exchange(s0, s1);
                }

                for (int i = length - 1; i >= 0; i--)
                {
                    uk = func(s0[i]);
                    ub = reinterpret_cast<u8*>(&uk) + 3;
                    s1[c3[*(ub)] - 1] = s0[i];
                    c3[*(ub)]--;
                }

                // Copy output back to original in array
                memcpy_s(in, size, s1, size);

                return *this;
            }
        };

        template<class Type>
        class Radix<Type, i32> : public radix<Type>
        {
        public:
            using radix<Type>::radix;

            template<class Functor>
            inline Radix& Sort(Functor func)
            {
                u32 counter[256 * 4];
                memset(counter, 0, 256 * 4 * sizeof(u32));

                u32* c0 = &counter[0];
                u32* c1 = &counter[256];
                u32* c2 = &counter[512];
                u32* c3 = &counter[768];

                u32 nl = 0;					// Negative Length
                u8* ub = nullptr;
                i32 ik;

                // Counting Pass
                for (int i = 0; i < length; i++)
                {
                    ik = func(in[i]);
                    ub = reinterpret_cast<u8*>(&ik);

                    // Split key into individual bytes and count in each list
                    c0[*ub]++;
                    c1[*(ub + 1)]++;
                    c2[*(ub + 2)]++;
                    c3[*(ub + 3)]++;

                    if (*(ub + 3) > 127)
                    {
                        nl++;
                    }
                }

                // Set counter[i] to number of elements less than or equal to i
                for (int i = 1; i < 256; i++)
                {
                    c0[i] += c0[i - 1];
                    c1[i] += c1[i - 1];
                    c2[i] += c2[i - 1];
                }

                // The MSB counter handles positive (<127) and negative (>127) values

                // Add negativeLenth to the number of elements less than or equal to 0
                c3[0] += nl;

                for (int i = 1; i < 128; i++)
                {
                    c3[i] += c3[i - 1];
                }

                // Set negative counter[i] to number of elements less than or equal to i
                // Iterate in reverse because negative values are ascending

                for (int i = 254; i > 127; --i)
                {
                    c3[i] -= c3[i + 1];
                }


                Type* s0 = &swap0[0];
                Type* s1 = &swap1[0];

                size_t size = sizeof(Type) * length;
                memcpy_s(s0, size, in, size);

                u32* c = nullptr;

                // Radix Passes	
                for (int pass = 0; pass < 3; pass++)
                {
                    // Get the counter for the current pass
                    c = &counter[(pass << 8)];

                    for (int i = length - 1; i >= 0; i--)
                    {
                        ik = func(s0[i]);
                        ub = reinterpret_cast<u8*>(&ik) + pass;

                        s1[c[*(ub)] - 1] = s0[i];
                        c[*(ub)]--;
                    }

                    exchange(s0, s1);
                }

                for (int i = length - 1; i >= 0; i--)
                {
                    ik = func(s0[i]);
                    ub = reinterpret_cast<u8*>(&ik) + 3;

                    s1[c3[*(ub)] - 1] = s0[i];
                    c3[*(ub)]--;
                }

                memcpy_s(in, size, s1, size);

                return *this;
            }
        };

        template<class Type>
        class Radix<Type, f32> : public radix<Type>
        {
        public:
            using radix<Type>::radix;

            template<class Functor>
            inline Radix& Sort(Functor func)
            {
                u32 counter[256 * 4 + 128];
                memset(counter, 0, (256 * 4 + 128) * sizeof(u32));

                u32* c0 = &counter[0];
                u32* c1 = &counter[256];
                u32* c2 = &counter[512];
                u32* c3 = &counter[768];
                u32* no = &counter[1024];   // Negative offsets counted separately

                u32 nl = 0;
                u8* ub = nullptr;
                f32 fk;

                for (int i = 0; i < length; i++)
                {
                    fk = func(in[i]);
                    ub = reinterpret_cast<u8*>(&fk);

                    c0[*ub]++;
                    c1[*(ub + 1)]++;
                    c2[*(ub + 2)]++;
                    c3[*(ub + 3)]++;

                    if (*(ub + 3) > 127)
                    {
                        no[*(ub + 3) - 128]++;
                        nl++;
                    }
                }

                for (int i = 1; i < 256; i++)
                {
                    c0[i] += c0[i - 1];
                    c1[i] += c1[i - 1];
                    c2[i] += c2[i - 1];
                }

                // Offset positive numbers by negative length
                c3[0] += nl;
                for (int i = 1; i < 128; i++)
                {
                    c3[i] += c3[i - 1];
                }

                // Get offsets for negative numbers
                no[0] = 0;
                for (int i = 126; i >= 0; --i)
                {
                    no[i] += no[i + 1];
                }

                Type* s0 = &swap0[0];
                Type* s1 = &swap1[0];

                size_t size = sizeof(Type) * length;
                memcpy_s(s0, size, in, size);

                u32* c = nullptr;

                // Radix Passes	
                for (int pass = 0; pass < 3; pass++)
                {
                    c = &counter[(pass << 8)];

                    for (int i = length - 1; i >= 0; i--)
                    {
                        fk = func(s0[i]);

                        u32 uk = *(reinterpret_cast<u8*>(&fk) + pass);
                        s1[c[uk] - 1] = s0[i];
                        c[uk]--;
                    }

                    exchange(s0, s1);
                }

                // Last pass for negatives
                for (int i = length - 1; i >= 0; i--)
                {
                    fk = func(s0[i]);

                    u32 uk = *(reinterpret_cast<u8*>(&fk) + 3);

                    if (uk < 128) { s1[c3[uk] - 1] = s0[i]; }
                    else { s1[no[uk - 128] - c3[uk]] = s0[i]; }

                    c3[uk]--;
                }

                memcpy_s(in, size, s1, size);

                return *this;
            }
        };
	}

	uint32_t flip(uint32_t& f)
	{
		uint32_t mask = -int32_t(f >> 31) | 0x80000000;
		return f ^ mask;
	}

	uint32_t unflip(uint32_t& f)
	{
		uint32_t mask = ((f >> 31) - 1) | 0x80000000;
		return f ^ mask;
	}
}

#endif