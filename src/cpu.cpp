// Copyright (c) 2020 Colin Harker

#include "cpu.h"

#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include <ncurses.h>
#include <limits>

using std::string;
using std::vector;

Cpu::Cpu()
{
    parseModelName();
    parseVersion();
    m_numCores = getNumberCores();
    addCores();
    parseCores();
    run();
}

void Cpu::run()
{
    m_cpuReader.run(0);
    parseCores();
}

CpuReader Cpu::getCpu() { return m_cpuReader; }

vector<CpuReader> Cpu::getCores() { return m_cores; }

string Cpu::getModelName() { return m_cpuReader.m_modelName; }

void Cpu::parseModelName()
{
    std::ifstream proc_cpuinfo("/proc/cpuinfo");
    proc_cpuinfo.seekg(std::ios::beg);
    for (int i = 0; i < 4; ++i) // skip the first 4 lines of /cpuinfo
    {
        proc_cpuinfo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    string mn;

    // skip the first 13 characters of the cpu model name
    proc_cpuinfo.ignore(13);
    std::getline(proc_cpuinfo, mn);

    m_cpuReader.setModelName(mn);
}

string Cpu::getVersion() { return m_cpuReader.m_version; }

int Cpu::getNumberCores()
{

    std::array<char, 4> buffer;
    string result;
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
    for (int i = 1; i <= m_numCores; i++)
    {
        CpuReader cpr;
        cpr.run(i);
        m_cores.emplace_back(cpr);
    }
}
void Cpu::parseCores()
{
    int i = 1;
    for (auto& core : m_cores)
    {
        core.run(i++);
    }
}

void Cpu::parseVersion()
{
    std::ifstream proc_cpuinfo("/proc/version");
    string ret;
    std::getline(proc_cpuinfo, ret);

    // only grabbing the information wanted from /version
    string vers = ret.substr(0, COLS);
    m_cpuReader.m_version = vers;
}