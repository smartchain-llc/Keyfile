#include "../include/key.h"

Key::Key() {
    this->shmBlock = attach_to_key_mem();
}
Key::~Key() {
    if ( shmBlock )
        detach_from_key_mem();
    delete shmBlock;
    delete keyData;
}

char* Key::attach_to_key_mem() {
    if( keyfile.mem_key() == -1 )
        return NULL;
    
    void* block = shmat( keyfile.mem_key(), NULL, 0 );
    if( ! block )
        return NULL;
    
    return static_cast<char*>( block );
}

void Key::detach_from_key_mem() {
    shmdt( shmBlock );
}

void Key::print() {
    printf("%s", *shmBlock);
}