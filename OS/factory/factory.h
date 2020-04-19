/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   factory.h
 * Author: ido
 *
 * Created on March 11, 2018, 6:09 PM
 */

#ifndef FACTORY_H
#define FACTORY_H

#include <map>

namespace ilrd
{
    

template <typename T,  typename K , typename P >
class factory
{
public:
    typedef T (*creator )(P);
    void registers(const K& key , creator cr_p);
    T create(const K& key , P param);
    
private:
    std::map < K ,creator > m_creators;    
    
};

}//ilrd
#endif /* FACTORY_H */

