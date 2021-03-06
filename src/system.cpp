// Copyright (c) 2020 Colin Harker

#include "system.h"

System::System(){};

void System::add(SystemProcess& sp) { m_processes.emplace_back(sp); }

SystemProcess System::get(int index) { return m_processes.at(index); }

void System::print()
{
   for(SystemProcess p : m_processes)
   {
      std::cout << p << "\n";
   }
}

void System::sort()
{
   std::sort(m_processes.begin(), m_processes.end(), [](SystemProcess& lhs, SystemProcess& rhs) {
      return lhs.getCpuAsFloat() > rhs.getCpuAsFloat();
   });
}

void System::display(WindowWrap& disp)
{
   constexpr char titles[] = " CPU   MEM  USER   PID      VSZ    RSS   TTY  STAT START  "
                             "TIME COMMAND";

   mvwprintw(disp.getWin(), 1, 0, titles);
   int ROW = 2;
   for(SystemProcess sp : m_processes)
   {
      float cpu = sp.getCpuAsFloat();
      float mem = sp.getMemAsFloat();

      std::string cpuStr = sp.getCpuAsString();
      std::string memStr = sp.getMemAsString();

      displayPercentColor(disp, cpu, cpuStr + " ", ROW, 1);
      displayPercentColor(disp, mem, memStr, ROW, 7);

      mvwprintw(disp.getWin(), ROW, 12, sp.toString().c_str());
      ROW++;
   }
   wclrtobot(disp.getWin());
}

void System::remove(int i) { m_processes.erase(m_processes.begin() + i); }
