#include "MergeSort.h"
#include "QuickSort.h"
#include "RadixSort.h"
#include "CountingSort.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "typedefs.h"
#include <vector>
#include <random>
#include <ctime>
#include <string>

template <class T>
struct Sortable
{
    const char* name;
    T key;
    
    Sortable() {};
    Sortable(std::string n, T k) : name(n.c_str()), key(k) {}
    ~Sortable() { name = nullptr; }
};

namespace algorithm
{
    template<>
    struct lessThan<Sortable<f32>>
    {
        bool operator()(const Sortable<f32>& lhs, const Sortable<f32>& rhs)
        {
            return lhs.key < rhs.key;
        }
    };

    template<>
    struct lessThan<Sortable<u32>>
    {
        bool operator()(const Sortable<u32>& lhs, const Sortable<u32>& rhs)
        {
            return lhs.key < rhs.key;
        }
    };

    template<>
    struct lessThan<Sortable<i32>>
    {
        bool operator()(const Sortable<i32>& lhs, const Sortable<i32>& rhs)
        {
            return lhs.key < rhs.key;
        }
    };

    template<>
    struct lessThanEqual<Sortable<f32>>
    {
        bool operator()(const Sortable<f32>& lhs, const Sortable<f32>& rhs)
        {
            return lhs.key <= rhs.key;
        }
    };

    template<>
    struct lessThanEqual<Sortable<u32>>
    {
        bool operator()(const Sortable<u32>& lhs, const Sortable<u32>& rhs)
        {
            return lhs.key <= rhs.key;
        }
    };

    template<>
    struct lessThanEqual<Sortable<i32>>
    {
        bool operator()(const Sortable<i32>& lhs, const Sortable<i32>& rhs)
        {
            return lhs.key <= rhs.key;
        }
    };
}

using namespace algorithm;

std::vector<Sortable<f32>> sfv;
std::vector<Sortable<u32>> suv;
std::vector<Sortable<i32>> siv;

std::vector<f32> fv;
std::vector<u32> uv;
std::vector<i32> iv;

int length = 100;

void check()
{
    static int ndx = 0;
    for (int i = 1; i < length; ++i)
    {
        bool correct;
        correct = sfv[i - 1].key <= sfv[i].key;
        correct = suv[i - 1].key <= suv[i].key;
        correct = siv[i - 1].key <= siv[i].key;

        correct = fv[i - 1] <= fv[i];
        correct = uv[i - 1] <= uv[i];
        correct = iv[i - 1] <= iv[i];
        
        if (!correct)
        {
            printf("Failed Sort at index: %d\n", ndx);
            break;
        }
    }

    ndx++;
}

void reset()
{
    sfv.clear();
    siv.clear();
    suv.clear();
    fv.clear();
    uv.clear();
    iv.clear();

    for (int i = 0; i < length; ++i)
    {
        f32 f = (f32)(rand() % 100) / 10.0f - 10.0f;
        u32 u = (u32)(rand() % 100);
        i32 n = (i32)(rand() % 100) - 10;

        sfv.push_back(Sortable<f32>(std::to_string(f), f));
        suv.push_back(Sortable<u32>(std::to_string(u), u));
        siv.push_back(Sortable<i32>(std::to_string(n), n));

        fv.push_back(f);
        uv.push_back(u);
        iv.push_back(n);
    }
}

int main(int argc, int* argv[])
{
    time_t now;
    time(&now);
    srand(static_cast<unsigned int>(now));

    reset();

    Merge<Sortable<f32>>(sfv).Sort([](const Sortable<f32>& lhs, const Sortable<f32> rhs) { return lhs.key < rhs.key; });
    Merge<Sortable<i32>>(siv).Sort();
    Merge<Sortable<u32>>(suv).Sort();
    Merge<f32>(fv).Sort();
    Merge<i32>(iv).Sort();
    Merge<u32>(uv).Sort();

    check();
    reset();

    Quick<Sortable<f32>>(sfv).Sort();
    Quick<Sortable<i32>>(siv).Sort();
    Quick<Sortable<u32>>(suv).Sort();
    Quick<f32>(fv).Sort();
    Quick<i32>(iv).Sort();
    Quick<u32>(uv).Sort();

    check();
    reset();

    Insertion<Sortable<f32>>(sfv).Sort();
    Insertion<Sortable<i32>>(siv).Sort();
    Insertion<Sortable<u32>>(suv).Sort();
    Insertion<f32>(fv).Sort();
    Insertion<i32>(iv).Sort();
    Insertion<u32>(uv).Sort();

    check();
    reset();

    Bubble<Sortable<f32>>(sfv).Sort();
    Bubble<Sortable<i32>>(siv).Sort();
    Bubble<Sortable<u32>>(suv).Sort();
    Bubble<f32>(fv).Sort();
    Bubble<i32>(iv).Sort();
    Bubble<u32>(uv).Sort();

    check();
    reset();

    Radix<Sortable<f32>, f32>(sfv).Sort([](Sortable<f32> s) { return s.key; });
    Radix<Sortable<i32>, i32>(siv).Sort([](Sortable<i32> s) { return s.key; });
    Radix<Sortable<u32>, u32>(suv).Sort([](Sortable<u32> s) { return s.key; });
    Radix<f32, f32>(fv).Sort([](f32 s) { return s; });
    Radix<i32, i32>(iv).Sort([](i32 s) { return s; });
    Radix<u32, u32>(uv).Sort([](u32 s) { return s; });

    check();
    reset();

    Count<Sortable<f32>, i32>(sfv).Sort([](Sortable<f32> s) { return (i32)s.key; });
    Count<Sortable<i32>, i32>(siv).Sort([](Sortable<i32> s) { return s.key; });
    Count<Sortable<u32>, u32>(suv).Sort([](Sortable<u32> s) { return s.key; });
    Count<f32, i32>(fv).Sort([](f32 s) { return (i32)s; });
    Count<i32, i32>(iv).Sort([](i32 s) { return s; });
    Count<u32, u32>(uv).Sort([](u32 s) { return s; });

    check();
    reset();

    return 0;
}