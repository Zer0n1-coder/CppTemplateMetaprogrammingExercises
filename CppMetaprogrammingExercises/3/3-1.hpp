#pragma once

template<int N>
struct int_
{
	static const int value = N;
};

template<class T,int N, int...Ns>
struct vector_c : vector_c<T, Ns>
{
	using type = typename T;
	static const int value = N;
};

template<class T, int N>
struct vector_c
{
	using type = typename T;
	static const int value = N;
};
