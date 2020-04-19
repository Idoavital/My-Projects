/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ex30.cpp
 * Author: stav
 *
 * Created on January 30, 2018, 11:05 AM
 */

#include <stdlib.h>
#include <iostream>


/*
 * Simple C++ Test Suite
 */


class X
{
public:
  X()
  {
        std::cout<<"x Ctor :"<<this <<std::endl;
  }
   virtual ~X(){
    std::cout<<"x Dtor :"<<this <<std::endl;
  }
private:
  double m_a;
  
};

class Y: public X
{
public:
  
  Y()
  {
        std::cout<<"y Ctor :"<<this <<std::endl;
  }
  ~Y()
  {
    std::cout<<"y Dtor :"<<this <<std::endl;
  }
private:
  int m_b;
};


void Foo(X x)
{
  std::cout<<"foo "<<std::endl;
}


#if 0
int main (int argc, char** argv)
{
  
  X* xp= new Y[4];
  std::cout<<"size x "<<sizeof(X)<<std::endl;
  std::cout<<"size y " <<sizeof(Y)<<std::endl;
  delete [] xp;
  
 
  Y y1;
  Foo(y1);

  return (EXIT_SUCCESS);
}

#endif