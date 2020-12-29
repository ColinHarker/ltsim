// Copyright (c) 2020 Colin Harker

#include "memory.h"

#include <fstream>
#include <limits>
#include <iostream>

RandomAccessMemory::RandomAccessMemory() { run(); }

void RandomAccessMemory::parseMemInfo(const std::string& memInfoType,
                                      flag::memType classVariable)
{
    std::string token;
    std::ifstream file("/proc/meminfo");
    while (file >> token)
    {
        if (token == memInfoType + ":")
        {
            std::string mem;
            if (file >> mem)
            {
                if (classVariable == flag::memType::memTotal)
                {
                    memTotal = std::stoul(mem);
                }
                else if (classVariable == flag::memType::memAvailable)
                {
                    memAvailable = std::stoul(mem);
                }
                else if (classVariable == flag::memType::swapTotal)
                {
                    swapTotal = std::stoul(mem);
                }
                else
                {
                    swapFree = std::stoul(mem);
                }
            }
        }
        // ignore rest of the line
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void RandomAccessMemory::run()
{
    parseMemInfo("MemTotal", flag::memType::memTotal);
    parseMemInfo("MemAvailable", flag::memType::memAvailable);
    parseMemInfo("SwapTotal", flag::memType::swapTotal);
    parseMemInfo("SwapFree", flag::memType::swapFree);
    calculateMemSwapUsage();
}

void RandomAccessMemory::calculateMemSwapUsage()
{
    memUsagePercent = 100.f * (1.f - (static_cast<double>(memAvailable) /
                                      static_cast<double>(memTotal)));
    swapUsagePercent = 100.f * (1.f - (static_cast<double>(swapFree) /
                                       static_cast<double>(swapTotal)));
}

float RandomAccessMemory::getMemUsage() const { return memUsagePercent; }
float RandomAccessMemory::getSwapUsage() const { return swapUsagePercent; }