#include "runtime.h"

void updateCpuWindow(WindowWrap& disp, Cpu& cpu)
{
    // display linux version
    displayElement(disp, 0, 0, cpu.getVersion(), flag::standard, flag::none);

    cpu.run();
    float util = cpu.getCpu().getUtil();
    std::vector<CpuReader> core = cpu.getCores();

    displayCpuLevel(disp, util, "CPU", 3, 0);
    displayCpuLevel(disp, util, "MEM", 4, 0);
    displayCpuLevel(disp, util, "SWAP", 5, 0);

    displayCpuCores(disp, core, 7);
}

void displayCpuLevel(WindowWrap& disp, float util, std::string label, int y,
                     int start_x)
{
    displayElement(disp, y, start_x, label, flag::standard, flag::none);
    displayElement(disp, y, start_x + 5, "[", flag::standard, flag::none);

    int level = static_cast<int>((32 * (util / 100)) + start_x + 6);
    for (int i = 0; i < 32; i++)
    {
        int offset = i + start_x + 6;
        if (offset > level)
        {
            mvwprintw(disp.getWin(), y, offset, " ");
        }
        else
        {
            // less than 60% cpu utilization
            if (util < 60)
                displayElement(disp, y, offset, "|", flag::use_color,
                               flag::green);
            else if (util >= 60 && util < 85)
                displayElement(disp, y, offset, "|", flag::use_color,
                               flag::yellow);
            else
                displayElement(disp, y, offset, "|", flag::use_color,
                               flag::red);
        }
        wrefresh(disp.getWin());
    }
    mvwprintw(disp.getWin(), y, start_x + 38, "]");

    std::ostringstream ss;
    ss << std::setprecision(2) << std::setw(4) << std::fixed << util << " %%";
    mvwprintw(disp.getWin(), y, start_x + 40, ss.str().c_str());
}

void displayCpuCores(WindowWrap& disp, std::vector<CpuReader> cores, int y)
{
    int i = 1;
    for (auto core : cores)
    {
        displayCpuLevel(disp, core.getUtil(), "Core" + std::to_string(i), y, 0);
        y++;
        i++;
    }
}

void displaySystemProcesses(WindowWrap& disp)
{
    System sys = exec("ps -aux");
    sys.remove(0); // removing the menu string
    sys.sort();
    sys.display(disp);
}