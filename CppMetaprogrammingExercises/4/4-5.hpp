#pragma once
#include <vector>
#include <type_traits>

template<class Predicate, class T1, class T2>
struct if_ : std::conditional<Predicate::value,T1,T2>
{
};

template<class Container,class Value>
auto container_find(Container& c, Value const& v)
->typename if_<std::is_const<Container>, typename Container::const_iterator, typename Container::iterator>::type
{
	return std::find(c.begin(), c.end(), v);
}


void test4_5()
{
	const std::vector<int> test1 = { 1,2,3,4,5 };
	std::vector<int> test2 = { 1,2,3,4,5 };
	auto result1 = container_find(test1, 2);
	auto result2 = container_find(test2, 2);
}
