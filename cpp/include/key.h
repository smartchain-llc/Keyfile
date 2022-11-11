#pragma once
#include <filesystem>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PAGE_SIZE 4096
#define SHM_KEY_ERROR (-1)

using namespace std::filesystem;

class Key{
    using byte = unsigned char;

    struct Keyfile{
        public:
            ~Keyfile(){
                destroy_key_mem();
            };
            Keyfile() {
                set_keyfile_mem_block();
            };
            const std::string&  filename() { 
                if ( isValid ) return fileName;
                else perror("Keyfile is not valid."); 
            };
            const path&         filePath() { 
                if ( isValid ) return defaultFile;
                else perror("Keyfile is not valid.");
            };
            const int& mem_key(){ return memKey; };

        private:
            const path defaultOutputDir         { "/tmp" };
            const path defaultInputDir          { std::getenv("HOME") };
            const std::string fileName          { ".key" };
            const path defaultFile              { defaultInputDir / fileName };

            path   shmFile;
            bool    isValid { false };
            int     memKey = SHM_KEY_ERROR;

            void set_keyfile_mem_block() {
                key_t key;
                key = ftok( defaultFile.c_str(), PAGE_SIZE );
                if ( key > 0 ) {
                    memKey = shmget( key, PAGE_SIZE, 0600 | IPC_CREAT );
                    shmFile = defaultFile;
                }

                key = ftok( (defaultOutputDir/fileName).c_str(), PAGE_SIZE );
                if ( key > 0 ) {
                    memKey = shmget( key, PAGE_SIZE, 0600 | IPC_CREAT );
                    shmFile = (defaultOutputDir/fileName);
                }
            }
            
            void destroy_key_mem() {
                if( memKey > 0 )
                    shmctl(memKey, IPC_RMID, NULL);
            }
    };

    public:
        Key();
        ~Key();
        const byte& at(int index) const { return keyData[index % keySize]; }
        const size_t& size() { return keySize; }
        void print();
    private:

        Keyfile     keyfile{};
        byte*       keyData;
        char*       shmBlock;
        const size_t    keySize { PAGE_SIZE };

        char* attach_to_key_mem();
        void detach_from_key_mem();
};