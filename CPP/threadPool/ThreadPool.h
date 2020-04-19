/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThreadPool.h
 * Author: stav
 *
 * Created on March 13, 2018, 6:34 PM
 */

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "pQueue.h"
#include "Task.h"



namespace ilrd
{
    
enum Priority
{
    LOW,
    MID,
    HIGH
};
    
typedef  std::pair<std::shared_ptr<Task> , Priority> Pair_t;


class cmp_t
{
public:
   bool operator ()(const Pair_t& l_pr ,const Pair_t& r_pr)
   {
       return ( l_pr.second< r_pr.second );
   }
};
bool cmp(const Pair_t& l_pr ,const Pair_t& r_pr);


class ThreadPool
{
public:
    explicit ThreadPool(int threads_size , int run_threads );
    ThreadPool(const ThreadPool& orig);
    virtual ~ThreadPool();
    void SetRunnigThreads(int run_threads);
    void shutDown();        //joinable function
    void Run();
    std::shared_ptr<Task> AddTask(std::shared_ptr<Task> ,Priority); 
private:
    
    std::vector<std::thread> m_vecThread ;              //threads vector
    pQueue<Pair_t ,std::vector<Pair_t>, cmp_t > m_pq;
    int m_threads_size;
    int m_run_threads;
    bool m_flag_run;           //  flag for stop the thread

};

class Dummy
{
public:
    int dum(){};
};

} // namespace ilrd

#endif /* THREADPOOL_H */

