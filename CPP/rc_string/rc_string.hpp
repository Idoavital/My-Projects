
/*
 * File:   rc_string.hpp
 * Author: ido
 *
 * Created on January 25, 2018,
 */

#ifndef RC_STRING_HPP
#define RC_STRING_HPP

#include <iostream>
#include <string.h>

namespace ilrd
{

class rc_proxy ;
 
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
 	String& operator = (const String& other_);

	// Get character of string
	rc_proxy operator[](size_t idx);
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
        
        // function for proxy class [] .
        String& ChengeChar (int index , char c);
        char & GetChar(int index);


private:
    struct RC_str ;
    
    void cleanUp();
    
    RC_str *m_rc_str;


};

// wrap the object with a class that overrides the operator=. 
//  This wrapper can then inform the store when the object has been updated.    
class rc_proxy 
{
public:
    rc_proxy(String& s , char c, int  i): m_string (s) ,m_char (c) ,index (i)
    {
    }
    // When assignment is done assign
     rc_proxy& operator=(char ch)
     {
         m_char= ch;
         m_string.ChengeChar(index, ch);
         return *this;
     }
     
     // Still allow the base object to be read
    // From within this wrapper.
    operator char const&()
    {
        return m_char;
    } 
    
    rc_proxy& operator= (rc_proxy& other_)
    {
        this->m_char=other_.m_char;
        return *this;
    }
private:
    String& m_string;
    char  m_char;
    size_t  index;
    
};

}

#endif /* RC_STRING_HPP */
