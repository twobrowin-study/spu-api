//
// Created by a.kiryanenko on 2019-05-21.
//

#include "extern_value.h"

namespace SPU
{
  std::map<gsid_t, std::map<key_t, BaseExternValue>> structure_values;


  void BaseExternValue::insert(SPU::gsid_t gsid, SPU::key_t key, SPU::BaseExternValue &value)
  {
    auto it = structure_values.find(gsid);
    if (it == structure_values.end()) {
      structure_values[gsid] = std::map<key_t, BaseExternValue>();
    }

    structure_values[gsid][key] = value;
  }

  void BaseExternValue::remove(gsid_t gsid, key_t key) {
    auto it = structure_values.find(gsid);
    if (it == structure_values.end()) {
      return;
    }

    structure_values[gsid].erase(key);
  }

  value_t BaseExternValue::get_id() {
    return _id;
  }

  void BaseExternValue::set_id(value_t id) {
    _id = id;
  }

  BaseExternValue::BaseExternValue() {
    _id = get_next_id();
  }

  value_t BaseExternValue::get_next_id() {
    static value_t next_id = {0};
    return ++next_id;
  }
}

