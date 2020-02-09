/*
  data_container_operations.hpp
        - all those operator for gsid_t and data_t

  Copyright 2019  Dubrovin Egor <dubrovin.en@ya.ru>
                  Alexander Kiryanenko <kiryanenkoav@mail.ru>
                  Alex Popov <alexpopov@bmstu.ru>
                  Bauman Moscow State Technical University

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "containers_operators.hpp"

namespace SPU
{

/***************************************
  data_t operators
***************************************/ 

/* Compare */
bool operator== (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) == 0; }
bool operator!= (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) != 0; }
bool operator>  (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) >  0; }
bool operator>= (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) >= 0; }
bool operator<  (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) <  0; }
bool operator<= (const data_t &c1, const data_t &c2) { return cmpContainers(c1, c2) <= 0; }

bool operator== (const data_t &c1, u8 num) { const data_t c2 = num; return cmpContainers(c1, c2) == 0; }
bool operator!= (const data_t &c1, u8 num) { const data_t c2 = num; return cmpContainers(c1, c2) != 0; }
bool operator>  (const data_t &c1, u8 num) { const data_t c2 = num; return cmpContainers(c1, c2) >  0; }
bool operator>= (const data_t &c1, u8 num) { const data_t c2 = num; return cmpContainers(c1, c2) >= 0; }
bool operator<  (const data_t &c1, u8 num) { const data_t c2 = num; return cmpContainers(c1, c2) <  0; }
bool operator<= (const data_t &c1, u8 num) { const data_t c2 = num; return cmpContainers(c1, c2) <= 0; }

bool operator== (const data_t &c1, unsigned int num) { const data_t c2 = num; return cmpContainers(c1, c2) == 0; }
bool operator!= (const data_t &c1, unsigned int num) { const data_t c2 = num; return cmpContainers(c1, c2) != 0; }
bool operator>  (const data_t &c1, unsigned int num) { const data_t c2 = num; return cmpContainers(c1, c2) >  0; }
bool operator>= (const data_t &c1, unsigned int num) { const data_t c2 = num; return cmpContainers(c1, c2) >= 0; }
bool operator<  (const data_t &c1, unsigned int num) { const data_t c2 = num; return cmpContainers(c1, c2) <  0; }
bool operator<= (const data_t &c1, unsigned int num) { const data_t c2 = num; return cmpContainers(c1, c2) <= 0; }

bool operator== (const data_t &c1, unsigned long num) { const data_t c2 = num; return cmpContainers(c1, c2) == 0; }
bool operator!= (const data_t &c1, unsigned long num) { const data_t c2 = num; return cmpContainers(c1, c2) != 0; }
bool operator>  (const data_t &c1, unsigned long num) { const data_t c2 = num; return cmpContainers(c1, c2) >  0; }
bool operator>= (const data_t &c1, unsigned long num) { const data_t c2 = num; return cmpContainers(c1, c2) >= 0; }
bool operator<  (const data_t &c1, unsigned long num) { const data_t c2 = num; return cmpContainers(c1, c2) <  0; }
bool operator<= (const data_t &c1, unsigned long num) { const data_t c2 = num; return cmpContainers(c1, c2) <= 0; }

/* Arithmetic */
data_t       operator+ (const data_t &c1, const data_t &c2) { return addContainers(c1, c2); }
data_t       operator- (const data_t &c1, const data_t &c2) { return subContainers(c1, c2); }

data_t       operator+ (const data_t &c1, u8 num) { const data_t c2 = num; return addContainers(c1, c2); }
data_t       operator- (const data_t &c1, u8 num) { const data_t c2 = num; return subContainers(c1, c2); }
data_t       operator+ (const data_t &c1, unsigned int num) { const data_t c2 = num; return addContainers(c1, c2); }
data_t       operator- (const data_t &c1, unsigned int num) { const data_t c2 = num; return subContainers(c1, c2); }
data_t       operator+ (const data_t &c1, unsigned long num) { const data_t c2 = num; return addContainers(c1, c2); }
data_t       operator- (const data_t &c1, unsigned long num) { const data_t c2 = num; return subContainers(c1, c2); }
data_t       operator+ (const data_t &c1, int num) { return num >= 0 ? c1 + (unsigned int) num : c1 - (unsigned int) -num; }
data_t       operator- (const data_t &c1, int num) { return num >= 0 ? c1 - (unsigned int) num : c1 + (unsigned int) -num; }

