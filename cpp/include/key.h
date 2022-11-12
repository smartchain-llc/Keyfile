#pragma once
#include <filesystem>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <fstream>

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

            int     memKey  { SHM_KEY_ERROR };
            char*   shmFile { nullptr };
            char*   shmIn   { nullptr };
            bool    isValid { false };
            std::fstream* fileReader { nullptr };

            void set_keyfile_mem_block() {
                key_t key;
                (std::filesystem::exists(defaultFile))? shmFile = const_cast<char*>(defaultFile.c_str()) : shmFile = const_cast<char*>((defaultOutputDir/fileName).c_str());
                key = ftok( shmFile, 4096 );
                if ( key > 0 ) {
                    memKey = shmget( key, PAGE_SIZE, 0600 | IPC_CREAT );

                    fileReader = new std::fstream( shmFile, std::ios::in );
                    shmIn = static_cast<char*>( shmat( memKey, NULL, 0) );
                    fileReader->read(shmIn, PAGE_SIZE);
                    
                    fileReader->close();
                    delete fileReader;
                    shmdt( shmIn );
                    shmIn = nullptr;
                }
                else
                    std::cout << "Could not ftok " << shmFile << std::endl;
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

        Keyfile*    keyfile { nullptr };
        byte*       keyData { nullptr };
        char*       shmBlock { nullptr };
        const size_t    keySize { PAGE_SIZE };

        void attach_to_key_mem();
        void detach_from_key_mem();
};