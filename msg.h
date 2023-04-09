#ifndef MESSAGES_H
#define MESSAGES_H

#include <iostream>
#include "memory_worker.h"

using namespace std;

class msg {
public: 
    static void IncorrectOptions();
    static void ShowHelp();
};

#endif