/* Increment/Decrement */
data_t &     operator++ (data_t &c1)      { return incContainer(c1); }
const data_t operator++ (data_t &c1, int) { auto prev = c1; incContainer(c1); return prev; } // Return before change
data_t &     operator-- (data_t &c1)      { return incContainer(c1); }
const data_t operator-- (data_t &c1, int) { auto prev = c1; decContainer(c1); return prev; } // Return before change

/* Bit operation */
data_t operator& (const data_t &c1, const data_t &c2) { return andContainers(c1, c2); }
data_t operator| (const data_t &c1, const data_t &c2) { return orContainers (c1, c2); }
data_t operator^ (const data_t &c1, const data_t &c2) { return xorContainers(c1, c2); }
data_t operator~ (const data_t &c1)                   { return notContainers(c1);     }

/* Shifts */
data_t operator<< (const data_t &cont, const u8 &shift);
data_t operator>> (const data_t &cont, const u8 &shift);



/***************************************
  gsid_t operators
***************************************/ 

/* Compare */
bool operator== (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) == 0; }
bool operator!= (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) != 0; }
bool operator>  (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) >  0; }
bool operator>= (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) >= 0; }
bool operator<  (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) <  0; }
bool operator<= (const gsid_t &c1, const gsid_t &c2) { return cmpContainers(c1, c2) <= 0; }

/* Arithmetic */
gsid_t       operator+ (const gsid_t &c1, const gsid_t &c2) { return addContainers(c1, c2); }
gsid_t       operator- (const gsid_t &c1, const gsid_t &c2) { return subContainers(c1, c2); }

/* Increment/Decrement */
gsid_t &     operator++ (gsid_t &c1)      { return incContainer(c1); }
const gsid_t operator++ (gsid_t &c1, int) { auto prev = c1; incContainer(c1); return prev; } // Return before change
gsid_t &     operator-- (gsid_t &c1)      { return incContainer(c1); }
const gsid_t operator-- (gsid_t &c1, int) { auto prev = c1; decContainer(c1); return prev; } // Return before change

/* Bit operation */
gsid_t operator& (const gsid_t &c1, const gsid_t &c2) { return andContainers(c1, c2); }
gsid_t operator| (const gsid_t &c1, const gsid_t &c2) { return orContainers (c1, c2); }
gsid_t operator^ (const gsid_t &c1, const gsid_t &c2) { return xorContainers(c1, c2); }
gsid_t operator~ (const gsid_t &c1)                   { return notContainers(c1);     }



/***************************************
  Functions implementations
***************************************/ 

/* Useful macros */
#define arraySize(a) (sizeof(a) / sizeof((a)[0]))

/* Compare container by their size */
template<class T>
int cmpContainers (T &c1, T &c2)
{
  for(int i = arraySize(c1) - 1; i >= 0; --i)
  {
    if (c1[i] != c2[i])
    {
      return c1[i] < c2[i] ? -1 : 1;
    }
  }
  return 0;
}

/* Addict containers */
template <typename T>
T addContainers (T &c1, T &c2)
{
  typename std::remove_const<T>::type ret = {0};
  u8 overflow = 0;
  for(u8 i = 0; i < arraySize(c1); i++)
  {
    u8 _overflow = __builtin_add_overflow(c1[i], c2[i], &ret[i]);
    overflow = __builtin_add_overflow(ret[i], overflow, &ret[i]) || _overflow;
  }
  return ret;
}

/* Subtract containers */
template <typename T>
T subContainers (T &c1, T &c2)
{
  typename std::remove_const<T>::type ret = {0};
  u8 overflow = 0;
  for (u8 i = 0; i < arraySize(c1); i++)
  {
    u8 _overflow = __builtin_sub_overflow(c1[i], c2[i], &ret[i]);
    overflow = __builtin_sub_overflow(ret[i], overflow, &ret[i]) || _overflow;
  }
  return ret;
}

