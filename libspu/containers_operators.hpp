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

#ifndef CONTAINERS_OPERATIONS_HPP
#define CONTAINERS_OPERATIONS_HPP

#include "libspu.hpp"

namespace SPU
{

/***************************************
  data_t operators
***************************************/ 

/* Compare */
bool operator== (const data_t &c1, const data_t &c2);
bool operator!= (const data_t &c1, const data_t &c2);
bool operator>  (const data_t &c1, const data_t &c2);
bool operator>= (const data_t &c1, const data_t &c2);
bool operator<  (const data_t &c1, const data_t &c2);
bool operator<= (const data_t &c1, const data_t &c2);

/* Arithmetic */
data_t       operator+ (const data_t &c1, const data_t &c2);
data_t       operator- (const data_t &c1, const data_t &c2);
data_t       operator+ (const data_t &c1, int c2);
data_t       operator- (const data_t &c1, int c2);

/* Increment/Decrement */
data_t &     operator++ (data_t &c1);
const data_t operator++ (data_t &c1, int);
data_t &     operator-- (data_t &c1);
const data_t operator-- (data_t &c1, int);

/* Bit operation */
data_t operator& (const data_t &c1, const data_t &c2);
data_t operator| (const data_t &c1, const data_t &c2);
data_t operator^ (const data_t &c1, const data_t &c2);
data_t operator~ (const data_t &c1);

/* Shifts */
data_t operator<< (const data_t &cont, const u8 &shift);
data_t operator>> (const data_t &cont, const u8 &shift);



/***************************************
  gsid_t operators
***************************************/ 

/* Compare */
bool operator== (const gsid_t &c1, const gsid_t &c2);
bool operator!= (const gsid_t &c1, const gsid_t &c2);
bool operator>  (const gsid_t &c1, const gsid_t &c2);
bool operator>= (const gsid_t &c1, const gsid_t &c2);
bool operator<  (const gsid_t &c1, const gsid_t &c2);
bool operator<= (const gsid_t &c1, const gsid_t &c2);

/* Arithmetic */
gsid_t       operator+ (const gsid_t &c1, const gsid_t &c2);
gsid_t       operator- (const gsid_t &c1, const gsid_t &c2);

/* Increment/Decrement */
gsid_t &     operator++ (gsid_t &c1);
const gsid_t operator++ (gsid_t &c1, int);
gsid_t &     operator-- (gsid_t &c1);
const gsid_t operator-- (gsid_t &c1, int);

/* Bit operation */
gsid_t operator& (const gsid_t &c1, const gsid_t &c2);
gsid_t operator| (const gsid_t &c1, const gsid_t &c2);
gsid_t operator^ (const gsid_t &c1, const gsid_t &c2);
gsid_t operator~ (const gsid_t &c1);



/***************************************
  Operations on containers
***************************************/
template<class T>     int cmpContainers (T &c1, T &c2);
template <typename T> T   addContainers (T &c1, T &c2);
template <typename T> T   subContainers (T &c1, T &c2);
template <class T>    T & incContainer  (T &c1);
template <class T>    T & decContainer  (T &c1);
template <typename T> T   andContainers (const T &c1, const T &c2);
template <typename T> T   orContainers  (T &c1, T &c2);
template <typename T> T   xorContainers (T &c1, T &c2);
template <typename T> T   notContainers (T &c1);

} /* namespace SPU */

#endif /* CONTAINERS_OPERATIONS_HPP */
