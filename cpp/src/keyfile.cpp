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

Keyfile* Keyfile::generate_key(){
    if ( ! valid_environment() )
        return nullptr;
        
    Keyfile* ret = new Keyfile;
    std::fstream fstream;
    std::ifstream instream;

    fstream.open( Keyfile::defaultOutDir/Keyfile::filename, std::ios_base::out );
    if ( fstream.bad() ){
        std::cout << "Could not open file" << std::endl;
        delete ret;
        return nullptr;
    }
    std::cout << "File Opened" << std::endl;

    unsigned char msg[3] = {0xC0, 0xFF, 0xEE};
    fstream.write(reinterpret_cast<const char*>(msg), sizeof(msg));

    if ( fstream.bad() ) {
        std::cout << "Could not write" << std::endl;
    }
    fstream.flush();

    instream.open("/dev/random", std::ios_base::in);
    if ( instream.bad() )
        std::cout << "Could not open instream" << std::endl;
    instream.read(reinterpret_cast<char*>(ret->key.data), PAGE_SIZE);
    if ( instream.bad() )
        std::cout << "Could not read" << std::endl;
    
    for (int i = 0; i < PAGE_SIZE; i++){
        std::cout << ret->key.data[i] << " ";
        if ( i % 16 == 0 )
            std::cout << std::endl;
    }
        

    return ret;
}