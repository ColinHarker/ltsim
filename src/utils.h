// Copyright (c) 2020 Colin Harker

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
enum class color : int
{
    none,
    green,
    yellow,
    red
};

enum class printType : int
{
    use_color,
    standard
};

enum class coreType : int
{
    cpu,
    core
};
enum class memType : int
{
    memTotal,
    memAvailable,
    swapTotal,
    swapFree
};
} // namespace flag

void displayElement(WindowWrap&, int, int, std::string, flag::printType,
                    flag::color);
void displayPercentColor(WindowWrap&, float, std::string, int, int);
System parseSystemInformation();
std::vector<std::string> parseStorageInformation();
std::vector<std::string> parseCommandLineOutput(const char*);

#endif