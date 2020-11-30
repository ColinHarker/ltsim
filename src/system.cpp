#include "system.h"

System::System(){};

void System::add(SystemProcess& sp) { processes.emplace_back(sp); }

SystemProcess System::get(int index) { return processes.at(index); }

void System::print()
{

    for (SystemProcess p : processes)
    {
        p.print();
    }
}

void System::sort()
{

    std::sort(processes.begin(), processes.end(),
              [](SystemProcess& lhs, SystemProcess& rhs) {
                  return lhs.getCpuAsFloat() > rhs.getCpuAsFloat();
              });
}

void System::display(WindowWrap& disp)
{
    std::string titles =
        "  CPU   MEM  USER   PID     VSZ    RSS   TTY  STAT START  "
        "TIME COMMAND";

    mvwprintw(disp.getWin(), 1, 0, titles.c_str());
    int i = 2;
    for (SystemProcess sp : processes)
    {
        mvwprintw(disp.getWin(), i, 0, sp.toString().c_str());
        i++;
    }
    wclrtobot(disp.getWin());
}

void System::remove(int i) { processes.erase(processes.begin() + i); }
