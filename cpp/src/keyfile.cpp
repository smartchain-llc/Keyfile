#include "../include/keyfile.h"

using path = std::filesystem::path;

bool valid_environment(){

    // Check environment variable and default .key location for key
    if ( std::getenv("EKEY") || std::filesystem::exists( Keyfile::defaultDirectory/Keyfile::filename ) ) {
        std::cout << "Invalid" << std::endl;
        return false;
    }
    std::cout << "Valid" << std::endl;
    return true;
}

Key* Keyfile::load_key() {
    if ( ! std::getenv("EKEY") ) {
        std::cout << "No environment (EKEY) variable for permanent key" << std::endl;
        if ( !std::filesystem::exists( Keyfile::defaultOutDir / Keyfile::filename ) ) {
            std::cout << "No temporary keyfile" << std::endl;
        }
    }
}

Key* Keyfile::generate_key(){
    if ( ! valid_environment() )
        return nullptr;
        
    Key* ret = new Key;
    std::fstream fstream;
    fstream.open( "/dev/random", std::ios::in );

    if ( fstream.bad() ){
        perror( "Could not open /dev/random\n" );
        exit( 1 );
    }

    fstream.read( reinterpret_cast<char*>(ret->data), PAGE_SIZE );
    if ( fstream.bad() ){
        perror("Could not read /dev/random\n");
        exit( 1 );
    }

    fstream.close();
    fstream.open( Keyfile::defaultOutDir / Keyfile::filename, std::ios::out );
    if ( fstream.bad() ){
        perror( "Could not open default keyfile\n" );
        exit( 1 );
    }

    fstream.write( reinterpret_cast<char*>(ret->data), PAGE_SIZE );
    if ( fstream.bad() ){
        perror("Could not write to keyfile\n");
        exit( 1 );
    }
    fstream.flush();
    fstream.close();

    return ret;
}