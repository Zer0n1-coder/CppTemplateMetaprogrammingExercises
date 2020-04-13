#pragma once
#include <type_traits>

template<class F,class X>
struct apply1:F::template apply<X>
{

};

template <class F, class X>
struct twice : apply1<F,typename apply1<F,X>::type>
{

};

struct add_pointer_f
{
	template <class T>
	struct apply : std::add_pointer<T> {};
};

template <class T>
struct twice2 : twice<add_pointer_f,typename twice<add_pointer_f,T>::type>
{ 

};

void test3_3()
{
	static_assert(std::is_same<int****, twice2<int>::type>::value); //success;
	static_assert(std::is_same<int**, twice2<int>::type>::value);	//fail;
}
