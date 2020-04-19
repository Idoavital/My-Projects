/*
 * rc_string
 * implement our on string class with a lazy copy.
 * and only when we need to write to tha data we
 * allocte a new memory and copy the origenal data if need.
 */
#include <cstddef>     /* offsetof */
#include "rc_string.hpp"

namespace ilrd
{
    

struct String::RC_str
{
public:
    static String::RC_str * init(const char * str_1 ); 
    size_t m_counter;
    char m_str[1]; // fixable array
private:
  
    RC_str(const char* str);
};

/************ struct constructor and functoin ***********************/
 String::RC_str::RC_str(const char * str)
 {
    size_t len = strlen(str)+1 ;
    memmove (m_str ,str, len );   // copy the string from user
    m_counter = 1;     // initialize the counter;
 }

 
String::RC_str * String::RC_str::init(const char * str_1 )
{
    
    //add 1 more cell for the '\0'
    size_t len = strlen(str_1)+1 ;
    size_t ofset = offsetof(String::RC_str, m_str);
    void * temp = operator new (len+ ofset);

    return ( new (temp) RC_str(str_1)) ;
}

/************** class String ****************************/
//default constructor
String::String(const char *str ):m_rc_str (String::RC_str:: init(str))
{

}

String::~String()
{
  this->cleanUp();
}

void String::cleanUp()
{
  if (this->m_rc_str->m_counter >1 )
    {
        this->m_rc_str->m_counter--;
    }
  else
    {
      delete m_rc_str;
    }
}

/* copy on write */
/* copy only the pointer to the string  */
String::String(const String &other_) //copy constructor
{
  this->m_rc_str = other_.m_rc_str;
  this->m_rc_str->m_counter++;

}

/*************** Assigment operator*******************/

/*create a copy of a data */
String& String::operator=(const String &other_)
{

    /*check if the object data pointed only by the oblect himself
    , if the objest is a single pionter , delete the data and create a new one  */
    if (&other_ != this)
    {
        this->cleanUp();
        this->m_rc_str = other_.m_rc_str;
        this->m_rc_str->m_counter++;
    }
    
    return *this;
}

// Get character of string
rc_proxy String::operator[](size_t idx)
{
    return rc_proxy(*this , m_rc_str->m_str[idx], idx);
}

const char& String::operator[] (size_t idx) const
{
     return m_rc_str->m_str[idx];
}

// Return length of string
	size_t String::Length() const
	{
	   return strlen(m_rc_str->m_str);
	}

bool operator == (const String& lhs, const String& rhs)
{
    return (strcmp (lhs. m_rc_str->m_str, rhs. m_rc_str->m_str) == 0);
}

bool operator != (const String& lhs, const String& rhs)
{
   return (!(lhs == rhs));
}

std::ostream& operator << (std::ostream& os_, const String& str)
{
   return os_<<(str.m_rc_str->m_str);
}


char & String::GetChar(int index)
{
    return m_rc_str->m_str[index];
}

String& String::ChengeChar (int index , char chr)
{
    
   if (this->m_rc_str->m_counter > 1)
    {
     
        RC_str *temp= String::RC_str::init(this->m_rc_str->m_str);
        this->m_rc_str->m_counter--;
        this->m_rc_str = temp;
    }
   
    this->m_rc_str->m_str[index]= chr ;
    return *this;
}
/*
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
 */

}
