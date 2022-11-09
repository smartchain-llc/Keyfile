#pragma once

#include <iostream>
#include <istream>
#include <fstream>
#include <filesystem>
#include <cstddef>

#define PAGE_SIZE 4096

class Keyfile{
    using path = std::filesystem::path;
    public:
        static inline const path        defaultDirectory    { std::getenv("HOME") };
        static inline const path        defaultOutDir       { "/tmp" };
        static inline const std::string filename            { ".key" };
        static inline const path        defaultFile         { Keyfile::defaultOutDir/Keyfile::filename };
        static Keyfile* generate_key();

    private:
        struct Key{
            using byte = unsigned char;
            byte data[PAGE_SIZE];
        };
        
        Key key;
};
