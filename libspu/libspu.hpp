/*
  libspu.hpp
        - main SPU library include file
        - file defines containers for key and value data and some more type hiders
        - file presents BitFlow class
        - have all need to_string convertors

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

#ifndef LIBSPU_HPP
#define LIBSPU_HPP

#include <cstring>
#include <string>

#include "spu.h"
#include "containers_operators.hpp"

namespace SPU
{

/* SPU key-value pair with SPU's status type */
struct pair_containter
{
  key_t    key;
  value_t  value;
  status_t status;

  /* Constructor for interface needs */
  pair_containter(status_t s = OK) :                     key(0), value(0), status(s) {}
  pair_containter(key_t k, value_t v, status_t s = OK) : key(k), value(v), status(s) {}
};
typedef struct pair_containter pair_t;

/* To-string converters */
std::string to_string(gsid_t gsid);
std::string to_string(data_t data, bool hex = true);
std::string to_string(status_t status);
std::string to_string(pair_t pair, bool hex = true);

} /* namespace SPU */

#endif /* LIBSPU_HPP */