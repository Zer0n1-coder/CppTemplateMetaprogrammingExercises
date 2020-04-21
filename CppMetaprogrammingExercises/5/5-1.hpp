#pragma once
#include <limits>
#include "5-0.hpp"

template<class T, class T2, int begin, int end, int flag>
struct Operator
{
	static constexpr int value = begin <= flag ? at_<T2, int_constant<begin>>::type::value * 2 : at_<T2, int_constant<begin>>::type::value;
	using type = typename Operator<tiny_push_back<T, int_constant<value>>::type, T2, begin + 1, end, flag>::type;
};

template<class T, class T2, int end, int flag>
struct Operator<T, T2, end, end, flag>
{
	static constexpr int value = end <= flag ? at_<T2, int_constant<end>>::type::value * 2 : at_<T2, int_constant<end>>::type::value;
	using type = tiny_push_back<T, int_constant<value>>::type
};

void test5_1()
{
	using t1 = tiny<int_constant<2>, int_constant<2>, int_constant<3>>;
	using t2 = tiny<int_constant<1>, int_constant<2>, int_constant<3>>;

	static_assert(std::is_same<t1,Operator<tiny<>, t2, 0, 2, 0>::type>::value); //success
}
