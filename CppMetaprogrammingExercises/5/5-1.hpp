#pragma once
#include <limits>
#include "5-0.hpp"

constexpr auto max_long = std::numeric_limits<long>::max();

template<class T, long N0 = max_long,long N1 = max_long,long N2 = max_long, long N3 = max_long>
struct vector_c;

//template<class T, T N0, T N1, T N2, T N3>
//struct vector_c<>

//template<class Vec_c>
//struct double_first_half
//{
//
//};

//template<int...Ns>
//struct double_first_half<vector_c<int,Ns...>>:double_first_n<vector_c<int, Ns...>,sizeof...(Ns)/2>
//{
//
//};

//template<class Vec_c,int Index>
//struct double_first_n;
//
//template<int Index,int...Ns>
//struct double_first_n<vector_c<int, Ns...>, Index>
//{
//	using type = vector_c<int, >
//};

template<class T,class T2, int begin , int end, int flag>
struct Operator
{
	using type = typename Operator<tiny_push_back<T, int_constant<at_<T2, int_constant<begin>>::type::value * 2>>::type, begin + 1, end, flag>::type;// : typename Operator<tiny_push_back<T, int_constant<at_<T2, int_constant<begin>>::type::value>>, begin + 1, end, flag>::type;
};

template<class T, class T2, int end, int flag>
struct Operator<T, T2, end, end, flag>
{
	using type = tiny_push_back<T, int_constant<at_<T2, int_constant<end>>::type::value * 2>>::type;//:tiny_push_back<T, int_constant<at_<T2, int_constant<end>>::type::value>>;
};

void test5_1()
{
	using t1 = tiny<int_constant<2>, int_constant<4>, int_constant<6>>;
	using t2 = tiny<int_constant<1>, int_constant<2>, int_constant<3>>;
	constexpr auto tmp = at_<t2, int_constant<0>>::type::value;
	constexpr auto tmp1 = at_<t2, int_constant<1>>::type::value;
	constexpr auto tmp2 = at_<t2, int_constant<2>>::type::value;
	tiny_push_back<tiny<>, int_constant<tmp * 2>>::type;
	static_assert(std::is_same<t1,
		Operator<tiny<>, t2, 0, 2, 0>::type>::value);
}
