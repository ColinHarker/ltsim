// Copyright (c) 2020 Colin Harker

#ifndef CPU_H
#define CPU_H

#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include <ncurses.h>

#include "cpu-reader.h"

class Cpu
{
private:
    CpuReader cpuReader;
    int numCores = -1;
    std::vector<CpuReader> cores;
    void parseModelName();
    void parseVersion();
    void parseCores();
    void addCores();

public:
    Cpu();
    void run();
    std::string getVersion();
    CpuReader getCpu();
    std::vector<CpuReader> getCores();
    std::string getModelName();
    int getNumberCores();
};

#endif