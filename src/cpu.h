// Copyright (c) 2020 Colin Harker

#ifndef CPU_H
#define CPU_H

#include "cpu-reader.h"
#include "utils.h"

#include <queue>

class Cpu
{
private:
    CpuReader m_CpuReader;
    FixedDeque<float, 100> m_CpuHistory;
    int m_NumCores = -1;
    std::vector<CpuReader> m_Cores;

    /** retrieves cpu model name from /proc/cpuinfo
     *  calls cpuReader.setModelName();
     */
    void parseModelName();

    /** retrieves linux version from /proc/version
     * sets the value of cpuReader.version
     */
    void parseVersion();

    /** executes 'nproc' command and reads the output
     *  which is the number of cores
     * @return number of cores or -1 if parsing fails
     */
    int getNumberCores();

    /** Creates a CpuReader object for each core and
     * adds this core to std::vector<CpuReader> cores
     */
    void addCores();

    /** Iterates through each core and parses the data
     * to update individual core utilization
     */
    void parseCores();

public:
    Cpu();
    void run();
    std::string getVersion();
    CpuReader getCpu();
    std::vector<CpuReader> getCores();
    std::string getModelName();
    FixedDeque<float, 100> getCpuHistory() const;
};

#endif