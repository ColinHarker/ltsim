#include "cpu-reader.h"

void CpuReader::setModelName(std::string mn) { this->modelName = mn; }

float CpuReader::getUtil() { return utilization; }

std::vector<size_t> CpuReader::retrieve_cpu_times(int i)
{

    std::ifstream proc_stat("/proc/stat"); // opening a filestream at /proc/stat

    proc_stat.seekg(std::ios::beg);
    for (int j = 0; j < i; ++j) // skip the first 4 lines of /cpuinfo
    {
        proc_stat.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.
    std::vector<size_t> times;

    for (size_t time; proc_stat >> time; times.push_back(time))
        ;

    return times;
}

bool CpuReader::get_cpu_times(int i)
{

    const std::vector<size_t> cpu_times = retrieve_cpu_times(i);

    if (cpu_times.size() < 4)
        return false;

    CpuReader::idle_time = cpu_times[3];
    total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);

    return true;
}

void CpuReader::run(int i)
{
    if (get_cpu_times(i))
    {
        const float idle_time_delta = idle_time - previous_idle_time;
        const float total_time_delta = total_time - previous_total_time;
        const float util = 100.0 * (1.0 - idle_time_delta / total_time_delta);
        previous_idle_time = idle_time;
        previous_total_time = total_time;
        this->utilization = util;
    }
    else
    {
        this->utilization = -1;
    }
}
