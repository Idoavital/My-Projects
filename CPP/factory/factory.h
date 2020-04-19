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
    
/*****************************************************************************/
/****************class factory **********************************************/
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

/*****************************************************************************/
/****************implementation class factory*********************************/
template <typename T,  typename K , typename P >
void factory<T,K,P>::registers(const K& key , creator cr_p)
{
    m_creators[key]=cr_p;
}

template <typename T,  typename K , typename P >
T factory<T,K,P>::create(const K& key , P param)
{ 
    if(m_creators.find(key) != m_creators.end())
    {
        return (m_creators[key](param));
    }
    
    return (NULL);
}



}//ilrd
#endif /* FACTORY_H */

