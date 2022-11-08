#pragma once

#include <iostream>
#include <istream>
#include <filesystem>
#include <cstddef>

#define PAGE_SIZE 4096;

class Keyfile{
    // using byte_stream = std::basic_iostream<std::byte>;
    // using byte_data = unsigned char*;
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
            
            private:

        };
        // byte_stream* iostream;
        
};
