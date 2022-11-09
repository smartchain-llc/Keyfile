#pragma once

#include <vector>
#include <map>
#include <iostream>

class Parameters{
    struct option {
        std::vector<char> conflicts;
    };

    public:
        static bool is_set(char opt);
    private:
        Parameters(){
            generate_options_list();
        };
        ~Parameters(){};
        
        static void generate_options_list();

        static std::map<char, option> option_list;
        
};