#include "linker.h"

int main()
{
   if (!init())
   {
      return EXIT_FAILURE;
   }

   struct winsize w;
   ioctl(0, TIOCGWINSZ, &w);

   const int T_ROWS = w.ws_row;
   const int T_COLS = w.ws_col;
   bool running = true;

   WindowWrap disp(T_ROWS / 2, T_COLS / 2, 0, 0);
   WindowWrap disp_2(T_ROWS / 2, T_COLS / 2, 0, T_COLS / 2);
   WindowWrap menu((T_ROWS / 2) + 1, T_COLS, T_ROWS / 2, 0);

   refresh();

   box(disp_2.getWin(), 0, 0);
   box(menu.getWin(), 0, 0);

   wrefresh(disp.getWin());
   wrefresh(disp_2.getWin());
   wrefresh(menu.getWin());

   CpuReader cpu;

   displayElement(disp, 2, 2, cpu.getModelName(), flag::standard, flag::none);

   while (running)
   {
      updateWindowOne(disp, cpu);

      std::string ps = exec("ps -aux");
      mvwprintw(menu.getWin(), 1, 2, ps.c_str());

      wrefresh(menu.getWin());
      wrefresh(disp.getWin());
      sleep(1);
   }

   //deallocates and ends ncurses
   endwin();

   return 0;
}
