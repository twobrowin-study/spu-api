/*
  extern_value.hpp
        - declaration of extern value class to declare a complete object into SPU

  Copyright 2019  Dubrovin Egor <dubrovin.en@ya.ru>
                  Aleksandr Kiryanenko <akiryanenko@mail.ru>
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

#ifndef EXTERN_VALUE_H
#define EXTERN_VALUE_H

#include "libspu.hpp"

#include <unordered_map>
#include <map>

namespace SPU
{

/***************************************
  BaseExternValue class declaration
***************************************/

class BaseExternValue
{
private:
  value_t _id; // Data ID

public:
  /* Constructors */
  BaseExternValue() { _id = get_next_id(); }
  explicit BaseExternValue(value_t id) : _id(id) {}

  /* Provider functions */
  value_t get_id()        { return _id; }
  void set_id(value_t id) { _id = id; }

  /* This methods should be used after SPU updates */
  static void spu_insert(gsid_t gsid, key_t key, BaseExternValue &value);
  static void spu_remove(gsid_t gsid, key_t key);

protected:
  value_t get_next_id(); // ID generator
};

extern std::map<gsid_t, std::map<key_t, BaseExternValue>> structure_values; // TODO:  unordered_map



/***************************************
  ExternValue class declaration
  This class is used to keep values
  in memory as like strings
***************************************/

template <class T>
class ExternValue : public BaseExternValue
{
public:
  /* Constructors */
  ExternValue() : BaseExternValue() {}
  ExternValue(value_t id) : BaseExternValue(id) {}

  /* Abstract Get Set value */
  virtual T & get() = 0;
  virtual void set(T value) = 0;


  /*************************************
    Some operators
  *************************************/

  operator T() { return get(); }
  
  ExternValue& operator<< (value_t id)
  {
    set_id(id);
    return *this;
  }
  
  ExternValue& operator<< (pair_t pair)
  {
    set_id(pair.value);
    return *this;
  }
  
  ExternValue& operator<< (T value)
  {
    set(value);
    return *this;
  }
  
  T& operator>> (T value) { return get(); }
};



/***************************************
  Hash based ExternVAlue class
***************************************/

template <class T>
class HashMapExternValue : public ExternValue<T>
{
private:
  static std::map<value_t, T> _data; // TODO:  unordered_map

public:
  /* Constructors */
  HashMapExternValue()            : ExternValue<T>() {}
  HashMapExternValue(value_t id)  : ExternValue<T>(id) {}            // Set the ID
  HashMapExternValue(pair_t pair) : ExternValue<T>(pair.value) {}
  HashMapExternValue(T value)     : ExternValue<T>() { set(value); } // Set the Data

  /* Get Set */
  T & get()         override { return _data[BaseExternValue::get_id()]; }
  void set(T value) override { _data[BaseExternValue::get_id()] = value; }
};

template <class T>
std::map<value_t, T> HashMapExternValue<T>::_data = std::map<value_t, T>(); // TODO: unordered_map

} /* namespace SPU */

#endif /* EXTERN_VALUE_H */
