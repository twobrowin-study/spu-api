/*
  simulator.cpp
        - SPU simulator implementation

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

#ifdef SPU_SIMULATOR

#include "simulator.hpp"

#include <algorithm>

namespace SPU
{

/* Simulating GSID generation */
gsid_t getNextGsid()
{
  static gsid_t gsid = {0};
  ++gsid;
  return gsid;
}

/***************************************
  Simulator class implementation
***************************************/

/* Constructor */
Simulator::Simulator()
{
  gsid = getNextGsid();
  _data = new std::map<key_t, value_t>();
}

/* Destructor */
Simulator::~Simulator()
{
  delete _data;
}

/* Get structure power */
u32 Simulator::get_power()
{
  return _data->size();
}

/* INS command execution */
status_t Simulator::insert(key_t key, value_t value, flags_t flags)
{
  auto res = _data->emplace(key, value);

  /* If new val was not incerted than we should change it */
  if (res.second == false)
  {
    res.first->second = value;
  }

  return OK;
}

/* DEL command execution */
status_t Simulator::del(key_t key, flags_t flags)
{
  _data->erase(key);
  return OK;
}

/* SRCH command execution */
pair_t Simulator::search(key_t key, flags_t flags)
{
  auto it = _data->find(key);
  if (it != _data->end())
  {
    return { key, it->second };
  }
  else
  {
    return { ERR };
  }
}

/* MIN command execution */
pair_t Simulator::min(flags_t flags)
{
  auto it = _data->begin();
  if (it != _data->end())
  {
    return { it->first, it->second };
  }
  else
  {
    return { ERR };
  }
}

/* MAX command execution */
pair_t Simulator::max(flags_t flags)
{
  auto it = _data->rbegin();
  if (it != _data->rend())
  {
    return { it->first, it->second };
  }
  else
  {
    return { ERR };
  }
}

/* NEXT command execution */
pair_t Simulator::next(key_t key, flags_t flags)
{
  auto it = _data->find(key);
  if (it != _data->end())
  {
    ++it;
    if (it != _data->end())
    {
      return { it->first, it->second };
    }
    else
    {
      return { ERR };
    }
  }
  else
  {
    return { ERR };
  }
}

/* PREV command execution */
pair_t Simulator::prev(key_t key, flags_t flags)
{
  auto it = _data->find(key);
  if (it != _data->end())
  {
    --it;
    if (it != _data->end())
    {
      return { it->first, it->second };
    }
    else
    {
      return { ERR };
    }
  }
  else
  {
    return { ERR };
  }
}

/* Next Smaller command execution */
pair_t Simulator::nsm(key_t key, flags_t flags)
{
  auto it = _data->lower_bound(key);
  --it;
  if (it != _data->end())
  {
    return { it->first, it->second };
  }
  else
  {
    return { ERR };
  }
}

/* Next Greater command execution */
pair_t Simulator::ngr(key_t key, flags_t flags)
{
  auto it = _data->upper_bound(key);
  if (it != _data->end())
  {
    return { it->first, it->second };
  }
  else
  {
    return { ERR };
  }
}

} /* namespace SPU */

#endif /* SPU_SIMULATOR */