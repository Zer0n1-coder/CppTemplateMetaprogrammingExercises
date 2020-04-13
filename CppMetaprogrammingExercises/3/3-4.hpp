#pragma once
#include <type_traits>

template<class F, class X>
struct apply1 :F::template apply<X>
{
	
};

template <class F, class X>
struct twice : apply1<F, typename apply1<F, X>::type>
{

};

struct add_pointer_f
{
	template <class T>
	struct apply : std::add_pointer<T> {};
};

struct twice1
{
	template <class T>
	struct apply : twice<add_pointer_f,T> {};
};

template <class T>
struct twice_self : twice<twice1, T>
{

};

void test3_4()
{
	static_assert(std::is_same<int****, twice_self<int>::type>::value); //success;
	static_assert(std::is_same<int**, twice_self<int>::type>::value);	//fail;
}
