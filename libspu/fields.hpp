/*
  fields.hpp
        - declaration of class necessary for data_t fields split

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

#ifndef FIELDS_HPP
#define FIELDS_HPP

#include "libspu.hpp"
#include "fields_containers.hpp"

namespace SPU
{

/* Fields splited data_t */
template <typename NameT>
class Fields
{
private:
  /* Types */
  using Length = FieldsLength<NameT>;
  using Data   = FieldsData<NameT>;

  Length length; // Length
  Data data;     // Data

  /* Data initializer from data flow */
  void init_data(data_t fields_data)
  {
    u8 shift = 0;
    for ( auto& ex : length )
    {
      data_t mask = Length::mask(ex.length);
      data_t flow = (fields_data >> shift) & mask;
      data.push( {ex.name, flow} );
      shift += ex.length;
    }
  }

  /* Data initializer from data fields */
  void init_data(Data fields_data)
  {
    for ( auto& ex : length )
    {
      data_t mask = Length::mask(ex.length);
      data_t flow = fields_data[ex.name] & mask;
      data.push( {ex.name, flow} );
    }
  }

  /* Data initializer from length fields */
  void init_data()
  {
    for ( auto& ex : length )
    {
      data.push( {ex.name, 0} );
    }
  }

public:
  /* Constructors, inited data via length masks */
  Fields(Length fields_length)                     : length(fields_length), data() { init_data();            }
  Fields(Length fields_length, Data fields_data)   : length(fields_length), data() { init_data(fields_data); }
  Fields(Length fields_length, data_t fields_data) : length(fields_length), data() { init_data(fields_data); }

  operator Data&()
  {
    return data;
  }

  /* data_t transform operator */
  operator data_t()
  {
    data_t ret = 0;
    u8 shift = 0;
    for(auto ex : length)
    {
      try
      {
        ret = ret | ( ( data[ex.name] & Length::mask(ex.length) ) << shift );
      }
      catch(DidNotFoundDataByName<NameT>&) {}
      shift += ex.cont;
    }
    return ret;
  }

  Fields& operator= (data_t fields_data)
  {
    init_data(fields_data);
    return *this;
  }

  Fields& operator= (Data fields_data)
  {
    data = fields_data;
    return *this;
  }

  /* Subscript operators */
  const data_t& operator[](NameT name) const { return data[name]; }
        data_t& operator[](NameT name)       { return data[name]; }

};

} /* namespace SPU */

#endif /* FIELDS_HPP */