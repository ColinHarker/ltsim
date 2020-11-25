#include "runtime.h"

void updateWindowOne(WindowWrap &disp, CpuReader &cpu)
{
   displayElement(disp, 0, 2, cpu.getVersion(), flag::standard, flag::none);

   float util = cpu.run();

   displayCpuLevel(disp, util);
}

void displayCpuLevel(WindowWrap &disp, float util)
{
   displayElement(disp, 3, 2, "CPU", flag::standard, flag::none);
   displayElement(disp, 3, 7, "[", flag::standard, flag::none);

   int level = static_cast<int>((32 * (util / 100)) + 8);
   for (int i = 0; i < 32; i++)
   {
      int offset = i + 8;
      if (offset > level)
      {
         mvwprintw(disp.getWin(), 3, offset, " ");
      }
      else
      {
         // less than 60% cpu utilization
         if (util < 60)
            displayElement(disp, 3, offset, "|", flag::use_color, flag::green);
         else if (util >= 60 && util < 85)
            displayElement(disp, 3, offset, "|", flag::use_color, flag::yellow);
         else
            displayElement(disp, 3, offset, "|", flag::use_color, flag::red);
      }
      wrefresh(disp.getWin());
   }
   mvwprintw(disp.getWin(), 3, 40, "]");

   std::ostringstream ss;
   ss << std::setprecision(2) << std::setw(4) << std::fixed << util << " %%";
   mvwprintw(disp.getWin(), 3, 42, ss.str().c_str());
}
