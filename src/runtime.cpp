#include "runtime.h"

void updateWindowOne(WindowWrap& disp, Cpu& cpu)
{
    displayElement(disp, 0, 2, cpu.getVersion(), flag::standard, flag::none);

    cpu.run();
    float util = cpu.getCpu().getUtil();
    std::vector<CpuReader> core = cpu.getCores();

    displayCpuLevel(disp, util, "CPU", 3);
    displayCpuLevel(disp, util, "MEM", 4);
    displayCpuLevel(disp, util, "SWAP", 5);

    // displayCpuCores();
}

void displayCpuLevel(WindowWrap& disp, float util, std::string label, int y)
{
    displayElement(disp, y, 2, label, flag::standard, flag::none);
    displayElement(disp, y, 7, "[", flag::standard, flag::none);

    int level = static_cast<int>((32 * (util / 100)) + 8);
    for (int i = 0; i < 32; i++)
    {
        int offset = i + 8;
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
    mvwprintw(disp.getWin(), y, 40, "]");

    std::ostringstream ss;
    ss << std::setprecision(2) << std::setw(4) << std::fixed << util << " %%";
    mvwprintw(disp.getWin(), y, 42, ss.str().c_str());
}

void displaySystemProcesses(WindowWrap& disp)
{
    System sys = exec("ps -aux");
    sys.remove(0); // removing the menu string
    sys.sort();
    sys.display(disp);
}