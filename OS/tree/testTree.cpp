/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   testTree.cpp
 * Author: stav
 *
 * Created on February 20, 2018, 5:46 PM
 */

#include <cstdlib>
#include <iostream>

#include "tree.h"

using namespace std;
using namespace ilrd;

/*
 * 
 */
void testBuild ();
void testfind ();
void testexepction (); /* try to find exepction*/
int main (int argc, char** argv)
{
    testBuild ();
    testfind ();
 
  return 0;
}

void testBuild ()
{
  string s1  = "/home/stav/svn/Proj/src/CPP";
  std::shared_ptr<Directory> p1;
 
  p1 = Directory::BuildTree ( s1);
  p1->Display ();
}

void testfind ()
{
 
  cout<<"try to find dir :cpp_to_c_ex/build/Debug "<<endl;
  std::shared_ptr<Directory> p1;
  p1 = Directory::BuildTree ( "/home/stav/svn/Proj/src/CPP");
  p1->Find ("cpp_to_c_ex/build/Debug")->Display ();
  
}

void testexepction ()
{
 
  cout<<"try to find dir :cpp_to_c/build/Debug "<<endl;
  std::shared_ptr<Directory> p1;
  p1 = Directory::BuildTree ( "/home/stav/svn/Proj/src/CPP");
  p1->Find ("cpp_to_c/build/Debug")->Display ();
  
}
