#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#include "utils.h"

class RandomAccessMemory
{
private:
    void parseMemInfo(std::string, flag::memType);
    unsigned long memTotal = 0;
    unsigned long memAvailable = 0;
    unsigned long swapTotal = 0;
    unsigned long swapFree = 0;
    float memUsagePercent = -1.0;
    float swapUsagePercent = -1.0;

public:
    RandomAccessMemory() { run(); };

    void run();
    float getMemUsage();
    float getSwapUsage();
};

#endif