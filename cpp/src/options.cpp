#include "../include/cli.h"

void Parameters::generate_options_list() {
    auto add = [](const char&& opt, const int&& argc, const std::initializer_list<char>&& conflictsWith){
        Parameters::option_list[opt] = option( argc, conflictsWith );
    };

    add('g', 1, {'l'});
}

void Parameters::parse_cli_args(int& argc, char* argv[]) {
    for (int i = 0; i < argc;) {
        if ( argv[i] && Parameters::is_opt(argv[i]) )
            printf("");
    }
}