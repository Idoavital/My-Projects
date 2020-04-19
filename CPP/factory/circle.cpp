/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   circle.cpp
 * Author: stav
 * 
 * Created on March 12, 2018, 9:57 AM
 */

#include "circle.h"

namespace ilrd
{
  
  shape* circle::create(int x)
  {
    return  new circle ;
  }

  circle::circle ():shape("i am circle") { }

 std::string circle::draw()
 {
   return m_str;
 }

}