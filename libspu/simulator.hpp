/*
  simulator.hpp
        - SPU base structure class re-implementation
        - based on map with O(log2(n)) difficulty

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

#ifndef SPU_SIMULATOR_HPP
#define SPU_SIMULATOR_HPP

#include "abstract_structure.hpp"

#include <map>
#include <glob.h>
#include <type_traits>
#include <unordered_map>

namespace SPU
{

/***************************************
  Hash func or something similar
***************************************/

template <typename T>
struct container_hash
{
  size_t operator() (const std::pair<int,int> &x)const
  {
    std::size_t h = 0;
    return std::hash <long long> () ( ( (long long) x.first ) ^ ( ( (long long) x.second ) <<32 ) );
  }
};



/***************************************
  Simulator class declaration
***************************************/

class Simulator : public AbstractStructure
{
private:
  std::map<key_t, value_t> *_data = nullptr; // Data of Structure

protected:
  /* Just to be a concrete class */
  adds_rslt_t adds() override { return { OK, gsid  }; };
  dels_rslt_t dels() override { return { OK, 0     }; };

public:
    Simulator();
    ~Simulator();

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

#endif /* SPU_SIMULATOR_HPP */

#endif /* SPU_SIMULATOR */
