/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThreadPool.cpp
 * Author: stav
 * 
 * Created on March 13, 2018, 6:34 PM
 */

#include "ThreadPool.h"

namespace ilrd
{

  
ThreadPool::ThreadPool (int threads_size , int run_threads ): 
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

ThreadPool::~ThreadPool () {}

void ThreadPool::shutDown()
{
   m_flag_run = false ;
   m_pq.Destroy ();
   
   for (int i =0 ; i<m_threads_size ; i++)
   {
       m_vecThread[i].join ();
   }
}

void ThreadPool::SetRunnigThreads(int run_threads)
{
  m_pq.setRunnigToken (run_threads);
}

bool cmp(const Pair_t& l_pr ,const Pair_t& r_pr)
{
    return ( l_pr.second< r_pr.second );
}


void ThreadPool::Run()
{
  Dummy dum_obj;
  Pair_t task_pair(Task::create (dum_obj, &Dummy::dum ), HIGH);
  
  while (m_flag_run)
  {
    (*task_pair.first)();
    m_pq.pop (task_pair);
    
  }  
    
//    if (m_flag_run)
//    {
//       (*task_pair.first)();
//    }
//  }
  
}


} //namespace ilrd