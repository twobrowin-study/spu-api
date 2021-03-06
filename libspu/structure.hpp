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
#include "fields_pointer.hpp"

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
template<typename KeyNameT = void, typename ValueNameT = void>
class Structure: public BaseStructureClass
{
private:
  /* Types */
  using Key          = Fields<KeyNameT>;
  using Value        = Fields<ValueNameT>;
  using KeyPointer   = FieldsPointer<KeyNameT>;
  using ValuePointer = FieldsPointer<ValueNameT>;
  using KeyLength    = FieldsLength<KeyNameT>;
  using ValueLength  = FieldsLength<ValueNameT>;
  using KeyData      = FieldsData<KeyNameT>;
  using ValueData    = FieldsData<ValueNameT>;

  /* Fields length keepers */
  KeyPointer   _key;
  ValuePointer _value;

protected:
  /* Set pair data to Fields if success */
  pair_t set_pair(pair_t pair)
  {
    if (pair.status == OK)
    {
      _key   = pair.key;
      _value = pair.value;
    }
    return pair;
  }

public:
  /*************************************
    Constructors and destructor
  *************************************/
  Structure(KeyLength key_length, bool is_val_constr = false) : BaseStructureClass(),
                                                                _key(new Key(key_length)) {}

  Structure(ValueLength value_length) : BaseStructureClass(),
                                        _value(new Value(value_length)) {}

  Structure(KeyLength key_length, ValueLength value_length) : BaseStructureClass(),
                                                              _key(new Key(key_length)),
                                                              _value(new Value(value_length)) {}

  /*************************************
    Fields interface methods
  *************************************/
  KeyPointer key()
  {
    return _key;
  }

  ValuePointer value()
  {
    return _value;
  }


  /*************************************
    Redefinitions of BaseStructure
    commands with composite key
  *************************************/

  /* Insert */
  status_t insert(key_t   key, value_t   value, flags_t flags = NO_FLAGS) { _key = key; _value = value; return BaseStructureClass::insert( key,  value, flags); }
  status_t insert(KeyData key, value_t   value, flags_t flags = NO_FLAGS) { _key = key; _value = value; return BaseStructureClass::insert(_key,  value, flags); }
  status_t insert(key_t   key, ValueData value, flags_t flags = NO_FLAGS) { _key = key; _value = value; return BaseStructureClass::insert( key, _value, flags); }
  status_t insert(KeyData key, ValueData value, flags_t flags = NO_FLAGS) { _key = key; _value = value; return BaseStructureClass::insert(_key, _value, flags); }

  /* Delete */
  status_t del(key_t   key, flags_t flags = NO_FLAGS) { _key = key; return BaseStructureClass::del( key, flags); }
  status_t del(KeyData key, flags_t flags = NO_FLAGS) { _key = key; return BaseStructureClass::del(_key, flags); }

  /* Search */
  pair_t search(key_t   key, flags_t flags = P_FLAG) {             return set_pair ( BaseStructureClass::search( key, flags) ); }
  pair_t search(KeyData key, flags_t flags = P_FLAG) { _key = key; return set_pair ( BaseStructureClass::search(_key, flags) ); }

  /* Min */
  pair_t min(flags_t flags = P_FLAG) { return set_pair ( BaseStructureClass::min(flags) ); }

  /* Max */
  pair_t max(flags_t flags = P_FLAG) { return set_pair ( BaseStructureClass::max(flags) ); }

  /* Next */
  pair_t next(key_t   key, flags_t flags = P_FLAG) {             return set_pair ( BaseStructureClass::next( key, flags) ); }
  pair_t next(KeyData key, flags_t flags = P_FLAG) { _key = key; return set_pair ( BaseStructureClass::next(_key, flags) ); }

  /* Prev */
  pair_t prev(key_t   key, flags_t flags = P_FLAG) {             return set_pair ( BaseStructureClass::prev( key, flags) ); }
  pair_t prev(KeyData key, flags_t flags = P_FLAG) { _key = key; return set_pair ( BaseStructureClass::prev(_key, flags) ); }

  /* NSM */
  pair_t nsm(key_t   key, flags_t flags = P_FLAG) {             return set_pair ( BaseStructureClass::nsm( key, flags) ); }
  pair_t nsm(KeyData key, flags_t flags = P_FLAG) { _key = key; return set_pair ( BaseStructureClass::nsm(_key, flags) ); }

  /* NGR */
  pair_t ngr(key_t   key, flags_t flags = P_FLAG) {             return set_pair ( BaseStructureClass::ngr( key, flags) ); }
  pair_t ngr(KeyData key, flags_t flags = P_FLAG) { _key = key; return set_pair ( BaseStructureClass::ngr(_key, flags) ); }
};


/***************************************
  Structure<> class declaration
***************************************/
template<>
class Structure<void, void> : public BaseStructureClass {};

} /* namespace SPU */

#endif /* STRUCTURE_HPP */