/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ido
 *
 * Created on March 13, 2018, 9:53 AM
 */

#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "ThreadPool.h"
#include "pQueue.h"


using namespace std;
using namespace ilrd;

/*
 * 
 */
void testPquqe();
void testPquqeMulti();
void testPquqewait();

class job1
{
 public:
    
  int run()
  {
    cout<<"start job 1"<<endl;
    sleep(2);
    cout<<"FINSH job 1"<<endl;   
    return 0;
  }
};

class job2
{
public:
  int run()
  {
    
    cout<<"\nstart job 2"<<endl;
    sleep(2);
    cout<<"\nFINSH job 2"<<endl;   
    return 0;
  }
}  ;
  
  
class job3
{
public:
  int run()
  {
    
    cout<<"\nstart job 3"<<endl;
    sleep(30);
    cout<<"\nFINSH job 3"<<endl;   
    return 0;
  }
};


int main (int argc, char* argv[])
{
  std::cout<<"-----test-----" <<endl;
  testPquqeMulti();
  testPquqewait();
  return 0;
}


void testPquqeMulti()
{
   job1 job_1;
   job2 job_2;
  
   shared_ptr<Task> t1 (Task::create (job_1 , &job1::run));
   shared_ptr<Task> t2 (Task::create (job_2 , &job2::run));
   
   
   ThreadPool tp1(8,1);
   
   tp1.AddTask (t1,MID);
   tp1.SetRunnigThreads (4);
   tp1.AddTask (t2,HIGH);
   tp1.AddTask (t1,MID);
   tp1.AddTask (t1,MID);
   tp1.AddTask (t2,HIGH);
   
   
   std::cout<<" finsh test 1 "<<endl;
   //sleep(20);
  
   
}

void testPquqewait()
{
  
  std::cout<<" -----test  wait --- "<<endl;
   job1 job_1;
   job2 job_2;
   job3 job_3;
  
   shared_ptr<Task> t1 (Task::create (job_1 , &job1::run));
   shared_ptr<Task> t2 (Task::create (job_2 , &job2::run));
   shared_ptr<Task> t3 (Task::create (job_3 , &job3::run));
   
   
   ThreadPool tp1(8,2);
   
   tp1.AddTask (t1,MID);
   tp1.AddTask (t2,HIGH);
   tp1.AddTask (t1,MID);
   tp1.AddTask (t1,MID);
   
   shared_ptr<Task> towait;
   towait = tp1.AddTask (t3,HIGH);
   towait->get ();
   std::cout<<" fafter get "<<endl;
  
}

void testPquqe()
{
  pQueue <int> pq;
  pq.push (1);
  pq.push (5);
  pq.push (2);
  pq.push (3);
  
 for(int i = 4 ; i > 0 ; i--)
 {
     
    cout<< pq.pop() << endl;
 }
}