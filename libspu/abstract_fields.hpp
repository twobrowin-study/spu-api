/*
  abstract_fields.hpp
        - abstract fields interface class

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

#ifndef ABSTRACT_FIELDS_HPP
#define ABSTRACT_FIELDS_HPP

#include "libspu.hpp"
#include "fields_containers.hpp"

namespace SPU
{

/* Abstract Fields interface */
template <typename NameT>
class AbstractFields
{
protected:
  /* Types */
  using Length = FieldsLength<NameT>;
  using Data   = FieldsData<NameT>;

public:
  /* Virtual destructor */
  virtual ~AbstractFields() {};

  /* data_t transform operator */
  virtual operator data_t() = 0;

  /* Set data_t for fields data */
  virtual AbstractFields& operator= (data_t fields_data) = 0;

  /* Set Data for fields data */
  virtual AbstractFields& operator= (Data fields_data) = 0;

  /* Subscript operators */
  virtual data_t& operator[](NameT name) = 0;

};


/* void Abstract Fields witch cannot be set */
template<>
class AbstractFields<void>
{
  template <typename T>
  inline AbstractFields& operator=(T any)
  {
    return *this;
  }
};

} /* namespace SPU */

#endif /* ABSTRACT_FIELDS_HPP */