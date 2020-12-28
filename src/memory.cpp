// Copyright (c) 2020 Colin Harker

#include "memory.h"

void RandomAccessMemory::parseMemInfo(std::string str,
                                      flag::memType classVariable)
{
    std::string token;
    std::ifstream file("/proc/meminfo");
    while (file >> token)
    {
        if (token == str + ":")
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
}

float RandomAccessMemory::getMemUsage()
{
    memUsagePercent = 100.f * (1.f - (static_cast<double>(memAvailable) /
                                      static_cast<double>(memTotal)));
    return memUsagePercent;
}
float RandomAccessMemory::getSwapUsage()
{
    swapUsagePercent = 100.f * (1.f - (static_cast<double>(swapFree) /
                                       static_cast<double>(swapTotal)));
    return swapUsagePercent;
}