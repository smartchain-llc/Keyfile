cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 20)
set(msg-head "--- [KEYGEN] ")

project(keyfile-keygen)
message(${msg-head} "Pulling keygen.cmake")
include(keygen.cmake)