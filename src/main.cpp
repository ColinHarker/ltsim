#include "linker.h"

int main()
{
  //initialize the screen
  //set up memory and clear screan
  initscr();
  //raw();
  noecho();
  curs_set(0);

  if (!has_colors())
  {
    printw("Terminal does not support color");
    getchar();
    return -1;
  }

  //setting color enum for uses with color_pair()
  //offset by 1 so that it starts on proper number

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);

  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  const int T_ROWS = w.ws_row;
  const int T_COLS = w.ws_col;

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

  mvwprintw(disp.getWin(), 2, 2, cpu.getModelName().c_str());

  while (1)
  {
    wattron(disp.getWin(), A_DIM);
    mvwprintw(disp.getWin(), 0, 2, cpu.getVersion().c_str());
    wattroff(disp.getWin(), A_DIM);
    float util = cpu.run();

    mvwprintw(disp.getWin(), 3, 2, "CPU");
    mvwprintw(disp.getWin(), 3, 7, "[");

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
        {
          wattron(disp.getWin(), COLOR_PAIR(green));
          mvwprintw(disp.getWin(), 3, offset, "|");
          wattroff(disp.getWin(), COLOR_PAIR(green));
        }
        else if (util >= 60 && util < 85)
        {
          wattron(disp.getWin(), COLOR_PAIR(yellow));
          mvwprintw(disp.getWin(), 3, offset, "|");
          wattroff(disp.getWin(), COLOR_PAIR(yellow));
        }
        else
        {
          wattron(disp.getWin(), COLOR_PAIR(red));
          mvwprintw(disp.getWin(), 3, offset, "|");
          wattroff(disp.getWin(), COLOR_PAIR(red));
        }
      }
      wrefresh(disp.getWin());
    }
    mvwprintw(disp.getWin(), 3, 40, "]");

    std::ostringstream ss;
    ss << std::setprecision(2) << std::setw(4) << std::fixed << util << " %%";
    mvwprintw(disp.getWin(), 3, 42, ss.str().c_str());

    std::string ps = exec("ps -aux");
    mvwprintw(menu.getWin(), 1, 2, ps.c_str());

    wrefresh(menu.getWin());
    wrefresh(disp.getWin());
    sleep(1);
  }

  getch();

  //deallocates and ends ncurses
  endwin();

  return 0;
}
