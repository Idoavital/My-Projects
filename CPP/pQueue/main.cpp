/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ido
 *
 * Created on March 13, 2018, 9:53 AM
 */

#include <cstdlib>
#include <iostream>

#include "pQueue.h"

using namespace std;
using namespace ilrd;

/*
 * 
 */
void testPquqe();
int main (int argc, char* argv[])
{
  std::cout<<"test" <<endl;
  testPquqe();
  return 0;
}
void testPquqe()
{
  pQueue <int> pq;
  pq.push (1);
  pq.push (5);
  pq.push (2);
  pq.push (3);
  
 for(int i = 4 ; i > 0 ; i--)
 {
     
    cout<< pq.pop() << endl;
 }
}