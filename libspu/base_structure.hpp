/*
  base_structure.hpp
        - base structure class declaration
        - structure is the main concept in whole SPU API
        - structure is a set of key-value pairs
        - this class defines and implements all structure methods without any key portion mechanism

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

#ifndef BASE_STRUCTURE_HPP
#define BASE_STRUCTURE_HPP

#include "abstract_structure.hpp"
#include "fileops.hpp"
#include "errors/could_not_create_structure.hpp"

namespace SPU
{

/***************************************
  BaseStructure class declaration
***************************************/

/* Structure in SPU */
class BaseStructure : public AbstractStructure
{
private:
  Fileops fops; // File operations provider
  u32 power;    // Current structure power

protected:
  adds_rslt_t adds() override;
  dels_rslt_t dels() override;

public:
  BaseStructure();
  ~BaseStructure() override;

  u32 get_power() override;

  status_t insert(key_t key, value_t value, flags_t flags = NO_FLAGS) override;
  status_t del(key_t key, flags_t flags = NO_FLAGS) override;
  pair_t search(key_t key, flags_t flags = P_FLAG) override;
  pair_t min(flags_t flags = P_FLAG) override;
  pair_t max(flags_t flags = P_FLAG) override;
  pair_t next(key_t key, flags_t flags = P_FLAG) override;
  pair_t prev(key_t key, flags_t flags = P_FLAG) override;
  pair_t nsm(key_t key, flags_t flags = P_FLAG) override;
  pair_t ngr(key_t key, flags_t flags = P_FLAG) override;
};

} /* namespace SPU */

#endif /* BASE_STRUCTURE_HPP */