#ifndef CPU_H
#define CPU_H

#include <fstream>
#include <iostream>
#include <numeric>
#include <unistd.h>
#include <vector>

class CpuReader
{
private:
    std::string modelName, version;
    size_t previous_idle_time = 0, previous_total_time = 0;
    size_t idle_time, total_time;
    bool get_cpu_times();
    std::vector<size_t> retrieve_cpu_times();
    void parseModelName();
    void parseVersion();

public:
    CpuReader();
    std::string getModelName();
    std::string getVersion();
    float run();
};

#endif