/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rectangle.cpp
 * Author: stav
 * 
 * Created on March 12, 2018, 11:42 AM
 */

#include "rectangle.h"


namespace ilrd
{

rectangle::rectangle(): shape("i am rectangle") { }


shape* rectangle::create(int x)
{
  return  ( new rectangle);
}

std::string rectangle::draw()
{
  return m_str;
}

}//ilrd