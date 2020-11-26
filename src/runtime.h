#ifndef RUNTIME_H
#define RUNTIME_H

#include "cpu.h"
#include "system.h"
#include "window.h"
#include "utils.h"

void updateWindowOne(WindowWrap&, CpuReader&);
void displayCpuLevel(WindowWrap&, float);
void displaySystemProcesses(WindowWrap&, System&);

#endif