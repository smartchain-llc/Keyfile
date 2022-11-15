cmake_minimum_required(VERSION 3.2)
project(keyfile-test LANGUAGES CXX)
message("-- [SRC] Adding key.cmake")
include(key/key.cmake)

message("-- [SRC] Adding Compiler Flags")
list(APPEND flags "-Wall")

option(GDB_DEBUG_SYMBOLS "Enable Debug Symbols for GDB" OFF)
if(GDB_DEBUG_SYMBOLS)
    message("-- [SRC] DEBUG ENABLED")
    list(APPEND flags "-g")
endif()

add_compile_options(${flags})

message("-- [SRC] Adding Sources")
add_executable(keyfile 
                binary.cpp 
                ${key_srcs})