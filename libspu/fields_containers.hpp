/*
  fields_containers.hpp
        - presents fields_length and fields_data classes

  Copyright 2019  Dubrovin Egor <dubrovin.en@ya.ru>
                  Alexander Kiryanenko <kiryanenkoav@mail.ru>
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

#ifndef FIELDS_CONTAINERS_HPP
#define FIELDS_CONTAINERS_HPP

#include "libspu.hpp"
#include "errors/did_not_found_by_name.hpp"

#include <vector>

namespace SPU
{

/* Fields abstract data container */
template <typename NameT, typename ContentT>
class FieldsContainer
{
protected:
  /* Content types */
  struct ContentStruct
  {
    NameT name;

    /* Aliases */
    union
    {
      ContentT cont;
      ContentT data;
      ContentT length;
    };

    /* Constructors */
    ContentStruct() {}
    ContentStruct(NameT c_name, ContentT c_cont) : name(c_name), cont(c_cont) {}
  };
  using ContentVector = std::vector<ContentStruct>;

  /* Iterates in vector to find first data with equals name */
  inline ContentT& find_data_by_name(NameT name)
  {
    for (auto& ex : cont_vec)
    {
      if (ex.name == name)
      {
        return ex.cont;
      }
    }
    throw DidNotFoundDataByName<NameT>(ClName, name);
  }

  /* Push to add data */
  inline void push(ContentStruct addict)
  {
    cont_vec.push_back(addict);
  }

  inline void clear()
  {
    cont_vec.clear();
  }

private:
  ContentVector cont_vec; // Content vector
  std::string ClName;     // Class name to inform DidNotFoundDataByName error

public: /* Constructors */
  FieldsContainer(std::string ClassName) : cont_vec({0}), ClName(ClassName) {}

  FieldsContainer(ContentVector content_vector, std::string ClassName) :
    cont_vec(content_vector), ClName(ClassName) {}

  FieldsContainer(std::initializer_list<ContentStruct> content_initializer_list, std::string ClassName) :
    cont_vec(content_initializer_list), ClName(ClassName) {}

  /* Friends functions used int foreach cycle */
  friend auto begin(FieldsContainer<NameT, ContentT>& container) { return container.cont_vec.begin(); }
  friend auto end(FieldsContainer<NameT, ContentT>& container)   { return container.cont_vec.end();   }
};



/* Fields length definitions container */
template <typename NameT = u8>
class FieldsLength : public FieldsContainer<NameT, u8>
{
private:
  /* Content length types */
  typedef FieldsContainer<NameT, u8> Parent;

public:
  using LengthStruct = typename Parent::ContentStruct;
  using LengthVector = typename Parent::ContentVector;

  /* Constructors */
  FieldsLength() : Parent("FieldsLength") {}
  FieldsLength(LengthVector length_vector) : Parent(length_vector, "FieldsLength") {}
  FieldsLength(std::initializer_list<LengthStruct> length_initializer_list) : Parent(length_initializer_list, "FieldsLength") {}

  /* Mask creator */
  inline static data_t mask(u8& length)
  {
    return ~( (-1) << length );
  }

  data_t fieldMask(NameT name) { return mask( Parent::find_data_by_name(name) ); }

  const u8& operator[](NameT name) const { return Parent::find_data_by_name(name); }
        u8& operator[](NameT name)       { return Parent::find_data_by_name(name); }
};



/* Fields data definitions container */
template <typename NameT = u8>
class FieldsData  : public FieldsContainer<NameT, data_t>
{
private:
  /* Content data types */
  typedef FieldsContainer<NameT, data_t> Parent;
  using DataStruct = typename Parent::ContentStruct;
  using DataVector = typename Parent::ContentVector;

public:
  /* Constructors */
  FieldsData() : Parent("FieldsData") {}
  FieldsData(DataVector data_vector) : Parent(data_vector, "FieldsData") {}
  FieldsData(std::initializer_list<DataStruct> data_initializer_list) : Parent(data_initializer_list, "FieldsData") {}

  /* Addiction interface */
  void push(DataStruct addict)
  {
    Parent::push(addict);
  }

  void clear()
  {
    Parent::clear();
  }

  /* Subscript operators */
  const data_t& operator[](NameT name) const { return Parent::find_data_by_name(name); }
        data_t& operator[](NameT name)       { return Parent::find_data_by_name(name); }
};



/***************************************
  Fields data and length void
***************************************/
template<>
class FieldsLength<void> {};
template<>
class FieldsData<void> {};

} /* namespace SPU */

#endif /* FIELDS_CONTAINERS_HPP */