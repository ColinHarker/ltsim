#include <ncurses.h>

WINDOW *borders;

int main()
{
  //initialize the screen
  //set up memory and clear screan
  initscr();
  raw();
  noecho();

  int height, width, start_y, start_x;
  height = 10;
  width = 20;
  start_y = start_x = 10;

  WINDOW *win = newwin(height, width, start_y, start_x);
  refresh();

  int left, right, top, bottom, tlc, trc, blc, brc;

  left = right = static_cast<int>('|');
  top = bottom = static_cast<int>('-');
  tlc = trc = blc = brc = static_cast<int>('*');
  wborder(win, left, right, top, bottom, tlc, trc, blc, brc);
  mvwprintw(win, 1, 1, "this is my box");
  wrefresh(win);

  getch();

  //deallocates and ends ncurses
  endwin();

  return 0;
}
