/*
  structure.hpp
        - definitions of structure template class with it's void specialization
        - this is the base interface class in SPU library

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

#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <vector>

#include "libspu.hpp"
#include "fields.hpp"
#include "extern_value.hpp"

/* Including base or simulator */
#ifndef SPU_SIMULATOR
#include "base_structure.hpp"
#else
#include "simulator.hpp"
#endif /* SPU_SIMULATOR */

namespace SPU
{

/* Using base or simulator */
#ifndef SPU_SIMULATOR
using BaseStructureClass = BaseStructure;
#else
using BaseStructureClass = Simulator;
#endif /* SPU_SIMULATOR */

/***************************************
  Structure template class declaration
***************************************/

/* Template Structure class definition */
template<typename NameT = void>
class Structure: public BaseStructureClass
{
public:
  struct InsertStruct
  {
    FieldsData<NameT> key_data;
    data_t            value;
  };
  using InsertVector = std::vector<InsertStruct>;

private:
  FieldsLength<NameT> key_len;

public:
  Structure(FieldsLength<NameT> key_length) : BaseStructureClass(), key_len(key_length) {}

  Fields<NameT> keyFields()
  {
    return Fields<NameT>(key_len);
  }

  /*************************************
    Parent's methods usage
  *************************************/
  using BaseStructureClass::insert;
  using BaseStructureClass::insertVector;
  using BaseStructureClass::del;
  using BaseStructureClass::search;
  using BaseStructureClass::min;
  using BaseStructureClass::max;
  using BaseStructureClass::next;
  using BaseStructureClass::prev;
  using BaseStructureClass::nsm;
  using BaseStructureClass::ngr;


  /*************************************
    Redefinitions of BaseStructure
    commands with composite key
  *************************************/

  /* Insert */
  status_t insert(data_t key, BaseExternValue value, flags_t flags = NO_FLAGS)            { return insert(key, value.get_id(), flags); }
  status_t insert(FieldsData<NameT> key, BaseExternValue value, flags_t flags = NO_FLAGS) { return insert(key, value.get_id(), flags); }
  status_t insert(FieldsData<NameT> key_data, data_t value, flags_t flags = NO_FLAGS)
  {
    Fields<NameT> key(key_len, key_data);
    return BaseStructureClass::insert(key, value, flags);
  }
  status_t insertVector(InsertVector insert_vector, flags_t flags = NO_FLAGS)
  {
    for(auto ex : insert_vector)
    {
      status_t status = insert(ex.key_data, ex.value, flags);
      if(status != OK)
      {
        return status;
      }
    }
    return OK;
  }

  /* Delete */
  status_t del(FieldsData<NameT> key_data, flags_t flags = NO_FLAGS)
  {
    Fields<NameT> key(key_len, key_data);
    return BaseStructureClass::del(key, flags);
  }

  /* Search */
  pair_t search(FieldsData<NameT> key_data, flags_t flags = P_FLAG)
  {
    Fields<NameT> key(key_len, key_data);
    return BaseStructureClass::search(key, flags);
  }

  /* Next */
  pair_t next(FieldsData<NameT> key_data, flags_t flags = P_FLAG)
  {
    Fields<NameT> key(key_len, key_data);
    return BaseStructureClass::next(key, flags);
  }

  /* Prev */
  pair_t prev(FieldsData<NameT> key_data, flags_t flags = P_FLAG)
  {
    Fields<NameT> key(key_len, key_data);
    return BaseStructureClass::prev(key, flags);
  }

  /* NSM */
  pair_t nsm(FieldsData<NameT> key_data, flags_t flags = P_FLAG)
  {
    Fields<NameT> key(key_len, key_data);
    return BaseStructureClass::nsm(key, flags);
  }

  /* NGR */
  pair_t ngr(FieldsData<NameT> key_data, flags_t flags = P_FLAG)
  {
    Fields<NameT> key(key_len, key_data);
    return BaseStructureClass::ngr(key, flags);
  }
};


/***************************************
  Structure special class declaration
***************************************/
template<>
class Structure<void> : public BaseStructureClass {};

} /* namespace SPU */

#endif /* STRUCTURE_HPP */