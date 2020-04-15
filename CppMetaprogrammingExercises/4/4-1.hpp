#pragma once
#include <type_traits>

template<class V1,class V2>
struct logical_and
{
	static constexpr bool value = V1::value && V2::value;
};

template<class V1, class V2>
struct logical_or
{
	static constexpr bool value = V1::value || V2::value;
};



void test4_1()
{
	static_assert(logical_and<std::is_reference<int&>, std::is_reference<int>>::value);		//fail
	static_assert(logical_and<std::is_reference<int&>, std::is_reference<int&>>::value);	//success

	static_assert(logical_or<std::is_reference<int&>, std::is_reference<int>>::value);		//success
	static_assert(logical_or<std::is_reference<int&>, std::is_reference<int&>>::value);		//success
	static_assert(logical_or<std::is_reference<int>, std::is_reference<int>>::value);		//fail
}


