#include "linker.h"

CpuReader::CpuReader() { parseModelName(); }

std::vector<size_t> CpuReader::retrieve_cpu_times()
{

  std::ifstream proc_stat("/proc/stat");
  proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.
  std::vector<size_t> times;

  for (size_t time; proc_stat >> time; times.push_back(time))
    ;

  return times;
}

bool CpuReader::get_cpu_times()
{

  const std::vector<size_t> cpu_times = retrieve_cpu_times();

  if (cpu_times.size() < 4)
    return false;

  CpuReader::idle_time = cpu_times[3];
  total_time = std::accumulate(cpu_times.begin(), cpu_times.end(), 0);

  return true;
}

float CpuReader::run()
{
  if (get_cpu_times())
  {
    const float idle_time_delta = idle_time - previous_idle_time;
    const float total_time_delta = total_time - previous_total_time;
    const float utilization = 100.0 * (1.0 - idle_time_delta / total_time_delta);
    previous_idle_time = idle_time;
    previous_total_time = total_time;
    return utilization;
  }
  else
  {
    return -1;
  }
}

std::string CpuReader::getModelName()
{
  return modelName;
}

void CpuReader::parseModelName()
{
  std::ifstream proc_cpuinfo("/proc/cpuinfo");
  proc_cpuinfo.seekg(std::ios::beg);
  for (int i = 0; i < 4; ++i)
  {
    proc_cpuinfo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  //proc_cpuinfo.ignore();
  std::string mn;
  proc_cpuinfo.ignore(13);
  std::getline(proc_cpuinfo, mn);

  modelName = mn;
}

std::string CpuReader::getVersion()
{
  parseVersion();
  return version;
}

void CpuReader::parseVersion()
{
  std::ifstream proc_cpuinfo("/proc/version");
  std::string ret;
  std::getline(proc_cpuinfo, ret);
  std::string vers = ret.substr(0, 41);
  version = vers;
}
