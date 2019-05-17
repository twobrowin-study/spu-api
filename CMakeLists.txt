cmake_minimum_required(VERSION 3.14)
project(graph_api)

set(CMAKE_CXX_STANDARD 14)


set(SPU_ARCH 64)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -DSPU${SPU_ARCH}")

add_library(
        spu-api STATIC
        spu.h
        libspu/spu.h
        libspu/base_structure.hpp
        libspu/data_container_operators.hpp
        libspu/fields.hpp
        libspu/fields_containers.hpp
        libspu/fileops.hpp
        libspu/libspu.hpp
        libspu/structure.hpp
        libspu/errors/could_not_create_structure.hpp
        libspu/errors/did_not_found_by_name.hpp

        simulator/Simulator.cpp
        simulator/Simulator.h
)


set(SOURCE_EXE simulator/test.cpp)
add_executable(main ${SOURCE_EXE})
target_link_libraries(main spu-api)		# Линковка программы с библиотекой