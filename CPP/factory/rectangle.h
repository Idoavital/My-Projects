/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rectangle.h
 * Author: stav
 *
 * Created on March 12, 2018, 11:42 AM
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"


namespace ilrd
{
    
class rectangle: public shape
{
public:
    
    static shape* create(int x);
    rectangle();
    rectangle(const rectangle& orig);
   
    virtual std::string draw();
    
private:

};

}
#endif /* RECTANGLE_H */

