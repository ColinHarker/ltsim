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

    if (!init()) // ncurses initialization, fails if terminal not supported
    {
        return EXIT_FAILURE;
    }

    Cpu cpu;
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
        updateCpuWindow(cpuInformationWindow,
                        cpu); // window that contains cpu utiliation

        displaySystemProcesses(systemProcessWindow);

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
