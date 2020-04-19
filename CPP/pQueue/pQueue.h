/*
 *  pQueue thread safety .
 *  there is two options Ctor: 
 *  1- default  priority queue 
 *  2 - multi thread  priority queue with option to decide how many task will run 
 *      in the same time .
 *      the Ctor get 2 parameter ,(int max_running thread , int number_of_threads) .
 * 
 */

/* 
 * File:   pQueue.h
 * Author: ido
 *
 * Created on March 13, 2018, 10:03 AM
 */

#ifndef PQUEUE_H
#define PQUEUE_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
 
namespace ilrd
{

template <typename T ,typename  Container = std::vector<T> ,typename Cmp = std::less<T> >
class pQueue
{
 public:
    explicit pQueue(int max_free_token = 1 , int num_of_token = 0 ); //Ctor
    ~pQueue();
    pQueue(const pQueue&) = delete;            // disable copying
    pQueue& operator=(const pQueue&) = delete; // disable assignment
    void setRunnigToken(int new_num_token);
    void Destroy();
  
     
  T pop()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
  
    m_counter++;
    
    while (( queue_.empty()   || m_counter < m_num_block ) && m_flag_run )
    {
        cond_.wait(mlock);
    }
     // if the function destroy been called the thread will live the queue
    if (!m_flag_run)
    {
         return 0;
    } 
    
    m_counter--;
    auto item = queue_.top();
    queue_.pop();
    
    return item;
  }
 
  void pop(T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    m_counter++; 
    
    while (( queue_.empty() || m_counter < m_num_block ) && m_flag_run)
    {
      cond_.wait(mlock);
    }
     // if the function destroy been called the thread will live the queue
    if (!m_flag_run)
    {
        return ;
    } 
    
    m_counter--;
    item = queue_.top();
    queue_.pop();
  }
 
  void push(const T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
  }
 
  void push(T&& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(std::move(item));
    mlock.unlock();
    cond_.notify_one();
  }
  
  
  
 private:
  std::priority_queue< T, Container ,Cmp > queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
  int m_counter;                    // count the number of free token 
  int m_num_token;
  int m_num_block;                        
  bool m_flag_run;                 //the flag tell to threads to live the queue if the set to false
  
};

/*******************************************************************************/
/********************** class functions ***************************************/


// Ctor
/*****************************************************************************/
template <typename T ,typename  Container ,typename Cmp >
pQueue<T,Container,Cmp >::pQueue(int max_free_token , int num_of_token ): m_counter(0),
                m_num_block (num_of_token - max_free_token),m_num_token(num_of_token),
        m_flag_run(true)

{   
}

// Destroy
/*****************************************************************************/
template <typename T ,typename  Container ,typename Cmp >
void pQueue<T,Container,Cmp >::Destroy()
{
     std::unique_lock<std::mutex> mlock(mutex_);
        m_flag_run = false;
        cond_.notify_all();  
}
// Dtor
/*****************************************************************************/
template <typename T ,typename  Container ,typename Cmp >
pQueue<T,Container,Cmp >::~pQueue()
{
    this->Destroy();
}

// setRunnigToken
/*****************************************************************************/
template <typename T ,typename  Container ,typename Cmp >
void pQueue<T,Container,Cmp >::setRunnigToken(int new_num_token)
{
  std::unique_lock<std::mutex> mlock(mutex_);
    m_num_block = m_num_token - new_num_token;
    cond_.notify_all();
 
}

} //namespace ilrd

#endif /* PQUEUE_H */

