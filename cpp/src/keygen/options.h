#pragma once
#include <iostream>
#include <vector>
#include <deque>

struct Argument {
    enum{
        DEFAULT,
        LOAD,
    };
    std::string name;
    std::string action;
};

/*
    == Current Available Arguments
    default:    Generates a keyfile at the directory
    load:       Loads a keyfile from $HOME directory into shared mem.
*/
class CLIArguments{
    static inline bool initialized { false };
    public:
        CLIArguments(char** argv);

    private:
        char**  mainArgv { nullptr };
        std::deque<Argument*> args {};

        void parseArgs() const;
};