/* Prefix increment */
template <class T>
T & incContainer (T &c)
{
  u8 overflow = __builtin_add_overflow(c[0], 1, &c[0]);
  for(u8 i = 1; overflow && i < arraySize(c); ++i)
  {
    overflow = __builtin_add_overflow(c[i], overflow, &c[i]);
  }
  return c;
}

/* Prefix decrement */
template <class T>
T & decContainer (T &c)
{
  u8 overflow = __builtin_sub_overflow(c[0], 1, &c[0]);
  for(u8 i = 1; overflow && i < arraySize(c); ++i)
  {
    overflow = __builtin_sub_overflow(c[i], overflow, &c[i]);
  }
  return c;
}

/* AND bit by bit */
template <typename T>
T andContainers (const T &c1, const T &c2)
{
  typename std::remove_const<T>::type ret = {0};
  for(u8 i = 0; i < arraySize(c1); i++)
  {
    ret[i] = c1[i] & c2[i];
  }
  return ret;
}

/* OR bit by bit */
template <typename T>
T orContainers (T &c1, T &c2)
{
  typename std::remove_const<T>::type ret = {0};
  for (u8 i = 0; i < arraySize(c1); i++)
  {
    ret[i] = c1[i] | c2[i];
  }
  return ret;
}

/* XOR bit by bit */
template <typename T>
T xorContainers (T &c1, T &c2)
{
  typename std::remove_const<T>::type ret = {0};
  for (u8 i = 0; i < arraySize(c1); i++)
  {
    ret[i] = c1[i] ^ c2[i];
  }
  return ret;
}

/* NOT bit by bit */
template <typename T>
T notContainers (T &c1)
{
  typename std::remove_const<T>::type ret = {0};
  for (u8 i = 0; i < arraySize(c1); i++)
  {
    ret[i] = ~c1[i];
  }
  return ret;
}



/***************************************
  Shift operators
***************************************/

/* Shift operator - iterates and shifts - that's it */
data_t operator<< (const data_t &cont, const u8 &shift)
{
  if(shift > 0)
  {
    data_t work_cont = cont;
    u8 work_shift    = shift;
    u8 part_bit_size = sizeof(*cont.cont)*8;

    /* Shift array element while shift more than one element size */
    u8 idx = 0;
    while(work_shift >= part_bit_size)
    {
      data_t unshifted_cont = work_cont;
      work_cont[idx++] = 0;
      for(u8 i=idx; i<SPU_WEIGHT; i++)
      {
        work_cont[i] = unshifted_cont[i-1];
      }
      work_shift -= part_bit_size;
    }

    if (shift == 0)
    {
      return work_cont;
    }

    /* Shift inside every element of array */
    data_t ret     = 0;
    u8 shifted_out = 0;
    for(u8 i=0; i<SPU_WEIGHT; i++)
    {
      ret[i] = (work_cont[i] << work_shift) | shifted_out;
      shifted_out = work_cont[i] >> (part_bit_size - work_shift);
    }

    return ret;
  }
  else
  {
    return cont;
  }
}

/* Shift operator - iterates and shifts - that's it */
data_t operator>> (const data_t &cont, const u8 &shift)
{
  if(shift > 0)
  {
    data_t work_cont = cont;
    u8 work_shift    = shift;
    u8 part_bit_size = sizeof(*cont.cont)*8;

    /* Shift array element while shift more than one element size */
    u8 idx = SPU_WEIGHT-1;
    while(work_shift >= part_bit_size)
    {
      data_t unshifted_cont = work_cont;
      work_cont[idx] = 0;
      for(u8 i=idx; i>0; i--)
      {
        work_cont[i-1] = unshifted_cont[i];
      }
      work_shift -= part_bit_size;
      idx--;
    }

    if (shift == 0)
    {
      return work_cont;
    }

    /* Shift inside every element of array */
    data_t ret     = 0;
    u8 shifted_out = 0;
    for(u8 i=SPU_WEIGHT; i>0; i--)
    {
      ret[i-1] = (work_cont[i-1] >> work_shift) | shifted_out;
      shifted_out = work_cont[i-1] << (part_bit_size - work_shift);
    }

    return ret;
  }
  else
  {
    return cont;
  }
}

} /* namespace SPU */