/*
  abstract_structure.hpp
        - structure abstract class declaration
        - this is an interface for creation other structure classes
        - structure is the main concept in whole SPU API
        - structure is a set of key-value pairs

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

#ifndef ABSTRACT_STRUCTURE_HPP
#define ABSTRACT_STRUCTURE_HPP

#include "libspu.hpp"

#include <vector>

namespace SPU
{

/***************************************
  AbstractStructure class declaration
***************************************/

/* Structure in SPU */
class AbstractStructure
{
public:
  /* Vector type based on data_t */
  struct InsertStruct
  {
    key_t   key;
    value_t value;
  };
  using InsertVector = std::vector<InsertStruct>;

protected:
  gsid_t gsid = { 0 }; // Global Structure ID

  /* Inside commands */
  virtual adds_rslt_t adds() = 0;
  virtual dels_rslt_t dels() = 0;

public:
  virtual ~AbstractStructure() = default;

  /* Helpers */
  virtual u32 get_power() = 0;

  /* Supported SPU commands */
  virtual status_t insert(key_t key, value_t value, flags_t flags = NO_FLAGS) = 0;
  virtual status_t del(key_t key, flags_t flags = NO_FLAGS) = 0;
  virtual pair_t search(key_t key, flags_t flags = P_FLAG) = 0;
  virtual pair_t min(flags_t flags = P_FLAG) = 0;
  virtual pair_t max(flags_t flags = P_FLAG) = 0;
  virtual pair_t next(key_t key, flags_t flags = P_FLAG) = 0;
  virtual pair_t prev(key_t key, flags_t flags = P_FLAG) = 0;
  virtual pair_t nsm(key_t key, flags_t flags = P_FLAG) = 0;
  virtual pair_t ngr(key_t key, flags_t flags = P_FLAG) = 0;

  /* Get GSID */
  gsid_t get_gsid()
  {
      return this->gsid;
  }

  /* Insert with vector type */
  status_t insertVector(InsertVector insert_vector, flags_t flags = NO_FLAGS)
  {
    for(auto ex : insert_vector)
    {
        status_t status = insert(ex.key, ex.value, flags);
        if(status != OK)
        {
            return status;
        }
    }
    return OK;
  }
};

} /* namespace SPU */

#endif /* ABSTRACT_STRUCTURE_HPP */