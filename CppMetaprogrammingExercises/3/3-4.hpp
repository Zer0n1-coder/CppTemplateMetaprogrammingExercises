#pragma once
#include <type_traits>

//implementation of placeholders
template<int N>
struct arg;

template<>
struct arg<1>
{
	template<class A1,class = std::void_t<>>
	struct apply
	{
		using type = A1;
	};
};

using _1 = arg<1>;

template<>
struct arg<2>
{
	template<class A1, class A2>
	struct apply
	{
		using type = A2;
	};
};

using _2 = arg<2>;

//implementation of the lambda metafunction
template<template<class T> class F>
struct fun_wrapper
{
	template<class X>
	struct apply : F<X>
	{
	};
};

template<class F>
struct lambda;

template<template<class T> class F>
struct lambda<F<_1>>
{
	using type = fun_wrapper<F>;
};

//twice
template<class F, class X>
struct apply1 :F::template apply<X>
{
	
};

template <class F, class X>
struct twice : apply1<F, typename apply1<F, X>::type>
{

};

struct twice1
{
	template <class T>
	struct apply : twice<lambda<std::add_pointer<_1>>::type,T> {};
};

template <class T>
struct twice_self : twice<twice1, T>
{

};

void test3_4()
{
	static_assert(std::is_same<int**, twice<lambda<std::add_pointer<_1>>::type,int>::type>::value); //success;
	static_assert(std::is_same<int****, twice_self<int>::type>::value);	//success;
	static_assert(std::is_same<int**, twice_self<int>::type>::value);	//fail;
}
