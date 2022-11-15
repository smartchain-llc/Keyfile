#pragma once

#include <vector>
#include <map>
#include <iostream>

class Parameters{
    struct option {
        std::vector<char> conflicts;
        bool is_set     = false;
        int cli_index   = 0;

        option(const int& argc, const std::initializer_list<char>& conflictsWith){
            for(auto& i : conflictsWith)
                conflicts.push_back(i);
            is_set = true;
        };
        ~option(){};
        
    };

    public:
        static bool is_set(char opt);
        static bool is_opt(char* opt);
        static void parse_cli_args(int& argc, char* argv[]);

    private:
        Parameters(){
            generate_options_list();
        };
        ~Parameters(){};
        
        static void generate_options_list();

        static std::map<char, option> option_list;
        
};