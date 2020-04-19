/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   singleTon.h
 * Author: ido
 *
 * Created on March 7, 2018, 9:41 AM
 */

#ifndef SINGLETON_H
#define SINGLETON_H

#include <stdlib.h>

/******************************************************************************/
/*********************class singleTon******************************************/

namespace ilrd
{

template <typename T>
class singleTon
{
    public :
        singleTon();
           
        static T&  GetInstance();    
        static void destroy();
        T* operator->();   
    private:
        
        singleTon(const T&  ){};      
        void operator= ( const T& ){};
        
        static T* m_instance;
        
};

/******************************************************************************/
/*****************************class declertion ********************************/

template <typename T>
T* singleTon<T>::m_instance;


template <typename T>
singleTon<T>::singleTon()
{
   GetInstance();
}

template <typename T>
T& singleTon<T>::GetInstance()
{
    static int lock = 0 ;
    while (!m_instance)
    {
        if (!  __atomic_fetch_or (&lock,1,__ATOMIC_ACQ_REL ) )
        {
              __atomic_fetch_or (&m_instance ,new T ,__ATOMIC_ACQ_REL );
             std::atexit(destroy);
        }
        else while(!  __atomic_fetch_or (&m_instance , 0 ,__ATOMIC_ACQ_REL ))
        {
            
        }
        
    }

    return *m_instance;
}


template <typename T>
void singleTon<T>::destroy()
{
   delete( m_instance );
   m_instance = (T*)0xDEADBEEFDEADBEEF;
}

template <typename T>
T* singleTon<T>::operator -> ()
{
    return (m_instance);
}

} //ilrd


#endif /* SINGLETON_H */

