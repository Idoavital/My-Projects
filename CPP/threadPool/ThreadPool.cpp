/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThreadPool.cpp
 * Author: ido
 * 
 * Created on March 13, 2018, 6:34 PM
 */

#include "ThreadPool.h"
#include <iostream>

namespace ilrd
{


  
ThreadPool::ThreadPool (int threads_size , int run_threads  ): 
                m_threads_size(threads_size),
                m_run_threads(run_threads),
                m_pq(run_threads , threads_size),
                m_vecThread(threads_size)
              
{
  for (int i =0 ; i< m_threads_size ; i++)
    {
      m_vecThread[i] = std::thread (&ThreadPool::Run ,this);
    }
}

ThreadPool::ThreadPool (const ThreadPool& orig) { }

ThreadPool::~ThreadPool ()
{
  shutDown();
}

void ThreadPool::shutDown()
{
   m_flag_run = false ;
   m_pq.Destroy ();
    
   for (int i =0 ; i<m_threads_size ; i++)
   {
       if (m_vecThread[i].joinable())
                m_vecThread[i].join ();
   }

}

void ThreadPool::SetRunnigThreads(int run_threads)
{
  m_pq.setRunnigToken (run_threads);
}

std::shared_ptr<Task> ThreadPool::AddTask(std::shared_ptr<Task> task,Priority pt)
{
    Pair_t pair (task , pt);
    m_pq.push (pair);
    return task;
}


void ThreadPool::Run()
{
  Dummy dum_obj;  // only for the first time
  Pair_t task_pair(Task::create (dum_obj, &Dummy::dum ), HIGH);
  
  while (m_flag_run)
  {
    (*task_pair.first).Run ();
    m_pq.pop (task_pair);
    
  }  
    

  
}


} //namespace ilrd