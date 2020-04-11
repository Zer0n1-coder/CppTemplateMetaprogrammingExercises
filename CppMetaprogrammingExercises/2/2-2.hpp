#pragma once
#include <type_traits>

template<class Derived>
class polymorphic_downcast
{
public:
	template<class Base>
	polymorphic_downcast(Base) {}

	operator Derived*()
	{
		return nullptr;
	}
};

template<class Derived>
class polymorphic_downcast<Derived&>
{
public:
	template<class Base>
	polymorphic_downcast(Base& b) :_d(static_cast<Derived&>(b)) {}

	operator Derived&()
	{
		return _d;
	}

private:
	Derived& _d;
};

template<class Derived>
class polymorphic_downcast<Derived*>
{
public:
	template<class Base>
	polymorphic_downcast(Base* b) :_d(static_cast<Derived*>(b)) {}

	operator Derived*()
	{
		return _d;
	}

private:
	Derived* _d;
};

void test2_2()
{
	struct A {};
	struct B : A {};

	B b;
	A* a_ptr = &b;
	B* b_ptr = polymorphic_downcast<B*>(a_ptr);

	A& a_ref = b;
	B& b_ref = polymorphic_downcast<B&>(a_ref);
}