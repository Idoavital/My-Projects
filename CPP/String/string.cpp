

#include "string.hpp"


namespace ilrd
{

static char * init(const char * str_1 )
{
    size_t len = strlen(str_1)+1 ;
    char * str_temp = new char[len];
    memcpy(str_temp , str_1 , len);

    return str_temp;
}



//default constructor
String::String(const char *str )
{
    m_str =init(str); //add 1 more cell for the '\0'
}


String::~String()
{
    delete[] m_str;
}


String::String(const String &other_): m_str (init(other_.m_str)) //copy constructor
{
}

/*************** Assigment operator*******************/

String& String::operator = (String other_)
{
    std::swap (m_str , other_.m_str);

    return *this;
}

// Get character of string
char&  String::operator[](size_t idx)
{
    return m_str[idx];
}

const char& String::operator[] (size_t idx) const
{
    return m_str[idx];
}

// Return length of string
	size_t String::Length() const
	{
	    return strlen(m_str);
	}

bool operator == (const String& lhs, const String& rhs)
{
    return (strcmp (lhs.m_str, rhs.m_str) == 0);
}

bool operator != (const String& lhs, const String& rhs)
{
    return (!(lhs == rhs));
}

std::ostream& operator << (std::ostream& os_, const String& str)
{
    return os_<<str.m_str;
}


String & String::operator += (String s1)
{
    char* temp= new char [ s1.Length() + this->Length() +1];
    memcpy (temp ,this->m_str, this->Length() );
    memcpy (temp+this->Length() ,s1.m_str, s1.Length()+1 );
    *this = temp;
    
    return *this;
}
 String operator + (String s1 , String s2)
 {
     return (s1+=s2);
 }
 
}