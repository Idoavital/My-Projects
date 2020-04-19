/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: stav
 *
 * Created on March 7, 2018, 9:37 AM
 */

#include <cstdlib>
#include <iostream>
#include "singleTon.h"



using namespace std;

using namespace ilrd;

/*
 * 
 */

/******************************************************************************/
/*********************class test     ******************************************/
class test
{
public:
 
  void print()
  {
    std::cout<< m_x ;
  }
  int add(int num)
  {
    m_x+=num;
    return (m_x);
  }
private:
  friend class singleTon<test>;
  
  test(int x = 0):m_x(x){};
  int m_x;
};
/******************************************************************************/
/**********************    main    ********************************************/

int main (int argc, char** argv)
{
  //test t1; // not pass compailtion
  
    {
       singleTon<test> s;
       s->add (3);
    }
    
   singleTon<test> s1;
   s1->print ();
   std::cout<<s1->add (3)<<"\n";
  
  
  return 0;
}
