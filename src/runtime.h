#ifndef RUNTIME_H
#define RUNTIME_H

#include <vector>

#include "cpu.h"
#include "system.h"
#include "window.h"
#include "utils.h"

void updateCpuWindow(WindowWrap&, Cpu&);
void displayCpuLevel(WindowWrap&, float, std::string, int, int);
void displayCpuCores(WindowWrap&, std::vector<CpuReader>, int);
void displaySystemProcesses(WindowWrap&);

#endif