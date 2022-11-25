cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
option(LIBGEN "Generate Shared Library" OFF)
if(LIBGEN)
    message("-- [SRC] key.cmake: Generating shared library files.")
    add_library(keyfileobj
                SHARED
                key/key.cpp
                key/key.h)
    set_target_properties(keyfileobj
                          PROPERTIES
                          POSITION_INDEPENDENT_CODE 1)
endif(LIBGEN)

set(key_srcs
    key/key.cpp)