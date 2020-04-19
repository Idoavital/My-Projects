/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bitArrayVector.h
 * Author: ido
 *
 * Created on February 12, 2018, 11:12 AM
 */

#ifndef BITARRAYVECTOR_H
#define BITARRAYVECTOR_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <unistd.h>

#define BITS 8
#define ST_BITS (8 * sizeof(size_t))

namespace ilrd
{

    
    
template <size_t Z>
class BitArray
{
  private:
    class proxy;
public:
   explicit BitArray(); // ctor
    
   const BitArray& operator &= (const BitArray& other);
   const BitArray& operator |= (const BitArray& other);
   const BitArray& operator ^= (const BitArray& other);
   bool  operator += (const BitArray& other);
   bool  operator == (const BitArray& other);
   bool  operator != (const BitArray& other);
 
   const BitArray& operator <<= (size_t num);
   
   proxy operator [] (size_t index);
   bool operator [] (size_t index) const;

   void setBit(size_t index , bool val);
   bool getBit(size_t index);
   
   size_t count();

private:
    std::vector<size_t > m_bit_arr;
    
};

template <size_t Z>
class BitArray<Z>::proxy
{
public:    
   proxy(BitArray<Z>& ref_bit ,size_t m_index);
   bool operator= ( bool val);
   bool operator= (const proxy& other);
   operator bool () const ;
private:
    size_t m_index;
    BitArray<Z>& m_ref_bit;
};
template <size_t Z>    
std::ostream& operator<< (std::ostream& os , BitArray<Z>& bit_arr );
/********************binari functor********************************************/
class B_OR
{
public:
    size_t operator ()(size_t left ,size_t right )
    {
        return (left|right);
    }
};
class B_AND
{
public:
    size_t operator ()(size_t left ,size_t right )
    {
        return (left&right);
    }
};
class B_XOR
{
public:
    size_t operator ()(size_t left ,size_t right )
    {
        return (left^right);
    }
};

class ShiftLeft
{
public:
    explicit ShiftLeft(size_t bit_len =0 ):m_bit_len(bit_len){};
    size_t operator ()(size_t right ,size_t left )
    {
        if (m_bit_len == 0)
        {
            return right;
        }
        return (right<<m_bit_len |left>>(ST_BITS - m_bit_len) );
    }
private:
    int m_bit_len;
};
class Count
{
public:
    explicit Count(size_t size):m_size(size) ,m_set_bit(0){}; /* ctor*/
    void operator()(size_t num)
    {
        //int i = 64;
        /* count the set bit in num*/
       /* while (m_size && i) 
        {
            if (num&1L ) 
            {
                m_set_bit++;
            }
            m_size--;
            i--;
            num>>=1;
        }*/
        while (num) 
        {
            m_set_bit++;
            num&=num-1;
            
        }

    }
    size_t GetCount(){return m_set_bit ;};
private:
    size_t m_set_bit;
    size_t m_size;
};
/************************bitArray class Ctor***********************************/
template <size_t Z> 
BitArray<Z>::BitArray():m_bit_arr((Z +(BITS * sizeof(size_t)) -1 )/(BITS * sizeof(size_t)), 0 )
{

}
/************************bitArray class function********************************/

template <size_t Z> 
const BitArray<Z>& BitArray<Z>::operator &= (const BitArray& other)
{
    std::transform(m_bit_arr.begin(),m_bit_arr.end(),other.m_bit_arr.begin()
                                    ,m_bit_arr.begin(), std::bit_and<size_t>());
}

template <size_t Z> 
const BitArray<Z>& BitArray<Z>::operator ^= (const BitArray& other)
{
    std::transform(m_bit_arr.begin(),m_bit_arr.end(),other.m_bit_arr.begin()
                                    ,m_bit_arr.begin(), std::bit_xor<size_t>());
}

template <size_t Z> 
const BitArray<Z>& BitArray<Z>::operator |= (const BitArray& other)
{
    std::transform(m_bit_arr.begin(),m_bit_arr.end(),other.m_bit_arr.begin()
                                     ,m_bit_arr.begin(), std::bit_or<size_t>());
   
}
size_t zero (size_t num)
{
    return 0;
}
template <size_t Z> 
bool  BitArray<Z>::operator == (const BitArray& other)
{
   
    return (this->m_bit_arr== other.m_bit_arr);
}

template <size_t Z> 
bool  BitArray<Z>::operator != (const BitArray& other)
{
    return (this->m_bit_arr!= other.m_bit_arr);
}
template <size_t Z> 
const BitArray<Z>& BitArray<Z>::operator <<= (size_t num)
{
    size_t block= num / ST_BITS;
    size_t temp =0;
    
    std::transform(m_bit_arr.rbegin()+block, //right ,
                        m_bit_arr.rend()-1,
                        m_bit_arr.rbegin()+block+1, //left
                        m_bit_arr.rbegin(),
                        ShiftLeft( num % ST_BITS)  ); 
    
     *m_bit_arr.begin() <<=( num % ST_BITS);
     *(m_bit_arr.begin()+block)=*m_bit_arr.begin();
     
    fill(m_bit_arr.begin(), m_bit_arr.begin()+block , 0 );
    
    /*set to zero all the last bits in the garbage area of the last block */
    temp=1L<<(Z % ST_BITS) ;
    temp-=1;
    *(m_bit_arr.rbegin()) &=temp;
    
    
}

template <size_t Z> 
std::ostream& operator<< (std::ostream& os , BitArray<Z>& bit_arr )
{

    for (ssize_t i = Z-1 ; i >= 0 ;--i)
    {      
        os<<bit_arr[i];
        if(i%8 == 0) 
            os<<" ";
        if(i%64 == 0) 
            os<<"\n";      
    };

    return os;
}

template <size_t Z> 
void BitArray<Z>::setBit(size_t index , bool val)
{
  size_t i =0;
  i = index / (BITS * (sizeof(size_t)));
  if (val)
    {
      m_bit_arr[i] |= 1UL << (index % (BITS * (sizeof(size_t))) );
    }
  else
    {
       m_bit_arr[i] &= ~(1UL << (index % (BITS * (sizeof(size_t))) ));
    }
}

template <size_t Z> 
bool BitArray<Z>::getBit(size_t index)
{
  bool ret = true;
  size_t i = 0;
  i = index / (BITS * (sizeof(size_t)));
  ret = 1UL & (m_bit_arr[i] >> index % (BITS * (sizeof(size_t)))); 
  return (ret);
}
/************************proxy class function**********************************/
/*proxy Ctor*/
template <size_t Z> 
BitArray<Z>::proxy::proxy(BitArray<Z> &ref_bit ,size_t index):m_ref_bit(ref_bit)
                                                        ,m_index(index){}


template <size_t Z> 
typename BitArray<Z>::proxy BitArray<Z>::operator [] (size_t index)
  {
    return BitArray<Z>::proxy(*this ,index);
  }
template <size_t Z> 
bool BitArray<Z>::operator [] (size_t index) const
  {
    return (BitArray<Z>::proxy(this->getBit(index)));
  }

template <size_t Z> 
bool BitArray<Z>::proxy::operator= ( bool val)
{
    m_ref_bit.setBit ( m_index, val);
}
template <size_t Z> 
BitArray<Z>::proxy::operator bool () const 
{
    return (m_ref_bit.getBit (m_index)); 
}

template <size_t Z> 
bool BitArray<Z>::proxy::operator= (const BitArray<Z>::proxy& other)
{
  bool val = other.m_ref_bit.getBit (other.m_index);
  m_ref_bit.setBit ( m_index, val);
  return (m_ref_bit.getBit (m_index)); 
}

template <size_t Z> 
size_t BitArray<Z>::count( )
{
    class Count c1(Z);
   
    c1 = std::for_each (m_bit_arr.begin(),m_bit_arr.end(),Count(Z));
    
    return c1.GetCount();
    
}
/************************Shift class Ctor**************************************/


}//namespace ilrd
#endif /* BITARRAYVECTOR_H */

