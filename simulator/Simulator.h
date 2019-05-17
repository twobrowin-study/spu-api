//
// Created by a.kiryanenko on 2019-05-17.
//

#ifndef GRAPH_API_SIMULATOR_H
#define GRAPH_API_SIMULATOR_H


#include <map>
#include "../libspu/base_structure.hpp"

using namespace std;

namespace SPU
{

    class Simulator : public BaseStructure {
        map<key_t, value_t> _data;

    public:
        u32 get_power () override;
        status_t insert (key_t key, value_t value, flags_t flags = NO_FLAGS) override;
        status_t del (key_t key, flags_t flags = NO_FLAGS) override;
        pair_t search (key_t key, flags_t flags = P_FLAG) override;
        pair_t min (flags_t flags = P_FLAG) override;
        pair_t max (flags_t flags = P_FLAG) override;
        pair_t next (key_t key, flags_t flags = P_FLAG) override;
        pair_t prev (key_t key, flags_t flags = P_FLAG) override;
        pair_t nsm (key_t key, flags_t flags = P_FLAG) override;
        pair_t ngr (key_t key, flags_t flags = P_FLAG) override;
    };

}

#endif //GRAPH_API_SIMULATOR_H
