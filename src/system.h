#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>

#include "window.h"
#include "system-process.h"

class System
{
private:
    std::vector<SystemProcess> processes;

public:
    System();
    void add(SystemProcess&);
    SystemProcess get(int);
    void display(WindowWrap&);
    void print();
};

#endif