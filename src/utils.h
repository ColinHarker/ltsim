#ifndef UTILS_H
#define UTILS_H

#define APP_VERS 0.1
#define APP_NAME "ltsim"
#define APP_NAME_FULL "Linux Terminal System Information Monitor"

#include <string>
#include <array>
#include <memory>

#include "window.h"
#include "system.h"

namespace flag
{
enum color
{
    none,
    green,
    yellow,
    red
};

enum print
{
    use_color,
    standard
};

enum coreType
{
    cpu,
    core
};
enum memType
{
    memTotal,
    memAvailable,
    swapTotal,
    swapFree
};
} // namespace flag

struct data
{
    float cpu, mem, swap;
};

void displayElement(WindowWrap&, int, int, std::string, flag::print,
                    flag::color);
void displayPercentColor(WindowWrap&, float, std::string, int, int);
System exec(const char*);
#endif