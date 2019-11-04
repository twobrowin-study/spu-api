/*
  fields_pointer.hpp
        - fields smart pointer classes

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

#ifndef FIELDS_POINTER_HPP
#define FIELDS_POINTER_HPP

#include "libspu.hpp"
#include "fields.hpp"

namespace SPU
{

/* Fields smart pointer */
template <typename NameT>
class FieldsPointer : public AbstractFields<NameT>
{
private:
  using Data = typename AbstractFields<NameT>::Data;
  Fields<NameT>* _ptr; // Pointer
  bool del_ptr = true; // Flag to del pointer

public:
  /* Constructors */
  FieldsPointer(Fields<NameT>* fields_ptr): AbstractFields<NameT>(), _ptr(fields_ptr) {}
  FieldsPointer(const FieldsPointer& other): AbstractFields<NameT>(), _ptr(other._ptr), del_ptr(false) {}
  
  /* Destructor */
  ~FieldsPointer()
  {
    if ( del_ptr )
    {
      delete _ptr;
    }
  }

  /* data_t transform operator */
  inline operator data_t() override { return (*_ptr); }

  /* Set data_t for fields data */
  inline FieldsPointer& operator= (data_t fields_data) override { (*_ptr) = fields_data; return *this; }

  /* Set Data for fields data */
  inline FieldsPointer& operator= (Data fields_data) override { (*_ptr) = fields_data; return *this; }

  /* Subscript operator */
  inline data_t& operator[](NameT name) override { return (*_ptr)[name]; }

  /* Friends functions used int foreach cycle */
  friend auto begin(FieldsPointer<NameT>& fields_ptr) { return begin( *(fields_ptr._ptr) ); }
  friend auto end(FieldsPointer<NameT>&   fields_ptr) { return end( *(fields_ptr._ptr) );   }
};


/* void FieldsPointer class */
template<>
class FieldsPointer<void> : public AbstractFields<void> {};

} /* namespace SPU */

#endif /* FIELDS_POINTER_HPP */