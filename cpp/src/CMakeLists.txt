cmake_minimum_required(VERSION 3.2)
project(keyfile-test LANGUAGES CXX)
message("-- [SRC] Adding key.cmake")
include(key.cmake)

message("-- [SRC] Adding Compiler Flags")
list(APPEND flags "-g" "-Wall")
add_compile_options(${flags})

message("-- [SRC] Adding Sources")
add_executable(test 
    test.cpp
    ${key_src})