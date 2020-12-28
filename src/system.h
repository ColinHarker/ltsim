// Copyright (c) 2020 Colin Harker

#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <algorithm>

class System;

#include "window.h"
#include "system-process.h"
#include "utils.h"

class System
{
private:
    std::vector<SystemProcess> processes;

public:
    System();
    void add(SystemProcess&);
    SystemProcess get(int);
    void sort();
    void display(WindowWrap&);
    void print();
    void remove(int);
};

#endif