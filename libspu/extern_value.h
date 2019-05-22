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
    /// Функция должжна давать следующий свободный уникальный идентификатор
    value_t get_next_id();

  public:
    BaseExternValue();
    explicit BaseExternValue(value_t id) : _id(id) {}

    value_t get_id();
    void set_id(value_t id);
    /// Вызывается при добавлении новой структуры в SPU
    static void spu_insert(gsid_t gsid, key_t key, BaseExternValue &value);
    /// Вызывается при удалении или замещении структуры в SPU
    static void spu_remove(gsid_t gsid, key_t key);
  };

  extern std::map<gsid_t, std::map<key_t, BaseExternValue>> structure_values;


  /// Используя данный класс в качестве значений можно использовать крупные структуры (например строки)
  /// В SPU будет храниться идентификатор на них
  template <class T>
  class ExternValue : public BaseExternValue {
  public:
    ExternValue() : BaseExternValue() {}
    ExternValue(value_t id) : BaseExternValue(id) {}

    /// Возвращает структуру соответствующую id
    virtual T & get_value() = 0;
    virtual void insert(T value) = 0;

    operator T() { return get_value(); }
    ExternValue& operator<< (value_t id) {
      set_id(id);
      return *this;
    }
    ExternValue& operator<< (pair_t pair) {
      set_id(pair.value);
      return *this;
    }
    ExternValue& operator<< (T value) {
      insert(value);
      return *this;
    }
    T& operator>> (T value) { return get_value(); }
  };


  /// Используя данный класс в качестве значений можно использовать крупные структуры (например строки)
  /// В SPU будет храниться идентификатор на них, а данные будут храниться в оперативке
  template <class T>
  class HashMapExternValue : public ExternValue<T> {
    static std::map<value_t, T> _data;

  public:
    HashMapExternValue() : ExternValue<T>() {}
    /// Данный констуктор инициализирует id. Используется при получении данных из SPU.
    HashMapExternValue(value_t id) : ExternValue<T>(id) {}
    /// Данный констуктор инициализирует id. Используется при получении данных из SPU.
    HashMapExternValue(pair_t pair) : ExternValue<T>(pair.value) {}
    /// Данный констуктор должен записать данные.
    HashMapExternValue(T value) : ExternValue<T>() { insert(value); }
    T & get_value() override { return _data[BaseExternValue::get_id()]; }
    void insert(T value) override { _data[BaseExternValue::get_id()] = value; }
  };

  template <class T>
  std::map<value_t, T> HashMapExternValue<T>::_data = std::map<value_t, T>();
}

#endif //GRAPH_API_EXTERN_VALUE_H
