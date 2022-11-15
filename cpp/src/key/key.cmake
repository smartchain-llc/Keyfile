
option(LIBGEN "Generate Shared Library" OFF)
if(LIBGEN)
    message("-- [SRC] key.cmake: Generating shared library files.")
    add_library(keyfileso
                SHARED
                key/key.h
                key/key.cpp)
endif(LIBGEN)

set(key_srcs
    key/key.cpp)