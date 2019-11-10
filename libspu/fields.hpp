/*
  fields.hpp
        - declaration of class necessary for data_t fields split

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

#ifndef FIELDS_HPP
#define FIELDS_HPP

#include "libspu.hpp"
#include "abstract_fields.hpp"
#include "errors/no_fields_data.hpp"

namespace SPU
{

/* Fields splited data_t */
template <typename NameT = u8>
class Fields : public AbstractFields<NameT>
{
private:
  /* Types */
  using Length = typename AbstractFields<NameT>::Length;
  using Data   = typename AbstractFields<NameT>::Data;
  Length length;       // Length
  Data   data; // Data

public:
  /* Constructor */
  Fields(Length fields_length): AbstractFields<NameT>(), length(fields_length)
  {
    for ( auto ex : length )
    {
      data.push( {ex.name, 0} );
    }
  }

  /* data_t transform operator */
  operator data_t() override
  {
    data_t ret = 0;
    u8 shift   = 0;
    for(auto ex : length)
    {
      try
      {
        ret = ret | ( ( data[ex.name] & Length::mask(ex.length) ) << shift );
      }
      catch(DidNotFoundDataByName<NameT>&) {}
      shift += ex.length;
    }
    return ret;
  }

  /* Set data_t for fields data */
  Fields& operator= (data_t fields_data) override
  {
    data.clear();

    u8 shift = 0;
    for ( auto ex : length )
    {
      data_t mask = Length::mask(ex.length);
      data_t flow = ( fields_data >> shift ) & mask;
      data.push( {ex.name, flow} );
      shift += ex.length;
    }

    return *this;
  }

  /* Set Data for fields data */
  Fields& operator= (Data fields_data) override
  {
    data.clear();

    for ( auto ex : fields_data )
    {
      data_t flow = ex.data & length.fieldMask(ex.name);
      data.push( {ex.name, flow} );
    }

    return *this;
  }

  /* Subscript operator */
  data_t& operator[](NameT name) override { return data[name]; }

  /* Friends functions used int foreach cycle */
  friend auto begin(Fields<NameT>& fields) { return begin(fields.data); }
  friend auto end(Fields<NameT>&   fields) { return end(fields.data);   }

};


/* void Fields class */
template<>
class Fields<void> : public AbstractFields<void> {};

} /* namespace SPU */

#endif /* FIELDS_HPP */