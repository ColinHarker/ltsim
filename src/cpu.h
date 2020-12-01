#ifndef CPU_H
#define CPU_H

#include <vector>
#include <array>
#include <memory>
#include <iostream>

#include "cpu-reader.h"

class Cpu
{
private:
    CpuReader cpu;
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