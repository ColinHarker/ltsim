#ifndef CPU_H
#define CPU_H

#include <vector>

#include "cpu-reader.h"

class Cpu
{
private:
    CpuReader cpu;
    std::vector<CpuReader> cores;
    void parseModelName();

public:
    Cpu();
    void run();
    std::string getVersion();
    CpuReader getCpu();
    std::vector<CpuReader> getCores();
    std::string getModelName();
};

#endif