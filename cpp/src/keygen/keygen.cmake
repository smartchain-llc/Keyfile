# set(msg-head "---[KEYGEN]")
message(${msg-head} "keygen.cmake Adding Executable")

message(${msg-head} "keygen.cmake Creating CLIArgs so")
add_library(cliargs
            SHARED
            options.h
            options.cpp)

message(${msg-head} "keygen.cmake Adding Executable")
add_executable(keyfile-keygen
    keygen.h
    keygen.cpp)

message(${msg-head} "keygen.cmake Linking CLIArgs lib")
target_link_libraries(keyfile-keygen cliargs)
