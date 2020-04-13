#pragma once
#include <type_traits>

template<long long N>
struct is_binary
{
	static const bool value = is_binary<N / 10>::value && (N % 10 < 2);
};

template<>
struct is_binary<0>
{
	static const bool value = true;
};

template<long long N>
struct binary
{
	static_assert(is_binary<N>::value, "is not binary !");
	static const long long value = N % 10 + binary<N / 10>::value * 2;
};

template<>
struct binary<0>
{
	static const long long value = 0;
};

void test3_0()
{
	constexpr auto test1 = binary<101011010>::value;	//success
	constexpr auto test1 = binary<9845752>::value;		//fail
}
