#pragma once
#include "3-4.hpp"

//my implementation of apply
template<class F, class A1, class = void>
struct apply;

template<template<class T> class F,class T, class A1>
struct apply<F<T>, A1>
{
	using type = typename F<A1>::type;
};

template<class F, class X>
struct twice_ : apply<F, apply<F, X>::type>
{

};

void test3_6()
{
	static_assert(std::is_same<int**, twice_<std::add_pointer<_1>, int>::type>::value); //succcess;
	static_assert(std::is_same<int*, twice_<std::add_pointer<_1>, int>::type>::value);	//fail;
}