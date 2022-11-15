#include "options.h"

CLIArguments::CLIArguments(char** argv) {
    printf("CLIArgs Constructor <%p>\n", this);
    
    mainArgv = argv;

    CLIArguments::initialized = true;
}

void CLIArguments::parseArgs() const {
    
}