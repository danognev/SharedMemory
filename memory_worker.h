#ifndef MEMORY_WORKER_H
#define MEMORY_WORKER_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <limits>
#include <string.h>

using namespace std;

class memory_worker {
private:
    static int shm;
    static char *address;

public: 
    static const string SM_NAME;
    static const int32_t SM_SIZE;

    static char* getAddress();

    static bool CreateSharedMemory();
    static void WriteInSharedMemory(char*);
    static void ReadSharedMemory();
    static void CloseMemory();
    static void SharedMemoryUnlink();
};


#endif