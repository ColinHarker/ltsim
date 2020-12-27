/*
MIT License

Copyright (c) 2020 Colin Harker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <ncurses.h>
#include <unistd.h>
#include <iomanip>
#include <sys/ioctl.h>

#include "cpu.h"
#include "window.h"
#include "init.h"
#include "utils.h"
#include "runtime.h"

int main()
{
    // ncurses initialization, fails if terminal or OS not supported
    if (!init())
    {
        return EXIT_FAILURE;
    }

    // initialize runtime objects
    Cpu cpu;
    RandomAccessMemory mem;
    bool running = true;

    WindowWrap topDisplayHeader(1, COLS, 0, 0);
    WindowWrap cpuInformationWindow(LINES / 2, COLS / 2, 1, 0);
    WindowWrap storageDisplayWindow(LINES / 2, COLS / 2, 1, COLS / 2);
    WindowWrap systemProcessWindow((LINES / 2) + 1, COLS, LINES / 2, 0);

    // display linux version
    displayElement(topDisplayHeader, 0, 0, cpu.getVersion(), flag::standard,
                   flag::none);

    // display cpu model above graph
    displayElement(cpuInformationWindow, 1, 0, cpu.getModelName(),
                   flag::standard, flag::none);

    // have not figured out proper exit of program yet, use ctrl-c for now
    while (running)
    {
        refresh();
        wrefresh(topDisplayHeader.getWin());
        wrefresh(systemProcessWindow.getWin());
        wrefresh(storageDisplayWindow.getWin());
        wrefresh(cpuInformationWindow.getWin());

        // following functions found in runtime.cpp
        updateCpuWindow(cpuInformationWindow, cpu, mem);
        displaySystemProcesses(systemProcessWindow);
        displayStorageInformation(storageDisplayWindow);

        sleep(1);
    }

    // deallocates and ends ncurses
    endwin();

    return EXIT_SUCCESS;
}
