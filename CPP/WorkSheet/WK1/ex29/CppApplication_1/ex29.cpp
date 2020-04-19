/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ido
 *
 * Created on January 29, 2018, 10:44 AM
 */
#include <iostream>
#include <cstdlib>

using namespace std;

class B
{
public :
  B(int a_ =8 ):m_a(a_)
  {
    cout<<"B::Ctor"<<endl;
  }
  virtual ~B()
  {
    cout<<"B::Dtor"<<endl;
  }
  
  virtual void Print1()  const{cout<<"B::Print1 B::m_a - "<<m_a<<endl;}
  virtual void Print2() const{cout<<"B::Print2  "<<endl;}
  virtual void Print3() const{cout<<"B::Print3  "<<endl;}
private:
  int m_a;
};

class X: public B
{
public:
  X():m_b(0)
  {
    cout<<"x:: Ctor"<<endl;
  }
  ~X()
  {
    cout<<"x:: Dtor"<<endl;
  }
  virtual void Print1() const{cout<<"X::Print1 B::m_B - "<<m_b<<endl;}
  virtual void Print2() const{cout<<"X::Print2  "<<endl;}
private:
  int m_b;
};
/*
 * 
 */

int main(int argc, char** argv) 
{
    B* b1 = new B;
    B* b2 = new X;
    
    
    cout<<endl<<"main b1:"<<endl;
    b1->Print1 ();
    b1->Print2();
    b1->Print3 ();
    
    cout<<endl<<"main b2:"<<endl;
    b2->Print1 ();
    b2->Print2 ();
    b2->Print3 ();
    
    X* xx= static_cast<X*>(b2);
    cout<<endl<<"main xx:"<<endl;
    xx->Print2 ();
    b2->Print2 ();
    
    delete b1;
    delete b2;
    
    return 0;
}

