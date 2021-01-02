// Copyright (c) 2020 Colin Harker

#ifndef RUNTIME_H
#define RUNTIME_H

#include <vector>

#include "cpu.h"
#include "memory.h"
#include "system.h"
#include "utils.h"
#include "window.h"

/** Updates the window that displays cpu information
 * @param display the WindowWrap object in which we are updating
 * @param cpuContainer Cpu object that contains all info in relation to cpu
 * @param memory RandomAccessMemory object that contains information in relation
 *               to ram and swap
 */
void updateCpuWindow(WindowWrap& display, Cpu& cpuContainer, RandomAccessMemory& memory);

/** Driver function to display utilization of specified component
 * @param display WindowWrap object in which we will display
 * @param utilization Object utilization percent in float format
 * @param label Component name that will be displayed on the left of GUI
 * @param row The row within the window that is used for display
 * @param startColumn The column within the row that the display will begin
 * @param length Enum class to choose between standard or small display length
 */
void displayUtilizationLevel(WindowWrap& display, float utilization, const std::string& label, int row, int startColumn, flag::displayLength length);

/** Iterates through vector of cpu cores and displays the utilization of each
 * @param display WindowWrap object in which we will display
 * @param cores Vector of CpuReader, one for each cpu core
 * @param startRow Row where the first core is displayed
 * @param length Enum class to choose between standard or small display length
 */
void displayCpuCores(WindowWrap& display, const std::vector<CpuReader> cores, int startRow, flag::displayLength length);

/** Parses system information and displays to window
 * @param display WindowWrap object in which we will display
 */
void displaySystemProcesses(WindowWrap& display);

/** Parses storage information and displays to window
 * @param display WindowWrap object in which we will display
 */
void displayStorageInformation(WindowWrap& display);

#endif