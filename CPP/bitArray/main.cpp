
/* 
 * File:   bitArray.h
 * Author: ido
 *
 * Created on February 8, 2018, 2:36 PM
 */

#ifndef BITARRAY_H
#define BITARRAY_H

#include <stddef.h>
#include <iostream>
#include <cstring> //memmove

#define BITS 8

//using namespace std;
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
   const BitArray& operator <<= ( int num);
   const BitArray& operator >>= (int num);
   proxy operator [] (size_t index);
   bool operator [] (size_t index) const;
   void setBit(size_t index , bool val);
   bool getBit(size_t index);

private:

    size_t m_bit_arr[(Z + (BITS * sizeof(size_t)) -1 )/(BITS * sizeof(size_t))];   //size of bit array in aize_t             
    size_t m_arr_size;
};

template <size_t Z>
class BitArray<Z>::proxy
{
public:    
   proxy(BitArray<Z>& ref_bit ,size_t m_index);
   bool operator= ( bool val);
   operator bool () const ;
   bool operator= (const proxy& other);
private:
    size_t m_index;
    BitArray<Z>& m_ref_bit;
};

/********************function definition  **********************************/
/*bitarray Ctor*/
template <size_t Z> 
BitArray<Z>::BitArray():m_bit_arr() ,m_arr_size((Z +(BITS * sizeof(size_t)) -1 )/(BITS * sizeof(size_t)))
{

}


template <size_t Z> 
const BitArray<Z>& BitArray<Z>::operator &= (const BitArray& other)
{

  for (size_t i =0 ; i< m_arr_size; i++)
    {
      this->m_bit_arr[i] &= other->m_bit_arr[i];
    }
}

template <size_t Z> 
const BitArray<Z>& BitArray<Z>::operator |= (const BitArray& other)
{
  
  for (size_t i =0 ; i< m_arr_size; i++)
    {
      this->m_bit_arr[i] |= other->m_bit_arr[i];
    }
}

template <size_t Z> 
const BitArray<Z>& BitArray<Z>::operator ^= (const BitArray& other)
{
  
  for (size_t i =0 ; i< m_arr_size; i++)
    {
      this->m_bit_arr[i] ^= other->m_bit_arr[i];
    }
}

template <size_t Z> 
const BitArray<Z>& BitArray<Z>::operator >>= ( int num)
{

  size_t bit_len = sizeof(size_t) * BITS;
  size_t shift = 1;
  size_t bits1 = 0, bits2 = 0;
  int array_jump = num / bit_len;
  if(0 == num)
    {
      return *this;
    }
  
  if (num > 1)
  {
      shift <<= (num  % bit_len); // 2^num
      shift -= 1; // set all num bits
  }
  
  memmove(m_bit_arr , m_bit_arr + array_jump, ((m_arr_size - array_jump) * (sizeof(size_t)) ));
  /*memset to 0 */
  memset( m_bit_arr + (m_arr_size - array_jump - 1),0 , array_jump * (sizeof(size_t)));
  
  for(int i = m_arr_size - 1 ; i >= 0; --i) 
  { 
        bits2 = m_bit_arr[i] & shift;
        m_bit_arr[i]  >>= (num % bit_len); /***to finsh ***/
        m_bit_arr[i] |= bits1 << (bit_len - (num % bit_len));
        bits1 = bits2;
   }
    
  return *this;
}
template <size_t Z> 
const BitArray<Z>& BitArray<Z>::operator <<= (int num)
{
  size_t bit_len = sizeof(size_t) *  BITS;
  size_t shift = 1; 
  size_t bits1 = 0, bits2 = 0;
  int array_jump = num / bit_len;
  
  if(0 == num)
    {
      return *this;
    }
  
  if (num > 1)
  {
    shift <<= num; // 2^num
    shift -= 1; // set all num bits
    shift = ~shift;
  }
 
  for(int i = array_jump ; i < m_arr_size ; ++i) 
  { 
        bits2 = m_bit_arr[i] & shift;
        m_bit_arr[i]  <<= (num % bit_len);
        m_bit_arr[i] |= bits1 >> (bit_len - (num % bit_len));
        bits1 = bits2;
   }
  return *this;
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

/*proxy Ctor*/
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
BitArray<Z>::proxy::proxy(BitArray<Z> &ref_bit ,size_t index):m_ref_bit(ref_bit)
                                                        ,m_index(index){}

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
/*********************MAIN *******************/
int main (int argc , char *argv[])
{
  
  BitArray<500> b1;
  BitArray<640> b2;
  b2[2] = true;
  b1.setBit (400, true);
  bool ret = b1.getBit (32);
  std::cout<<ret <<std::endl;
  std::cout<<b1.getBit (30) <<std::endl;
  std::cout<<b1[400]<<std::endl;
  b1[39] = b2[2];
  std::cout<<b1[39]<<std::endl;
  b1>>=100;
  std::cout<< "b1 300- "<<b1[300]<<std::endl;
  std::cout<<"b1 299 -"<<b1[299]<<std::endl;
  b1<<=1;
  std::cout<<b1[39]<<std::endl;
  std::cout<<b1[38]<<std::endl;
  
  return 0;
}


}
#endif /* BITARRAY_H */


