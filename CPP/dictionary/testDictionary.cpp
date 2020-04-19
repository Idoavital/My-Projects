#include <iostream>
#include <fstream>      // std::ifstream
#include <string.h>		//strchr


#include "dictionary.hpp"


#define PRINT_ERROR(msg) 	         						  \
do{                              	 	 					  \
	std::cout << ""RED"" << __FILE__<< ":" << __LINE__ << 	  \
	":"<< msg << "\n"RESET"";							  	  \
	++errors;        										  \
}while(0)

#define RED   "\x1b[1m\x1b[31m "
#define BOLD  "\x1b[1m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b	33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
using namespace ilrd;

void BasicTest();
void DictionaryTest();

size_t errors = 0;

int main()
{
	BasicTest();
	DictionaryTest();


	if(errors == 0)
	{
		std::cout << ""GREEN"Finished dictionary testing - no errors\n"RESET"";
	}
	else
	{
		std::cout << ""RED"Finished dictionary testing with " <<  errors <<
		" errors\n"RESET"";
	}

	return (0);
}



inline void PrintError(const char *str)
{

	std::cout << ""RED"" << __FILE__<< ":" << __LINE__ << ":"<< str <<
	"\n"RESET"";
	++errors;

}


void BasicTest()
{
	Dict dict;

	if ((dict.Count() != 0) || (dict.Contains("a") != 0))
	{
		PRINT_ERROR("count empty trie error");
	}

	//inserting first word 'a'
	if (dict.Insert("a") != 0)
	{
		PRINT_ERROR("insert error error");
	}

	if ((dict.Count() != 1) || (dict.Contains("a") != 1)
		|| (dict.Contains("A") != 1)|| (dict.Contains("aa") != 0))
	{
		PRINT_ERROR("after inserting 'a' error- count or contain");
		std::cout << "count: " << dict.Count() << std::endl;
		std::cout << "contain A: " << dict.Contains("A") << std::endl;
	}
	//inserting second word 'aa'
	if (dict.Insert("aa") != 0)
	{
		PRINT_ERROR("insert error");
	}

	if ((dict.Count() != 2) || (dict.Contains("a") != 1)
		|| (dict.Contains("aa") != 1) || (dict.Contains("ab") != 0)
		|| (dict.Contains("AA") != 1))
	{
		PRINT_ERROR("after inserting error- count or contain");
		std::cout << "count: " << dict.Count() << std::endl;
		std::cout << "contain a: " << dict.Contains("a") << std::endl;
		std::cout << "contain aa: " << dict.Contains("aa") << std::endl;
	}
	//inserting  'AAB'
	if (dict.Insert("AAB") != 0)
	{
		PRINT_ERROR("insert error");
	}

	if ((dict.Count() != 3) || (dict.Contains("a") != 1)
		|| (dict.Contains("aa") != 1) || (dict.Contains("ab") != 0)
		|| (dict.Contains("aab") != 1) || (dict.Contains("AAB") != 1))
	{
		PRINT_ERROR("after inserting error- count or contain");
		std::cout << "count: " << dict.Count() << std::endl;
		std::cout << "contain a: " << dict.Contains("a") << std::endl;
		std::cout << "contain aa: " << dict.Contains("aa") << std::endl;
	}
	//inserting  'zzAA'
	if (dict.Insert("zzAA") != 0)
	{
		PRINT_ERROR("insert error");
	}

	if ((dict.Count() != 4) || (dict.Contains("a") != 1)
		|| (dict.Contains("aa") != 1) || (dict.Contains("ab") != 0)
		|| (dict.Contains("zzAA") != 1) || (dict.Contains("AAB") != 1))
	{
		PRINT_ERROR("after inserting error- count or contain");
		std::cout << "count: " << dict.Count() << std::endl;
		std::cout << "contain a: " << dict.Contains("a") << std::endl;
		std::cout << "contain aa: " << dict.Contains("aa") << std::endl;
	}

	//inserting  'zzAA'
	if (dict.Insert("zz'A") != 1)
	{
		PRINT_ERROR("insert ilagel error");
	}

	if ((dict.Count() != 4) || (dict.Contains("a") != 1)
		|| (dict.Contains("aa") != 1) || (dict.Contains("ab") != 0)
		|| (dict.Contains("zzAA") != 1) || (dict.Contains("AAB") != 1))
	{
		PRINT_ERROR("after inserting error- count or contain");
		std::cout << "count: " << dict.Count() << std::endl;
		std::cout << "contain a: " << dict.Contains("a") << std::endl;
		std::cout << "contain aa: " << dict.Contains("aa") << std::endl;
	}

	//removing  'zzAA'
	if (dict.Remove("zzAA") != 0)
	{
		PRINT_ERROR("remove error");
	}

	if ((dict.Count() != 3) || (dict.Contains("a") != 1)
		|| (dict.Contains("aa") != 1) || (dict.Contains("ab") != 0)
		|| (dict.Contains("zzAA") != 0) || (dict.Contains("AAB") != 1))
	{
		PRINT_ERROR("after removing error- count or contain");
		std::cout << "count: " << dict.Count() << std::endl;
		std::cout << "contain a: " << dict.Contains("a") << std::endl;
		std::cout << "contain aa: " << dict.Contains("aa") << std::endl;
	}

	//removing  'a'
	if (dict.Remove("a") != 0)
	{
		PRINT_ERROR("remove error");
	}

	if ((dict.Count() != 2) || (dict.Contains("a") != 0)
		|| (dict.Contains("aa") != 1) || (dict.Contains("ab") != 0)
		|| (dict.Contains("dfhj") != 0) || (dict.Contains("AAB") != 1))
	{
		PRINT_ERROR("after removing error- count or contain");
		std::cout << "count: " << dict.Count() << std::endl;
		std::cout << "contain ab: " << dict.Contains("ab") << std::endl;
		std::cout << "contain AAB: " << dict.Contains("AAB") << std::endl;
	}

}


void DictionaryTest()
{
	Dict dict;

	std::ifstream is ("/usr/share/dict/words", std::ifstream::binary);
	if (is) {
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    char* buffer = new char [length];
    char* buffer_start = buffer;
    std::cout << "Reading " << length << " characters... ";
    // read data as a block:
    is.read (buffer,length);

    if (is)
      std::cout << "all characters read successfully.\n";
    else
      std::cout << "error: only " << is.gcount() << " could be read";


    // ...buffer contains the entire file...

	while (buffer > (buffer_start + length))
	{
		std::cout << "eof: " << is.eof() << std::endl;
		char *start_word = buffer;
		size_t count = 0;

		buffer = strchr(buffer, '\n');
		*buffer = '\0';
		++buffer;

		std::cout << start_word << std::endl;
		if (dict.Insert(start_word) != 0)
		{
			PRINT_ERROR("insert error");
		}
		else
		{
			++count;
			if ((dict.Count() != count) || (dict.Contains(start_word) != 1))
			{
				PRINT_ERROR("after inserting to dict error- count or contain");
			}
		}


	}


	is.close();
    delete[] buffer;
}}
