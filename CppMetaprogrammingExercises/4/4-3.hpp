#pragma once
#include <type_traits>

//my implementation of if_ for question1
template<class Predicate,class T1,class T2>
struct if_ : std::conditional<Predicate::value, T1, T2>
{
};

template<class N>
struct next_
{
	using type = N;
};

//question1
template<class N,class Predicate>
struct next_if : if_<apply<Predicate,N>, next_<N>,N>
{
};

//my implementation of not_equal_to_ for question2
template<class N1,class N2>
struct not_equal_to_ : bool_constant<!N1::value == N2::value>
{
};

//my implementation of minus_ for question2
template<class N1,class N2>
struct minus_ :integral_constant<int, N1::value - N2::value>
{
};

//my implementation of greater_ for question2
template<class N1, class N2>
struct greater_:bool_constant<N1::value > N2::value >
{
};

//my implementation of plus_ for question2
template<class N1, class N2>
struct plus_:integral_constant<int, N1::value + N2::value>
{
};

//my implementation of multiplies_ for question2
template<class N1, class N2>
struct multiplies_:integral_constant<int, N1::value * N2::value>
{
};

//question2
template<class N1,class N2>
struct formula : if_<
	not_equal_to_<N1, N2>,
	if_<greater_<N1,N2>,minus_<N1,N2>,N1>,
	plus_<N1,multiplies_<N1,integral_constant<int,2>>>>
{

};