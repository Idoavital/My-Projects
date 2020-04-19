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
#include <dlfcn.h>

#include "singleTon.h"
#include "test.h"

using namespace std;
using namespace ilrd;

int main (int argc, char** argv)
{
  // open the library
   void* handle = dlopen("./singleTon.so", RTLD_LAZY);

   if (!handle) {
       cerr << "Cannot open library: " << dlerror() << '\n';
       return 1;
   }
    //load the symble
  typedef void (*add_t)();
  dlerror();
  add_t so_add =  (add_t) dlsym (handle, "add4to");
  const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol 'add4to': " << dlerror() << '\n';
        dlclose(handle);
        return 1;
    }


  singleTon<test> s1;
  int y= 0;
  y= s1->add (3);

  std::cout<<  "in main singlton befor: "<<y<<std::endl;

  so_add();
  std::cout<<  "in main singlton after :" <<s1->print()<<std::endl;
  return 0;
}
