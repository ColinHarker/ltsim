#include "linker.h"

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

void CpuReader::run(WindowWrap &menu)
{

  while (get_cpu_times())
  {
    const float idle_time_delta = idle_time - previous_idle_time;
    const float total_time_delta = total_time - previous_total_time;
    const float utilization = 100.0 * (1.0 - idle_time_delta / total_time_delta);
    previous_idle_time = idle_time;
    previous_total_time = total_time;
    mvwprintw(menu.getWin(), 5, 1, std::to_string(utilization).c_str());
  }
}
