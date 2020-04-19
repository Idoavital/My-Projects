#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <iostream>
#include <string.h>

namespace ilrd
{

/******************************************************************************
 ****************************** STRING CLASS **********************************
 ******************************************************************************/

class String
{
public:

	// Constructors
	String(const char *str = "");
	String(const String &other_); //copy constructor

	// Destructor
	~String();

	// Assigment operator
 	String& operator = (const String other_);

	// Get character of string
	char& operator[](size_t idx);
	const char &operator[] (size_t idx) const;

	// Return length of string
	size_t Length() const;

	// Relational Operators
	friend bool operator != (const String& lhs, const String& rhs);
	friend bool operator == (const String& lhs, const String& rhs);

	// Insert string into stream
	friend std::ostream& operator << (std::ostream& os_, const String& str);
        
        String& operator += (String s1);
        friend String operator + (String s1 , String s2);
       

private:

	char *m_str;
};

}


#endif /* __STRING_HPP__ */
