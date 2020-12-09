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

    if (!init())
    {
        // ncurses initialization, fails if terminal not supported
        return EXIT_FAILURE;
    }

    Cpu cpu;
    RandomAccessMemory mem;
    bool running = true;

    WindowWrap cpuInformationWindow(LINES / 2, COLS / 2, 0, 0);
    WindowWrap disp_2(LINES / 2, COLS / 2, 0, COLS / 2);
    WindowWrap systemProcessWindow((LINES / 2) + 1, COLS, LINES / 2, 0);

    refresh();

    box(disp_2.getWin(), 0, 0);

    wrefresh(cpuInformationWindow.getWin());
    wrefresh(disp_2.getWin());
    wrefresh(systemProcessWindow.getWin());

    // display cpu model above graph
    displayElement(cpuInformationWindow, 2, 0, cpu.getModelName(),
                   flag::standard, flag::none);

    while (running)
    {
        updateCpuWindow(cpuInformationWindow, cpu,
                        mem); // window that contains cpu utiliation

        displaySystemProcesses(systemProcessWindow);

        displayStorageInformation(disp_2);

        displayElement(disp_2, 1, 1, "STORAGE: 0.0GB / 250.98GB",
                       flag::print_type::standard, flag::color::none);

        // list size of files
        // du -h --max-depth=1 | sort -hr

        // display storage mounts
        // df

        refresh();
        wrefresh(systemProcessWindow.getWin());
        wrefresh(disp_2.getWin());
        wrefresh(cpuInformationWindow.getWin());
        sleep(1);
    }

    // deallocates and ends ncurses
    endwin();

    return 0;
}
