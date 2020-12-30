// Copyright (c) 2020 Colin Harker

#ifndef RUNTIME_H
#define RUNTIME_H

#include <vector>

#include "cpu.h"
#include "system.h"
#include "window.h"
#include "memory.h"
#include "utils.h"

/** Updates the window that displays cpu information
 * @param display the WindowWrap object in which we are updating
 * @param cpuContainer Cpu object that contains all info in relation to cpu
 * @param memory RandomAccessMemory object that contains information in relation
 *               to ram and swap
 */
void updateCpuWindow(WindowWrap& display, Cpu& cpuContainer,
                     RandomAccessMemory& memory);

/** Driver function to display utilization of specified component
 * @param display WindowWrap object in which we will display
 * @param utilization Object utilization percent in float format
 * @param label Component name that will be displayed on the left of GUI
 * @param row The row within the window that is used for display
 * @param startColumn The column within the row that the display will begin
 * @param length Enum class to choose between standard or small display length
 */
void displayUtilizationLevel(WindowWrap& display, float utilization,
                             const std::string& label, int row, int startColumn,
                             flag::displayLength length);

void displayCpuCores(WindowWrap&, std::vector<CpuReader>, int,
                     flag::displayLength);

void displaySystemProcesses(WindowWrap&);

void displayStorageInformation(WindowWrap&);

#endif