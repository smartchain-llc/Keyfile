
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
    
    # add_library(keyfile-static
    #             STATIC
    #             keyfile-objects)
    # set_target_properties(keyfile-static
    #                         PROPERTIES
    #                         OUTPUT_NAME "keyfileobj")       
    # add_library(keyfile-shared
    #             SHARED
    #             keyfile-objects)
    # set_target_properties(keyfile-shared
    #                         PROPERTIES
    #                         OUTPUT_NAME "keyfileobj")
endif(LIBGEN)

set(key_srcs
    key/key.cpp)