#pragma once
#include <type_traits>

template<class T, class = void> 
struct add_T_function_pointer_T		//para is T,ret is T
{
	using type = T;
};

template<class T>
struct add_T_function_pointer_T<T, std::void_t<T(*)(T)>>
{
	using type = T(*)(T);
};

//replaces all occurrences of a type x within c with y
template<class C, class X, class Y>
struct replace_type							
{										
	using type = void;
};

template<class T, class Y>
struct replace_type<typename std::add_pointer<T>::type, T, Y>
{
	using type = typename std::add_pointer<Y>::type;
};

template<class T, class Y, size_t s>
struct replace_type<T*[s], T, Y>		
{
	using type = Y * [s];
};

template<class T, class Y>
struct replace_type<typename add_T_function_pointer_T<T>::type, T, Y>
{
	using type = typename add_T_function_pointer_T<Y>::type;
};

void test2_1()
{
	static_assert(std::is_same_v<int*, replace_type<void*, void, int>::type>);
	static_assert(std::is_same_v<long*[10], replace_type<const int*[10], const int, long>::type>);
	static_assert(std::is_same_v<long& (*)(long&), replace_type<char& (*)(char&), char&, long&>::type>);
}