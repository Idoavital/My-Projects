/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ido
 *
 * Created on February 12, 2018, 11:11 AM
 */

#include <cstdlib>
#include "bitArrayVector.h"

using namespace ilrd;

/*
 * 
 */
void testBitWise ();
void testShift ();

int main (int argc, char** argv)
{
  
  testBitWise();
  testShift ();

  return 0;
}

void testBitWise ()
{
  BitArray<300> b1;
  BitArray<300> b2;
  BitArray<300> b3;
  
  b1.setBit (70,true);
  b1.setBit (299,true);
  b1.setBit (2,true);
  b1.setBit (2,true);
  
  b2|=b1;
  
  if (b2==b1)
    {
      std::cout<<"test operator == success \n ";
    }
  else
     {
      std::cout<<"test operator == failed \n ";
    }
  
  b2&=b3;
  
  if (b2!=b1)
    {
      std::cout<<"test operator == success \n ";
    }
  else
     {
      std::cout<<"test operator == failed \n ";
    }

}

void testShift ()
{
    BitArray<220> b1;
    BitArray<300> b2;
    b1[1]=1;
    b1[0]=1;
    b2[3]=1;
    b1[7]=b2[3];
    
  
    std::cout<<"test [] = and count \n";
    if (b1.count() == 3)
      {
         std::cout<<"test success \n";
         std::cout<<"count - "<<b1.count ()<< "\n" ;
      }
    else
     {
         std::cout<<"test failed \n";
         std::cout<<"count - "<<b1.count ()<< "\n" ;
     }
    
    for(int i = 70 ; i >=50 ; --i)
    {

      b1[i] =1;
    }
    
    std::cout<<b1;
    std::cout<<"\n after  << 20\n";
    b1<<=20;
    std::cout<<"\n----------------------\n";

    std::cout<<"count - "<<b1.count ()<< "\n" ;
    std::cout<<"\n----------------------\n";

    std::cout <<b1;

    
}