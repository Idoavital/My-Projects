/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   shap.h
 * Author: stav
 *
 * Created on March 12, 2018, 9:49 AM
 */

#ifndef SHAP_H
#define SHAP_H

#include <iostream>
namespace ilrd
{
    

/* abstract class */
class shape
{
public:
    shape(const std::string& str);
    
    virtual std::string draw();
    
protected:
    std::string m_str;

};






}//ilrd
#endif /* SHAP_H */

