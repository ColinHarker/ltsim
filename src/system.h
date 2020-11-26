#ifndef SYSTEM_H
#define SYSTEM_H

#include "linker.h"
#include "system-process.h"

class System
{
private:
    std::vector<SystemProcess> processes;

public:
    System();
    void add(SystemProcess&);
};

#endif