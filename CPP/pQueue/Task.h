/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Task.h
 * Author: stav
 *
 * Created on March 13, 2018, 6:34 PM
 */

#ifndef TASK_H
#define TASK_H

#include <memory>

namespace ilrd
{
 /******************************************************************************/   
/********************class Task*************************************************/
class Task 
{
public:
      
    explicit Task(){};
    Task(const Task& orig);
    virtual ~Task(){};
    virtual int operator () () =0 ;
    void wait();
    
    template <typename T >
    std::shared_ptr<Task> static create (T& obj, int (T::*pfunc)());
    
private:
 

};

 /******************************************************************************/   
/********************class derived_task*****************************************/
template <typename T >
class derived_task: public Task
{
public:
     derived_task(T& obj, int (T::*pfunc)()):m_obj(obj),m_pfunc(pfunc) {}
    ~ derived_task(){};
    
    int operator () ()
    {
        return(m_obj.*m_pfunc)();
    }
    
private:

    T& m_obj;
    int (T::*m_pfunc)();
    
};

 /******************************************************************************/   
/********************static function create*************************************/

template <typename T >
std::shared_ptr<Task> Task::create (T& obj, int (T::*pfunc)())
{
    return std::shared_ptr<Task> (new derived_task<T>(obj , pfunc));
}

}// nameapce ilrd

#endif /* TASK_H */

