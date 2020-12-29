// Copyright (c) 2020 Colin Harker

#include "cpu-reader.h"

#include <limits>
#include <numeric>

using std::string;
using std::vector;

void CpuReader::setModelName(const string& mn) { modelName = mn; }

float CpuReader::getUtilization() const { return utilization; }

vector<size_t> CpuReader::retrieveCpuTimes(int lineNumberTarget) const
{

    std::ifstream proc_stat("/proc/stat"); // opening a filestream at /proc/stat

    proc_stat.seekg(std::ios::beg);

    // skip the first 4 lines of /cpuinfo
    for (int j = 0; j < lineNumberTarget; ++j)
    {
        proc_stat.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.
    vector<size_t> times;

    for (size_t time; proc_stat >> time; times.push_back(time))
        ;

    return times;
}

bool CpuReader::getCpuTimes(int lineNumberTarget)
{

    const vector<size_t> cpu_times = retrieveCpuTimes(lineNumberTarget);

    if (cpu_times.size() < 4)
        return false;

    CpuReader::idleTime = cpu_times[3];
    totalTime = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);

    return true;
}

void CpuReader::run(int lineNumberTarget)
{
    if (getCpuTimes(lineNumberTarget))
    {
        const float idle_time_delta = idleTime - previousIdleTime;
        const float total_time_delta = totalTime - previousTotalTime;
        const float util = 100.0 * (1.0 - idle_time_delta / total_time_delta);
        previousIdleTime = idleTime;
        previousTotalTime = totalTime;
        this->utilization = util;
    }
    else
    {
        this->utilization = -1;
    }
}
