#pragma once 
#ifndef RADIXSORT_HPP
#define RADIXSORT_HPP
#include "common.hpp"
#include <stdint.h>

#ifndef TYPEDEFS_H
#include "typedefs.h"
#endif

#include <functional>
#include <vector>

#define LOG std::cout

namespace cliqCity
{
	namespace algorithm
	{
		template<class Type, typename Key>
		class Radix
		{
		public:
			Radix(Type* const in, const int& length, Type* const out) : _in(in), _out(out), _len(length)  {}
            Radix(std::vector<Type> in, std::vector<Type>* out) : _in(in.data), _out(out.data), _len(static_cast<int>(in.size())) {}

            template<class Functor>
            Radix Sort(Functor key)
            {
                return Sort(_in, _len, _out, key);
            }

			template<class Functor>
			Radix* Sort(Type* const in, const int& length, Type* out, Functor key)
			{
				throw UnsupportedTypeException;
			}

			template<class Functor>
			Radix* Sort(std::vector<Type> in, std::vector<Type>* out, Functor key)
			{
				out->resize(in.size());
				return RadixSort(in.data(), in.size(), out.data(), key);
			}

            template<class Functor>
            static void Sort()

        private:
            Type* _in;
            Type* _out;
            int _len;
		};

		template<class Type>
		struct RadixSort<Type, u32>
		{
			template<class Functor>
			void operator()(Type* const in, const int& length, Type* out, Functor functor)
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
					uk = functor(in[i]);
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

				size_t size = sizeof(Type) * length;
				Type* swap	= new Type[length];
				memcpy_s(swap, size, in, size);

				// Radix Passes
				u32* c = nullptr;
				for (int pass = 0; pass < 4; pass++) 
				{
					c = &counter[(pass << 8)];

					for (int i = length - 1; i >= 0; i--) 
					{
						uk = functor(swap[i]);
						ub = reinterpret_cast<u8*>(&uk) + pass;
						out[c[*(ub)] - 1] = swap[i];
						c[*(ub)]--;
					}

					// Copy output back to swap for next pass
					memcpy_s(swap, size, out, size);
				}

				delete[] swap;
			}
		};

		template<class Type>
		struct RadixSort<Type, i32>
		{
			template<class Functor>
			void operator()(Type* const in, const int& length, Type* out, Functor functor)
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
					ik = functor(in[i]);
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


				size_t size = sizeof(Type) * length;
				Type* swap = new Type[length];
				memcpy_s(swap, size, in, size);

				u32* c = nullptr;

				// Radix Passes	
				for (int pass = 0; pass < 4; pass++) 
				{
					// Get the counter for the current pass
					c = &counter[(pass << 8)];

					for (int i = length - 1; i >= 0; i--) 
					{
						ik = functor(swap[i]);
						ub = reinterpret_cast<u8*>(&ik) + pass;

						out[c[*(ub)] - 1] = swap[i];
						c[*(ub)]--;
					}

					// Copy output back to swap for next pass NOTE: EXTRA COPY AT PASS 3
					memcpy_s(swap, size, out, size);
				}

				delete[] swap;
			}
		};

		template<class Type>
		struct RadixSort<Type, f32>
		{
			template<class Functor>
			void operator()(Type* const in, const int& length, Type* out, Functor functor)
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
					fk = functor(in[i]);
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

				size_t size = sizeof(Type) * length;
				Type* swap = new Type[length];
				memcpy_s(swap, size, in, size);

				u32* c = nullptr;

                // Radix Passes	
				for (int pass = 0; pass < 3; pass++)
				{
					c = &counter[(pass << 8)];

					for (int i = length - 1; i >= 0; i--)
					{
						fk = functor(swap[i]);

						u32 uk = *(reinterpret_cast<u8*>(&fk) + pass);
						out[c[uk] - 1] = swap[i];
						c[uk]--;
					}

					memcpy_s(swap, size, out, size);
				}

                // Last pass for negatives
				for (int i = length - 1; i >= 0; i--)
				{
					fk = functor(swap[i]);
					
                    u32 uk = *(reinterpret_cast<u8*>(&fk) + 3);

                    if (uk < 128) { out[c3[uk] - 1]     = swap[i]; }
                    else { out[no[uk - 128] - c3[uk]]   = swap[i]; }

                    c3[uk]--;
				}

				delete[] swap;
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