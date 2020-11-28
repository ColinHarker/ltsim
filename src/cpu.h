#ifndef CPU_H
#define CPU_H

#include <fstream>
#include <limits>
#include <numeric>
#include <vector>

class CpuReader
{
private:
    std::string modelName, version;
    size_t previous_idle_time = 0, previous_total_time = 0;
    size_t idle_time, total_time;

    bool get_cpu_times(); // sets the total_time variable for cpu, returns false
                          // if not enough information
    std::vector<size_t> retrieve_cpu_times(); // retrieves info from /proc/stat
    void parseModelName(); // retrieves Cpu name from /proc/cpuinfo
    void parseVersion();   // retieves linux version from /proc/version

public:
    CpuReader();
    std::string getModelName();
    std::string getVersion();
    float run(); // calculates the total cpu utilization, returns -1 if there is
                 // not enough information in /proc/stat
};

#endif