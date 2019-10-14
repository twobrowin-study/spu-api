/*
  libspu.hpp
        - implementation for all to-string converters

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

#include "libspu.hpp"

namespace SPU
{
  
/* Convert GSID to string */
std::string to_string(gsid_t gsid)
{
  char buf[100];
  snprintf(buf, sizeof(buf), GSID_FORMAT, GSID_VAR(gsid));
  return std::string(buf);
}

/* Convert data container to string */
std::string to_string(data_t data, bool hex)
{
  std::string ret;
  const char *format = hex ? "%08x-" : "%d-"; // Choose if it hex or decimal

  for(u8 i=1; i<SPU_WEIGHT+1; i++)
  {
    char buf[100];
    snprintf(buf, sizeof(buf), format, data[SPU_WEIGHT-i]);
    ret += buf;
  }
  return ret.substr(0, ret.size()-1);
}

/* Convert result into string */
std::string to_string(status_t status)
{
  /* Check if status is OK */
  if(status == OK)
  {
    return "OK";
  }

  std::string ret;

  /* If status is not OK find all parts */
  if(status & ERR)
  {
    ret += "ERR & ";
  }

  if(status & QERR)
  {
    ret += "QERR & ";
  }

  if(status & OERR)
  {
    ret += "OERR & ";
  }

  return ret.substr(0, ret.size()-3);
}

/* Convert key : value pair with status into string */
std::string to_string(pair_t pair, bool hex)
{
  return to_string(pair.status) + " : " + to_string(pair.key, hex) + " : " + to_string(pair.value, hex);
}

} /* namespace SPU */