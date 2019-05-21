//
// Created by a.kiryanenko on 2019-05-21.
//

#ifndef GRAPH_API_EXTERN_VALUE_H
#define GRAPH_API_EXTERN_VALUE_H

#include <unordered_map>
#include <map>
#include "libspu.h"

namespace SPU
{
  class BaseExternValue {
    value_t _id;

  protected:
    void set_id(value_t id);
    /// Функция должжна давать следующий свободный уникальный идентификатор
    value_t get_next_id();

  public:
    BaseExternValue();
    explicit BaseExternValue(value_t id) : _id(id) {}

    value_t get_id();
    /// Вызывается при добавлении новой структуры в SPU
    static void insert(gsid_t gsid, key_t key, BaseExternValue &value);
    /// Вызывается при удалении или замещении структуры в SPU
    static void remove(gsid_t gsid, key_t key);
  };

  extern std::map<gsid_t, std::map<key_t, BaseExternValue>> structure_values;


  /// Используя данный класс в качестве значений можно использовать крупные структуры (например строки)
  /// В SPU будет храниться идентификатор на них
  template <class T>
  class ExternValue : public BaseExternValue {
  public:
    ExternValue() : BaseExternValue() {}
    /// Возвращает структуру соответствующую id
    virtual T & get_value() = 0;
    operator T() { return get_value(); }
  };


  /// Используя данный класс в качестве значений можно использовать крупные структуры (например строки)
  /// В SPU будет храниться идентификатор на них, а данные будут храниться в оперативке
  template <class T>
  class HashMapExternValue : public ExternValue<T> {
    static std::map<value_t, T> _data;

  public:
    HashMapExternValue(T value) : ExternValue<T>() { _data[BaseExternValue::get_id()] = value; }
    T & get_value() override { return _data[BaseExternValue::get_id()]; }
  };

}

#endif //GRAPH_API_EXTERN_VALUE_H
