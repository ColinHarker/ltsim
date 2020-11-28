#include "system-process.h"

SystemProcess::SystemProcess(std::string t_user, std::string t_pid,
                             std::string t_cpu, std::string t_mem,
                             std::string t_vsz, std::string t_rss,
                             std::string t_tty, std::string t_stat,
                             std::string t_start, std::string t_time,
                             std::string t_command)
    : user(t_user), pid(t_pid), cpu(t_cpu), mem(t_mem), vsz(t_vsz), rss(t_rss),
      tty(t_tty), stat(t_stat), start(t_start), time(t_time),
      command(t_command){};

void SystemProcess::parse(const char* buffer)
{

    std::istringstream ss(buffer);

    ss >> user >> pid >> cpu >> mem >> vsz >> rss >> tty >> stat >> start >>
        time;
    std::string word;
    while (ss >> word)
    {
        command += word;
    }

    if (command.length() > 70)
    {
        command = command.substr(1, 70) + "...";
    }
}

SystemProcess::SystemProcess(){};

void SystemProcess::print() { std::cout << this->toString(); }

std::string SystemProcess::toString()
{
    std::ostringstream oss;
    oss << std::setw(5) << cpu << " " << std::setw(5) << mem << " "
        << std::setw(5) << user << " " << std::setw(5) << pid << " "
        << std::setw(7) << vsz << " " << std::setw(6) << rss << " "
        << std::setw(5) << tty << " " << std::setw(5) << stat << " "
        << std::setw(5) << start << " " << std::setw(5) << time << " "
        << command << std::endl;
    return oss.str();
}

float SystemProcess::getCpuAsFloat()
{
    float ret = atoi(cpu.c_str());
    return ret;
}

std::string SystemProcess::getCpuAsString() { return cpu; }

void SystemProcess::setCpu(std::string str) { cpu = str; }