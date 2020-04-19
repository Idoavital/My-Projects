/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   circle.h
 * Author: stav
 *
 * Created on March 12, 2018, 9:57 AM
 */

#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

namespace ilrd
{
    

class circle: public shape
{
public:
    circle();
   
    static shape* create(int x );
   
    std::string draw();
private:

};

}//ilrd
#endif /* CIRCLE_H */

