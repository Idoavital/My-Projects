/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Task.h"

namespace ilrd
{
   int Task::get()
   {
     std::unique_lock<std::mutex> mlock(m_mutex);
     while (!m_done)
       {
         m_conVar.wait (mlock);
       }
     return m_result;
       
   }
   
   void Task::Run()
   {
     m_result =  (*this)();
     
     std::unique_lock<std::mutex> mlock(m_mutex);
     m_done = true;
     mlock.unlock ();
     
     m_conVar.notify_all ();
     
   }

}