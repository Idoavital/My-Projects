/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   shap.cpp
 * Author: stav
 * 
 * Created on March 12, 2018, 9:49 AM
 */

#include "shape.h"
namespace ilrd
{

/*****************************************************************************/
/********************* class shape ********************************************/
shape::shape (const std::string& str) :m_str(str){ }

std::string shape::draw()
{
  return m_str;
}

        

}