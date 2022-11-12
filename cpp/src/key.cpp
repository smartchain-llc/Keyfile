#include "../include/key.h"

Key::Key() {
    keyfile = new Keyfile();
    attach_to_key_mem();

}
Key::~Key() {
    if ( shmBlock )
        detach_from_key_mem();
    // delete shmBlock;
    // delete keyData;
}

void Key::attach_to_key_mem() {
    if( keyfile->mem_key() == -1 )
        std::cout << "MemKey Invalid!" << std::endl;
    
    shmBlock = static_cast<char*>( shmat( keyfile->mem_key(), NULL, 0 ) );
}

void Key::detach_from_key_mem() {
    shmdt( shmBlock );
}

void Key::print() {
    printf("%s", shmBlock);
}