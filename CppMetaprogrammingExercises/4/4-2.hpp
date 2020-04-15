#pragma once
#include <type_traits>

template<class V,class...Values>
struct logical_and
{
	static constexpr bool value = V::value && logical_and<Values...>::value;
};

template<class V>
struct logical_and
{
	static constexpr bool value = V::value;
};

template<class V, class...Values>
struct logical_or
{
	static constexpr bool value = V::value || logical_and<Values...>::value;
};

template<class V>
struct logical_or
{
	static constexpr bool value = V::value;
};

void test4_2()
{
	static_assert(logical_and<
		std::is_reference<int&>, 
		std::is_reference<int>, 
		std::is_reference<int>, 
		std::is_reference<int&>,
		std::is_reference<int&>>::value);		//fail

	static_assert(logical_and<
		std::is_reference<int&>,
		std::is_reference<int&>,
		std::is_reference<int&>,
		std::is_reference<int>,
		std::is_reference<int>>::value);		//fail

	static_assert(logical_or<
		std::is_reference<int&>,
		std::is_reference<int&>,
		std::is_reference<int&>,
		std::is_reference<int&>,
		std::is_reference<int&>>::value);		//success

	static_assert(logical_or<
		std::is_reference<int&>,
		std::is_reference<int&>,
		std::is_reference<int>,
		std::is_reference<int>,
		std::is_reference<int>>::value);		//success

	static_assert(logical_or<
		std::is_reference<int>,
		std::is_reference<int>,
		std::is_reference<int>,
		std::is_reference<int>,
		std::is_reference<int>>::value);		//fail
}