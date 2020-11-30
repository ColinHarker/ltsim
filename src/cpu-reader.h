#ifndef CPU_READER_H
#define CPU_READER_H

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
    float utilization;

    friend class Cpu;

    bool get_cpu_times(int); // sets the total_time variable for cpu, returns
                             // false if not enough information
    std::vector<size_t>
    retrieve_cpu_times(int); // retrieves info from /proc/stat
    void parseVersion();     // retieves linux version from /proc/version
    void run(int); // calculates the total cpu utilization, takes in an int to
                   // specify what information to parse. 0 parses total cpu, 1-8
                   // or more denotes specific cores.
public:
    void setModelName(std::string);
    std::string getVersion();
    float getUtil();
};

#endif