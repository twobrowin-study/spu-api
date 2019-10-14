/*
  errors/could_not_create_structure.hpp
        - error when there is no data in fields class

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

#ifndef NO_FIELDS_DATA_HPP
#define NO_FIELDS_DATA_HPP

#include <stdexcept>
#include <string>

namespace SPU
{

/* Exception throws when there is no chance to crate another new structure */
struct NoFieldsData : public std::exception
{
  const char * what () const throw ()
    {
      return "FeildsData instance was not found in Fields";
    }
};

} /* namespace SPU */

#endif /* NO_FIELDS_DATA_HPP */