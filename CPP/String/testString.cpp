/******************************************************************************
 ******************************* Libaries *************************************
 ******************************************************************************/
#include <iostream> /* size_t, cout, cin 									  */
//#include <fstream>  /* ofstream, open(), close(), good(), eof()				  */
#include <string>   /* getline() 											  */

#include "string.hpp"

using namespace ilrd;

/******************************************************************************
 ********************* MACROS & Global Const Variables ************************
 ******************************************************************************/

/* Colors */
#define BOLD  "\x1b[1m"
#define RED   "\x1b[1m\x1b[31m "
#define GREEN "\x1b[1m\x1b[32m "
#define RESET " \x1b[0m"

/******************************************************************************
 *************************** FUNCS DECLARATIONS *******************************
 ******************************************************************************/
void BasicTestStringClass();
void CheckConstness(const String &obj);

/******************************************************************************
 ********************************** MAIN **************************************
 ******************************************************************************/

int main(int argc, char *argv[])
{
    
    String s1 = "ido";
    String s2 = "lolo";
        
     s2+=s1;
     s2 = s2 + s1;
        
     
     std::cout <<"test operator += and operator + \n ***" << s2 << std::endl;
     
	BasicTestStringClass();
	return (0);
}


void BasicTestStringClass()
{
	String str1;
	String str2("Hello");
	String str3(str2);
	String str4;
        
        
        

	size_t failure_status =  0;

	// Default constructor with "" string
	if (str1.Length() != 0)
	{
		std::cout << RED"(1.1) Error: str1.Length() should be zero (recieved: "
				  << str1.Length() << ")\n"RESET;
		++failure_status;
	}

	// Default constructor with initial string
	if (str2.Length() != 5)
	{
		std::cout << RED"(1.2) Error: str2.Length() should be 5 (recieved: "
				  << str2.Length() << ")\n"RESET;
		++failure_status;
	}

	// CCtor
	if (str3.Length() != 5)
	{
		std::cout << RED"(1.3) Error: str3.Length() should be 5 (recieved: "
				  << str3.Length() << ")\n"RESET;
		++failure_status;
	}

	// Assignment operators:
	// 1. Object assigment
	str1 = str2;
	if (str1.Length() != 5)
	{
		std::cout << RED"(1.4) Error: str1.Length() should be 5 (recieved: "
				  << str1.Length() << ")\n"RESET;
		++failure_status;
	}

	// 2. String assigment
	str4 = "Hello again";
	if (str4.Length() != 11)
	{
		std::cout << RED"(1.5) Error: str4.Length() should be 11 (recieved: "
				  << str4.Length() << ")\n"RESET;
		++failure_status;
	}

	// // Operator []: Get character of string
	str4[0] = ' ';
	if (str4[0] != ' ')
	{
		std::cout << RED"(2.1) Error: str4[0] = ' ';\n"RESET;
		++failure_status;
	}

	str4[0] = 'H';
	if (str4[5] == 'a')
	{
		std::cout << RED"(2.2) Error: (str4[5] == 'a');\n"RESET;
		++failure_status;
	}

	// Relational Operators
	if (str3 != str2)
	{
		std::cout << RED"(3.1) Error: (str3 != str2);\n"RESET;
		++failure_status;
	}

	if (str1 == str4)
	{
		std::cout << RED"(3.2) Error: (str1 == str4);\n"RESET;
		++failure_status;
	}

	// Check self-assignment
	str4 = str4;
	if (str4.Length() != 11)
	{
		std::cout << RED"(4.1) Error: str4.Length() should be 11 (recieved: "
				  << str4.Length() << ")\n"RESET;
		++failure_status;
	}

	// You suppose to fail on this test; if so, remove the line within the func.
	CheckConstness(str4);

	// Insert string into stream
	std::cout << str1 << std::endl;
	std::cout << str4 << std::endl;


	if (!failure_status)
	{
		std::cout << GREEN"String Basic test: passed; \n"RESET;
	}

}

void CheckConstness(const String &obj)
{
	// You suppose to fail on this test; if so, remove the line
//	obj[0] = 'a';
}







