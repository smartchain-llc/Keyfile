#pragma once
#include <filesystem>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <iostream>
#include <fstream>

#define PAGE_SIZE 4096
#define SHM_KEY_ERROR (-1)

using namespace std::filesystem;

class Key{

    struct Keyfile{
        public:
            ~Keyfile(){ destroy_key_mem(); };
            Keyfile() {
                (std::filesystem::exists( defaultFile ))? shmFile = const_cast<char*>(defaultFile.c_str()) : shmFile = const_cast<char*>((defaultOutputDir/fileName).c_str());
                if (std::filesystem::exists( shmFile ))
                    set_keyfile_mem_block(); 
                else 
                    fatal_error("KeyFile", 69);
            };

            const int& mem_key(){ return memKey; };
            const std::string&  filename() { 
                if ( isValid ) return fileName;
                fatal_error("Keyfile is not valid", 69);
            };
            const path&         filePath() { 
                if ( isValid ) return defaultFile;
                fatal_error("Keyfile is not valid.", 69);
            };
            void generate_keyfile(){
                if( std::filesystem::exists( defaultFile ) || std::filesystem::exists( (defaultOutputDir / fileName) ))
                    fatal_error("KeyGen", 69);
                
                fileReader = new std::fstream( "/dev/random", std::ios::in );
                char* randData = new char[PAGE_SIZE];
                fileReader->read( randData, PAGE_SIZE );
                fileReader->close();
                
                fileReader->open( defaultInputDir / fileName, std::ios::out );
                fileReader->write( defaultFile.c_str(), PAGE_SIZE );
                fileReader->flush();
                fileReader->close();
                delete fileReader;
            }
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
                key = ftok( shmFile, 4096 );    //TODO: Pull group key from env vars
                if ( key > 0 ) {
                    memKey = shmget( key, PAGE_SIZE, 0 );
                    if( memKey > 0 )
                        return;
                    
                    memKey = shmget( key, PAGE_SIZE, 0600|IPC_CREAT );
                    if ( memKey < 0 )
                        fatal_error("Mem Key", 69);

                    shmIn = static_cast<char*>( shmat( memKey, NULL, 0) );

                    fileReader = new std::fstream( shmFile, std::ios::in );
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
                    shmctl( memKey, IPC_RMID, NULL );
                std::cout << "Keyfile Block destroyed" << std::endl;
            }

            void fatal_error(const char* msg, int err) {
                perror(msg);
                exit(err);
            }
    };

    public:
        using byte = unsigned char;
        Key();
        ~Key();
        const byte&     operator[](int index) const;
        const size_t&   size() { return keySize; }
        void print() const;
    private:

        Keyfile*    keyfile { nullptr };
        byte*       keyData { nullptr };
        const size_t    keySize { PAGE_SIZE };
        
        void attach_to_key_mem();
        void detach_from_key_mem();
};