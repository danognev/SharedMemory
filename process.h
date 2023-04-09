#ifndef PROCESS_H
#define PROCESS_H

#include <unistd.h>
#include <sys/wait.h>
#include "memory_worker.h"

using mw = memory_worker;

class process {
public:
    static void Process(char*);
};

#endif