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

    /** retrieves process from processes vector
     * @param index index of process to be retrieved
     * @return SystemProcess object
     */
    SystemProcess get(int index);

    /** sorts the processes in decending order based on cpu load
     */
    void sort();

    /** displays all system proccesses held in System Object to designated
     * window
     * @param win window to be dispayed on
     */
    void display(WindowWrap& win);

    void print();

    /** Remove watched process at index
     * @param index Index within processes vector to remove
     */
    void remove(int index);
};

#endif