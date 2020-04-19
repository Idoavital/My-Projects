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
#include "shap.h"

namespace ilrd
{
    

class circle: public shap
{
public:
    circle();
    circle(const circle& orig);
    virtual ~circle();
private:

};

}
#endif /* CIRCLE_H */

