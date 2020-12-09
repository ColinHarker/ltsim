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
                if (classVariable == flag::memTotal)
                {
                    memTotal = std::stoul(mem);
                }
                else if (classVariable == flag::memAvailable)
                {
                    memAvailable = std::stoul(mem);
                }
                else if (classVariable == flag::swapTotal)
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
    parseMemInfo("MemTotal", flag::memTotal);
    parseMemInfo("MemAvailable", flag::memAvailable);
    parseMemInfo("SwapTotal", flag::swapTotal);
    parseMemInfo("SwapFree", flag::swapFree);
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