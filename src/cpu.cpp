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
    m_NumCores = getNumberCores();
    addCores();
    parseCores();
    run();
}

void Cpu::run()
{
    m_CpuReader.run(0);
    m_CpuHistory.push(m_CpuReader.getUtilization());
    parseCores();
}

CpuReader Cpu::getCpu() { return m_CpuReader; }

vector<CpuReader> Cpu::getCores() { return m_Cores; }

string Cpu::getModelName() { return m_CpuReader.m_modelName; }

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

    m_CpuReader.setModelName(mn);
}

string Cpu::getVersion() { return m_CpuReader.m_version; }

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
    for (int i = 1; i <= m_NumCores; i++)
    {
        CpuReader cpr;
        cpr.run(i);
        m_Cores.emplace_back(cpr);
    }
}
void Cpu::parseCores()
{
    int i = 1;
    for (auto& core : m_Cores)
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
    m_CpuReader.m_version = vers;
}

FixedDeque<float, 100> Cpu::getCpuHistory() const { return m_CpuHistory; }