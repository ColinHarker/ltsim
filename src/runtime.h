#ifndef RUNTIME_H
#define RUNTIME_H

#include <vector>

#include "cpu.h"
#include "system.h"
#include "window.h"
#include "utils.h"

void updateWindowOne(WindowWrap&, Cpu&);
void displayCpuLevel(WindowWrap&, float, std::string, int);
void displaySystemProcesses(WindowWrap&);

#endif