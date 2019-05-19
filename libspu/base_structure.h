/*
  base_structure.hpp
        - base structure class declaration and implementation
        - structure is the main concept in whole SPU API
        - structure is a set of key-value pairs
        - this class defines and implements all structure methods without any key portion mechanism

  Copyright 2019  Dubrovin Egor <dubrovin.en@ya.ru>
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

#include "libspu.h"
#include "fileops.hpp"
#include "errors/could_not_create_structure.hpp"

#include <vector>

namespace SPU
{

/***************************************
  BaseStructure class declaration
***************************************/

/* Structure in SPU */
class BaseStructure
{
public:
  struct InsertStruct
  {
    key_t   key;
    value_t value;
  };
  using InsertVector = std::vector<InsertStruct>;

private:
  gsid_t gsid = { 0 };       // Global Structure ID
  Fileops fops;              // File operations provider
  u32 power;                 // Current structure power

public:
  explicit BaseStructure(bool initialize=true);
  virtual ~BaseStructure();

  gsid_t get_gsid();
  virtual u32 get_power();

  void init();

  /// выполняет поиск значения, связанного с ключом
  virtual status_t insert(key_t key, value_t value, flags_t flags = NO_FLAGS);
  status_t insert (InsertVector insert_vector, flags_t flags = NO_FLAGS);
  /// выполняет поиск указанного ключа и удаляет его из структуры данных
  virtual status_t del(key_t key, flags_t flags = NO_FLAGS);
  /// выполняет поиск значения, связанного с ключом
  virtual pair_t search(key_t key, flags_t flags = P_FLAG);
  /// ищет первый ключ в структуре данных
  virtual pair_t min(flags_t flags = P_FLAG);
  /// ищет последний ключ в структуре данных
  virtual pair_t max(flags_t flags = P_FLAG);
  /// находит соседний (следующий) ключ в структуре данных относительно переданного ключа.
  /// В связи с тем, что исходный ключ должен обязательно присутствовать в
  /// структуре данных, операции NEXT отличаются от NSM
  virtual pair_t next(key_t key, flags_t flags = P_FLAG);
  /// находит соседний (предыдущий) ключ в структуре данных относительно переданного ключа.
  /// В связи с тем, что исходный ключ должен обязательно присутствовать в
  /// структуре данных, операции PREV отличаются от NGR
  virtual pair_t prev(key_t key, flags_t flags = P_FLAG);
  /// выполняет поиск соседнего ключа, который меньше заданного и возвращает его значение.
  /// Операции могут быть использованы для эвристических вычислений,
  /// где интерполяция данных используется вместо точных вычислений (например, кластеризация или агрегация).
  virtual pair_t nsm(key_t key, flags_t flags = P_FLAG);
  /// выполняет поиск соседнего ключа, который больше заданного и возвращает его значение.
  /// Операции могут быть использованы для эвристических вычислений,
  /// где интерполяция данных используется вместо точных вычислений (например, кластеризация или агрегация).
  virtual pair_t ngr(key_t key, flags_t flags = P_FLAG);

protected:
  virtual adds_rslt_t createStructure();
  virtual dels_rslt_t deleteStructure();
};

} /* namespace SPU */

#endif /* BASE_STRUCTURE_HPP */