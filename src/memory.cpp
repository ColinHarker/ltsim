// Copyright (c) 2020 Colin Harker

#include "memory.h"

#include <fstream>
#include <iostream>
#include <limits>

RandomAccessMemory::RandomAccessMemory() { run(); }

void RandomAccessMemory::parseMemInfo(const std::string& memInfoType,
                                      flag::memType      classVariable)
{
   std::string   token;
   std::ifstream file("/proc/meminfo");
   while(file >> token)
   {
      if(token == memInfoType + ":")
      {
         std::string mem;
         if(file >> mem)
         {
            if(classVariable == flag::memType::memTotal)
            {
               m_memTotal = std::stoul(mem);
            }
            else if(classVariable == flag::memType::memAvailable)
            {
               m_memAvailable = std::stoul(mem);
            }
            else if(classVariable == flag::memType::swapTotal)
            {
               m_swapTotal = std::stoul(mem);
            }
            else
            {
               m_swapFree = std::stoul(mem);
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
   m_memUsagePercent  = 100.f * (1.f - (static_cast<double>(m_memAvailable) / static_cast<double>(m_memTotal)));
   m_swapUsagePercent = 100.f * (1.f - (static_cast<double>(m_swapFree) / static_cast<double>(m_swapTotal)));
}

float RandomAccessMemory::getMemUsage() const { return m_memUsagePercent; }
float RandomAccessMemory::getSwapUsage() const { return m_swapUsagePercent; }