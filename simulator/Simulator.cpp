//
// Created by a.kiryanenko on 2019-05-17.
//

#include <algorithm>
#include "Simulator.h"

SPU::u32 SPU::Simulator::get_power() {
    return _data.size();
}

SPU::status_t SPU::Simulator::insert(SPU::key_t key, SPU::value_t value, SPU::flags_t flags) {
    _data[key] = value;
    return OK;
}

SPU::status_t SPU::Simulator::del(SPU::key_t key, SPU::flags_t flags) {
    _data.erase(key);
    return OK;
}

SPU::pair_t SPU::Simulator::search(SPU::key_t key, SPU::flags_t flags) {
    auto it = _data.find(key);
    if (it != _data.end()) {
        return pair_t(key, it->second);
    } else {
        return pair_t(ERR);
    }
}

SPU::pair_t SPU::Simulator::min(SPU::flags_t flags) {
    auto it = std::min_element(_data.begin(), _data.end());
    if (it != _data.end()) {
        return pair_t(it->first, it->second);
    } else {
        return pair_t(ERR);
    }
}

SPU::pair_t SPU::Simulator::max(SPU::flags_t flags) {
    auto it = std::max_element(_data.begin(), _data.end());
    if (it != _data.end()) {
        return pair_t(it->first, it->second);
    } else {
        return pair_t(ERR);
    }
}

SPU::pair_t SPU::Simulator::next(SPU::key_t key, SPU::flags_t flags) {
    return BaseStructure::next(key, flags);
}

SPU::pair_t SPU::Simulator::prev(SPU::key_t key, SPU::flags_t flags) {
    return BaseStructure::prev(key, flags);
}

SPU::pair_t SPU::Simulator::nsm(SPU::key_t key, SPU::flags_t flags) {
    return BaseStructure::nsm(key, flags);
}

SPU::pair_t SPU::Simulator::ngr(SPU::key_t key, SPU::flags_t flags) {
    return BaseStructure::ngr(key, flags);
}

