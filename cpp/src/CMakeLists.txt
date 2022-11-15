cmake_minimum_required(VERSION 3.2)
project(keyfile-test LANGUAGES CXX)
set(msg-head "-- [SRC] ")
message(${msg-head} "Adding key.cmake")
include(key/key.cmake)

message(${msg-head} "Adding Compiler Flags")
list(APPEND flags "-Wall")

option(GDB_SYMBOLS "Enable Debug Symbols for GDB" OFF)
if(GDB_SYMBOLS)
    message(${msg-head} "DEBUG ENABLED")
    list(APPEND flags "-g")
endif()

add_compile_options(${flags})

message(${msg-head} "Adding Sources")
add_executable(keyfile
                ${key_srcs})
if(LIBGEN)
    target_link_libraries(keyfile keyfileobj)
endif()

message(${msg-head} "Building KeyGen Executable")
add_subdirectory(keygen)