/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ido
 *
 * Created on March 11, 2018, 6:08 PM
 */

#include <cstdlib>
#include <iostream>
#include <memory>

#include "factory.h"
#include "shape.h"
#include "circle.h"
#include "rectangle.h"

using namespace std;
using namespace ilrd;

/*
 * 
 */
void test();

int main (int argc, char** argv)
{
  
  test();
  return 0;
}

void test()
{
   std::shared_ptr<shape> s;
   factory <std::shared_ptr<shape> , std::string , int> f;  // crate a factory with a string key type
   
   f.registers ("circle" , circle::create );  // insert a circle type to the factory
   f.registers ("rectangle" , rectangle::create );  // // insert a rectangle type to the factory
   
   s = f.create ("circle", 5 );
   
   std::cout<<"\n" << s->draw ()<<"\n";
   
   //delete s;
}