# message("-- [SRC] key.cmake: Setting source variable")
# set(key_src
#     key.cpp)
option(LIBGEN "Generate Shared Library" OFF)
if(LIBGEN)
    message("-- [SRC] key.cmake: Generating shared library files.")
    add_library(kf
                SHARED
                ../include/key.h
                key.cpp)
endif(LIBGEN)

set(key_srcs
    key.cpp)

add_executable(keyfile binary.cpp ${key_srcs})
