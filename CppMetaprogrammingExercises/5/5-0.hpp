#pragma once
#include <type_traits>

template<int N>
using int_constant = std::integral_constant<int, N>;

template<class N>
struct next_c;

template<int N>
struct next_c<int_constant<N>>
{
	using type = int_constant<N + 1>;
};

template<class N>
struct prior_c;

template<int N>
struct prior_c<int_constant<N>>
{
	using type = int_constant<N - 1>;
};

//none
struct none{};

//tiny
template<class T0 = none,class T1 = none,class T2 = none>
struct tiny
{
	using t0 = T0;
	using t1 = T1;
	using t2 = T2;
};

template<class Tiny,class Pos>
struct tiny_iterator
{
};

template<class Iterator>
struct next_;

template<class Tiny, class Pos>
struct next_<tiny_iterator<Tiny, Pos>>
{
	using type = tiny_iterator<Tiny, next_c<Pos>>;
};

template<class Iterator>
struct prior_;

template<class Tiny, class Pos>
struct prior_<tiny_iterator<Tiny, Pos>>
{
	using type = tiny_iterator<Tiny, prior_c<Pos>>;
};

template<class Tiny,int N>
struct tiny_at;

template<class Tiny>
struct tiny_at<Tiny, 0>
{
	using type =typename Tiny::t0;
};

template<class Tiny>
struct tiny_at<Tiny, 1>
{
	using type = typename Tiny::t1;
};

template<class Tiny>
struct tiny_at<Tiny, 2>
{
	using type = typename Tiny::t2;
};

template<class Tiny,class Pos>
struct at_;

template<class T0,class T1,class T2, class Pos>
struct at_<tiny<T0, T1, T2>, Pos>:tiny_at<tiny<T0, T1, T2>,Pos::value>
{

};

template<class Iterator>
struct deref;

template<class Tiny, class Pos>
struct deref<tiny_iterator<Tiny, Pos>> :at_<Tiny, Pos>
{

};

template<class Tiny>
struct begin_
{
	using type = tiny_iterator<Tiny, int_constant<0>>;
};

template<class Tiny>
struct end_;

template<class T0>
struct end_<tiny<T0, none, none>>
{
	using type = tiny_iterator<tiny<T1, none, none>, int_constant<1>>;
};

template<class T0, class T1>
struct end_<tiny<T0, T1, none>>
{
	using type = tiny_iterator<tiny<T1, none, none>, int_constant<2>>;
};

template<class T0, class T1, class T2>
struct end_<tiny<T0, T1, T2>>
{
	using type = tiny_iterator<tiny<T1, none, none>, int_constant<3>>;
};

template<class Tiny>
struct size_;

template<>
struct size_<tiny<none, none, none>> :int_constant<0>
{

};

template<class T0>
struct size_<tiny<T0, none, none>> :int_constant<1>
{

};

template<class T0, class T1>
struct size_<tiny<T0, T1, none>> :int_constant<2>
{

};

template<class T0, class T1,class T2>
struct size_<tiny<T0, T1, T2>> :int_constant<3>
{

};

void test5_0()
{
	static_assert(std::is_same<int_constant<0>,size_<tiny<>>::type>::value);
	static_assert(std::is_same<int_constant<1>, size_<tiny<int>>::type>::value);
	static_assert(std::is_same<int_constant<2>, size_<tiny<int,float>>::type>::value);
	static_assert(std::is_same<int_constant<3>, size_<tiny<int, float,double>>::type>::value);

	static_assert(std::is_same<int, deref<begin_<tiny<int, float, double>>::type>::type>::value);
	static_assert(std::is_same<int, at_<tiny<int, float, double>,int_constant<0>>::type>::value);
	static_assert(std::is_same<float, at_<tiny<int, float, double>, int_constant<1>>::type>::value);
	static_assert(std::is_same<double, at_<tiny<int, float, double>, int_constant<2>>::type>::value);
}