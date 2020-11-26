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

void System::display(WindowWrap& disp)
{
    int i = 1;
    for (SystemProcess sp : processes)
    {
        mvwprintw(disp.getWin(), i, 2, sp.toString().c_str());
        i++;
    }
}