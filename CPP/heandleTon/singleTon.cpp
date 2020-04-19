/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 #include <cstdlib>
 #include <iostream>

 #include "singleTon.h"
 #include "test.h"

 using namespace ilrd;

 extern "C" void add4to()

{
   singleTon<test> so;
   std::cout << "in shared object singleTon  befor  +4: "<< so->print() << std::endl;
   std::cout << "in shared object singleTon  after +4: "<<so->add(4)  << std::endl;

}
