#pragma once
#include <type_traits>

template<class N1,class N2>
struct and_ : std::bool_constant<N1::value && N2::value>
{

};

template<class N>
struct not_ : std::bool_constant<!N::value>
{

};

template<class T>
struct is_data_member_pointer : 
	and_<std::is_member_pointer<T>, not_<std::is_member_function_pointer<T>>>
{

};

template<class T>
struct is_function_pointer : 
	and_<std::is_pointer<T>, std::is_function<std::remove_pointer<T>::type>>
{

};

template<class T>
struct is_reference_to_function_pointer : 
	and_<std::is_reference<T>, is_function_pointer<std::remove_reference<T>::type>>
{

};

template<class T>
struct is_reference_to_non_const : 
	and_<std::is_reference<T>,not_<std::is_const<std::remove_reference<T>::type>>>
{

};

void test4_4()
{
	struct A
	{
		int a;
		int fun(int){}
	};

	static_assert(is_data_member_pointer<int*>::value);
	static_assert(is_data_member_pointer<int A::*>::value);
	static_assert(is_data_member_pointer<int (A::*)(int)>::value);

	static_assert(is_function_pointer<int*>::value);
	static_assert(is_function_pointer<int (A::*)(int)>::value);
	static_assert(is_function_pointer<int (*)(int)>::value);

	using Fun = int(*)(int);
	static_assert(is_reference_to_function_pointer<Fun&>::value);
	static_assert(is_reference_to_function_pointer<int&>::value);

	static_assert(is_reference_to_non_const<Fun&>::value);
	static_assert(is_reference_to_non_const<int&>::value);
	static_assert(is_reference_to_non_const<const Fun&>::value);
	static_assert(is_reference_to_non_const<const int&>::value);
}