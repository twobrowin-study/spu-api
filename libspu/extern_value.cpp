/*
  extern_value.hpp
        - implementation of extern value class

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
#include "extern_value.hpp"

namespace SPU
{

/* Extern values keeper */
std::map<gsid_t, std::map<key_t, BaseExternValue>> structure_values; // TODO:  unordered_map

/* Incert extern value */
void BaseExternValue::spu_insert(gsid_t gsid, key_t key, BaseExternValue &value)
{
  auto it = structure_values.find(gsid);
  if (it == structure_values.end())
  {
    structure_values[gsid] = std::map<key_t, BaseExternValue>();
  }
  structure_values[gsid][key] = value;
}

/* Remove extern value */
void BaseExternValue::spu_remove(gsid_t gsid, key_t key)
{
  auto it = structure_values.find(gsid);
  if (it == structure_values.end())
  {
    return;
  }
  structure_values[gsid].erase(key);
}

/* Get a new free ID */
value_t BaseExternValue::get_next_id()
{
  static value_t next_id = {0};
  return ++next_id;
}

} /* namespace SPU */

