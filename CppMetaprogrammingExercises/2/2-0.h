#pragma once
#include <type_traits>

template<bool Is_Ref, class T>
struct _add_const_ref
{
	using type = T;
};

template<class T>
struct _add_const_ref<true, T>
{
	using type = T;
};

template<class T>
struct _add_const_ref<false, T>
{
	using type = const T&;
};

template<class T>
struct add_const_ref:_add_const_ref<std::is_reference_v<T>,T>
{
};

//test
void test2_0()
{
	static_assert(std::is_same_v<const int&, add_const_ref<int>::type>);		//success
	static_assert(std::is_same_v<const int&, add_const_ref<int&>::type>);		//fail
	static_assert(std::is_same_v<const int&, add_const_ref<const int&>::type>); //success
	static_assert(std::is_same_v<int&, add_const_ref<int&>::type>);				//success
	static_assert(std::is_same_v<const int&, add_const_ref<const int>::type>);	//success
}



