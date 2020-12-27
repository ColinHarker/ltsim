// Copyright (c) 2020 Colin Harker

#include "cpu.h"

Cpu::Cpu()
{
    run();
    parseModelName();
    parseVersion();
    numCores = getNumberCores();
    addCores();
    parseCores();
}

void Cpu::run()
{
    cpuReader.run(0);
    parseCores();
}

CpuReader Cpu::getCpu() { return cpuReader; }

std::vector<CpuReader> Cpu::getCores() { return cores; }

std::string Cpu::getModelName() { return cpuReader.modelName; }

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

    cpuReader.setModelName(mn);
}

std::string Cpu::getVersion() { return cpuReader.version; }

int Cpu::getNumberCores()
{

    std::array<char, 4> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("nproc", "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    if (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        return std::atoi(buffer.data());
    }
    else
        return -1;
}
void Cpu::addCores()
{
    for (int i = 1; i <= numCores; i++)
    {
        CpuReader cpr;
        cpr.run(i);
        cores.emplace_back(cpr);
    }
}
void Cpu::parseCores()
{
    int i = 1;
    for (auto& core : cores)
    {
        core.run(i++);
    }
}

void Cpu::parseVersion()
{
    std::ifstream proc_cpuinfo("/proc/version");
    std::string ret;
    std::getline(proc_cpuinfo, ret);

    // only grabbing the information wanted from /version
    std::string vers = ret.substr(0, COLS);
    cpuReader.version = vers;
}