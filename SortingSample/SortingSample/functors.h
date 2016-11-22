struct Comparator
{
	inline int operator()(const float& first, const float& second) const
	{
		if (first < second) {
			return -1;
		}
		else if (first == second) {
			return 0;
		}
		else {
			return 1;
		}
	}
} comparator;

template<typename T>
struct TComparator
{
	inline int operator()(const T& first, const T& second) const
	{
		if (first < second) {
			return -1;
		}
		else if (first == second) {
			return 0;
		}
		else {
			return 1;
		}
	}
};

TComparator<float> fcomp;
TComparator<unsigned int> ucomp;
TComparator<int> icomp;


struct UnsignedComparator
{
	inline int operator()(const unsigned int& first, const unsigned int& second) const
	{
		if (first < second) {
			return -1;
		}
		else if (first == second) {
			return 0;
		}
		else {
			return 1;
		}
	}
} unsignedComparator;

struct Rank
{
	inline int operator()(const float& value) const
	{
		return *(int *)&value;
	}
} rank;

struct UnsignedRank
{
	inline unsigned int operator()(const unsigned int& value) const
	{
		return value;
	}
} unsignedRank;

struct Key
{
	inline float* operator()(float* const t, const int& index) const
	{
		return &t[index];
	}
} key;

struct TestKey
{
	inline float operator()(float* const t, const int& index) const
	{
		return t[index];
	}
} testKey;

struct UnsignedKey
{
	inline unsigned int* operator()(unsigned int* t, const int& index) const
	{
		return &t[index];
	}
} unsignedKey;

template<typename T>
struct TKey
{
	inline T operator()(T t) const
	{
		return t;
	}
};

TKey<float> fKey;
TKey<int> iKey;
TKey<unsigned int> uKey;

int compareInt(const void* a, const void* b)
{
	int first = *(int*)a;
	int second = *(int*)b;
	if (first < second) {
		return -1;
	}
	else if (first == second) {
		return 0;
	}
	else {
		return 1;
	}
}