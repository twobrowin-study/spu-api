# CMakeLists.txt
#       - top build description file
#
# Copyright 2019  Dubrovin Egor <dubrovin.en@ya.ru>
#                 Aleksandr Kiryanenko <akiryanenko@mail.ru>
#                 Alex Popov <alexpopov@bmstu.ru>
#                 Bauman Moscow State Technical University
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.14)
project(spu-api)

########################################
# User setting
########################################

set(TARGET main.cpp) # WRITE YOUR FILE HERE
set(SPU_ARCH 64)
set(SPU_SIMULATOR ON)

########################################
# Rules
########################################

set(CMAKE_CXX_STANDARD 14)

if(${SPU_SIMULATOR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSPU_SIMULATOR")
endif(${SPU_SIMULATOR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -Wall -ggdb -DSPU${SPU_ARCH}")

include_directories(libspu)

add_library(
        spu-api STATIC
        libspu/spu.h
        libspu/libspu.hpp
        libspu/libspu.cpp
        libspu/containers_operators.hpp
        libspu/containers_operators.cpp

        libspu/abstract_structure.hpp
        libspu/base_structure.hpp
        libspu/base_structure.cpp
        libspu/simulator.cpp
        libspu/simulator.hpp
        libspu/structure.hpp
        
        libspu/fileops.hpp
        libspu/fields.hpp
        libspu/fields_containers.hpp
        libspu/extern_value.hpp
        libspu/extern_value.cpp
        
        libspu/errors/could_not_create_structure.hpp
        libspu/errors/did_not_found_by_name.hpp
)

add_executable(main ${TARGET})
target_link_libraries(main spu-api)