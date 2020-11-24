#include "linker.h"

int main()
{
  //initialize the screen
  //set up memory and clear screan
  initscr();
  raw();
  noecho();

  if (!has_colors())
  {
    printw("Terminal does not support color");
    getchar();
    return -1;
  }
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  const int T_ROWS = w.ws_row;
  const int T_COLS = w.ws_col;

  WindowWrap disp(T_ROWS / 2, T_COLS / 2, 0, 0);
  WindowWrap disp_2(T_ROWS, T_COLS / 2, 0, T_COLS / 2);
  WindowWrap menu((T_ROWS / 2) + 1, T_COLS / 2, T_ROWS / 2, 0);

  refresh();

  box(disp.getWin(), 0, 0);
  box(disp_2.getWin(), 0, 0);
  box(menu.getWin(), 0, 0);

  wrefresh(disp.getWin());
  wrefresh(disp_2.getWin());
  wrefresh(menu.getWin());

  //allows us to use arrow keys
  keypad(menu.getWin(), true);

  std::array<std::string, 3> choices = {"One", "Two", "Three"};
  int choice = 0;
  int highlight = 0;

  //CpuReader *cpu;
  //std::thread cpu_t(&CpuReader::run, cpu, menu);
  //cpu.run(menu);
  //mvwprintw(menu.getWin(), 5, 1, to_string(util).c_str());

  while (1)
  {
    for (int i = 0; i < 3; i++)
    {
      if (i == highlight)
        //turn on element, reverse background color
        wattron(menu.getWin(), A_REVERSE);
      mvwprintw(menu.getWin(), i + 1, 1, choices.at(i).c_str());
      wattroff(menu.getWin(), A_REVERSE);
    }

    mvwprintw(disp.getWin(), 1, 2, "CPU");
    mvwprintw(disp.getWin(), 1, 7, "[");
    for (int i = 8; i < 30; i++)
    {
      wattron(disp.getWin(), COLOR_PAIR(1));
      mvwprintw(disp.getWin(), 1, i, "|");
      wattroff(disp.getWin(), COLOR_PAIR(1));
    }
    mvwprintw(disp.getWin(), 1, 40, "]");
    wrefresh(disp.getWin());
    choice = wgetch(menu.getWin());

    switch (choice)
    {
    case KEY_UP:
      highlight--;
      if (highlight < 0)
        highlight = 0;
      break;
    case KEY_DOWN:
      highlight++;
      if (highlight > 2)
        highlight = 2;
      break;
    default:
      break;
    }

    //if user presses ENTER key
    if (choice == 10)
      break;
  }

  mvwprintw(disp.getWin(), 0, 0, choices.at(highlight).c_str());

  getch();

  //deallocates and ends ncurses
  endwin();

  return 0;
}
