/******************************************************************************
 ******************************* Libaries *************************************
 ******************************************************************************/

#include <iostream> /* size_t, cout, cin 									  */

#include "SharedPtr.hpp"

using namespace ilrd;

/******************************************************************************
 ********************* MACROS & Global Const Variables ************************
 ******************************************************************************/

#define PRINT_ERROR(x) (std::cout << ""RED << __FILE__ << ": " \
								  << __LINE__ << "->" << #x <<""RESET"\n")

/* Colors */
#define BOLD  "\x1b[1m"
#define RED   "\x1b[1m\x1b[31m "
#define GREEN "\x1b[1m\x1b[32m "
#define RESET " \x1b[0m"

/******************************************************************************
 *************************** FUNCS DECLARATIONS *******************************
 ******************************************************************************/

void BasicTest();

/******************************* Base Class ***********************************/
class Base
{
	public:
		int m_a;
		int *m_b;

		Base();
		~Base();
		int foo() const;
};

Base::Base() : m_a(10), m_b(new int(11))
{
  std::cout<<"Ctor Base\n";
}

Base::~Base()
{
         std::cout<<"Dtor Base\n";
	delete m_b;
}

int Base::foo() const
{
	return (12);
}

class Derived : public Base
{
	public:
		Derived();

		int m_derived;
};

/****************************** Derived Class *********************************/
Derived::Derived(): m_derived(300)
{}

class Base2
{
	public:
		int *m_b2;

		Base2();
		~Base2();
};


Base2::Base2() : m_b2(new int(1111))
{}

Base2::~Base2()
{
	delete m_b2;
}
/******************************************************************************
 ********************************** MAIN **************************************
 ******************************************************************************/

int main(int argc, char *argv[])
{
	BasicTest();
	return (0);
}

void BasicTest()
{
	size_t failure_status =  0;
	SharedPtr<int> sp1;
	SharedPtr<int> sp2(0);
	SharedPtr<int> sp3(new int(5));

	if ((*sp3 != 5) || (5 != *sp3))
	{
		PRINT_ERROR("((*sp3 != 5) || (5 != *sp3))");
		++failure_status;
	}

	*sp3 = 3;
	if (*sp3 != 3)
	{
		PRINT_ERROR("*sp3 = 3;");
		++failure_status;
	}

	SharedPtr<Base> sp_test(new Base());
	if ((sp_test->m_a != 10)   || (10 != sp_test->m_a)    ||
		(*(sp_test->m_b) != 11) || (sp_test->foo() != 12) ||
		((*(sp_test)).foo() != 12))
	{
		PRINT_ERROR("->/* operators against class test");
		++failure_status;
	}

	// If compiler said error, congrutulations! remove the line! :)
	//(*sp_test).foo() = 3;

	sp_test->m_a *= 2;
	*(sp_test->m_b) *= 2;
	if ((sp_test->m_a != 20) ||(*(sp_test->m_b) != 22))
	{
		PRINT_ERROR("assignment with ->/* operators");
		++failure_status;
	}

	if (((!sp1) != true) || ((!sp2) != true) || ((!sp3) != false))
	{
		PRINT_ERROR("! operator");
		++failure_status;
	}

	// Valgrind test: Check the valgrind...
	sp1 = sp3;
	sp2 = sp3;

	SharedPtr<int> sp4;
	sp1 = sp4;
	sp2 = sp4;

	SharedPtr<Base> sp_base(new Base());
	SharedPtr<Derived> sp_derived(new Derived());

	sp_base = sp_derived;

	// If compiler said error, congrutulations! remove the lines! :)
	//SharedPtr<Base2> sp_base2(new Base2());
	//sp_base = sp_base2;
	//sp_base2 = sp_base;


	// If compiler said error, congrutulations! remove the line! :)
	sp_derived = sp_base;

	if (!failure_status)
	{
		std::cout << GREEN"Basic test: passed; \n"RESET;
	}
}
