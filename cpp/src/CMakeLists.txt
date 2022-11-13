cmake_minimum_required(VERSION 3.2)
project(keyfile-test)
message("-- [SRC] Adding key.cmake")
include(key.cmake)
add_executable(test 
    test.cpp
    ${key_src})