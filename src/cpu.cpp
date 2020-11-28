#include "cpu.h"

Cpu::Cpu()
{
    this->cpu.run(0);
    this->parseModelName();
}

void Cpu::run() { this->cpu.run(0); }

CpuReader Cpu::getCpu() { return this->cpu; }

std::vector<CpuReader> Cpu::getCores() { return this->cores; }

std::string Cpu::getModelName() { return cpu.modelName; }

void Cpu::parseModelName()
{
    std::ifstream proc_cpuinfo("/proc/cpuinfo");
    proc_cpuinfo.seekg(std::ios::beg);
    for (int i = 0; i < 4; ++i) // skip the first 4 lines of /cpuinfo
    {
        proc_cpuinfo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::string mn;

    // skip the first 13 characters of the cpu model name
    proc_cpuinfo.ignore(13);
    std::getline(proc_cpuinfo, mn);

    this->cpu.setModelName(mn);
}

std::string Cpu::getVersion()
{
    this->cpu.parseVersion();
    return cpu.version;
}