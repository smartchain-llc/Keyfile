#include "../include/keyfile.h"

using path = std::filesystem::path;

Keyfile* Keyfile::generate_key(){
    if ( ! valid_environment() )
        return nullptr;
}
bool valid_environment(){

    // Check environment variable and default .key location for key
    if ( std::getenv("EKEY") || std::filesystem::exists( Keyfile::defaultDirectory/Keyfile::filename ) )
        return false;
    return true;
}