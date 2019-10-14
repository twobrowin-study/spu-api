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
#include "errors/no_fields_data.hpp"

namespace SPU
{

/* Fields splited data_t */
template <typename NameT = u8>
class Fields
{
private:
  /* Types */
  using Length = FieldsLength<NameT>;
  using Data   = FieldsData<NameT>;

  Length length;       // Length
  Data   *data = NULL; // Data

protected:

  /* Check for data instance */
  void check_data()
  {
    if (!data)
    {
      throw NoFieldsData();
    }
  }

  /* Delete Data instance */
  void clear_data()
  {
    if (data)
    {
      delete data;
    }
  }

public:
  /* Constructor */
  Fields(Length fields_length): length(fields_length)
  {
    data = new Data();
    for ( auto ex : length )
    {
      data->push( {ex.name, 0} );
    }
  }
  
  /* Destructor */
  ~Fields()
  { 
    clear_data();
  }

  /* data_t transform operator */
  operator data_t()
  {
    check_data();

    data_t ret = 0;
    u8 shift   = 0;
    for(auto ex : length)
    {
      try
      {
        ret = ret | ( ( (*data)[ex.name] & Length::mask(ex.length) ) << shift );
      }
      catch(DidNotFoundDataByName<NameT>&) {}
      shift += ex.length;
    }
    return ret;
  }

  Fields& operator= (data_t fields_data)
  {
    clear_data();
    data = new Data();

    u8 shift = 0;
    for ( auto ex : length )
    {
      data_t mask = Length::mask(ex.length);
      data_t flow = ( fields_data >> shift ) & mask;
      data->push( {ex.name, flow} );
      shift += ex.length;
    }

    return *this;
  }

  Fields& operator= (Data fields_data)
  {
    clear_data();
    data = new Data();
    
    for ( auto ex : fields_data )
    {
      data_t flow = ex.data & length[ex.name];
      data->push( {ex.name, flow} );
    }

    return *this;
  }

  /* Subscript operators */
  const data_t& operator[](NameT name) const { check_data(); return (*data)[name]; }
        data_t& operator[](NameT name)       { check_data(); return (*data)[name]; }

  /* Friends functions used int foreach cycle */
  friend auto begin(Fields<NameT>& fields) { fields.check_data(); return begin(*fields.data); }
  friend auto end(Fields<NameT>& fields)   { fields.check_data(); return end(*fields.data);   }

};


/* void Fields class */
template<>
class Fields<void>
{};

} /* namespace SPU */

#endif /* FIELDS_HPP */