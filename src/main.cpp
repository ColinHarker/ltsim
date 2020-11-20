#include <ncurses.h>
#include <sys/ioctl.h>

WINDOW *borders;

int main()
{
  //initialize the screen
  //set up memory and clear screan
  initscr();
  raw();
  noecho();

  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  const int height = w.ws_row;
  const int width = w.ws_col;
  int start_y = 0;
  int start_x = 0;

  //WINDOW *win = newwin(height, width, start_y, start_x);
  WINDOW *disp = newwin(height / 2, width / 2, 0, 0);
  WINDOW *disp_2 = newwin(height, width / 2, width / 2, height);

  refresh();

  int left, right, top, bottom, tlc, trc, blc, brc;

  left = right = 0;
  top = bottom = 0;
  tlc = trc = blc = brc = 0;

  //wborder(win, left, right, top, bottom, tlc, trc, blc, brc);
  box(disp, 0, 0);
  box(disp_2, 0, 0);

  //wrefresh(win);
  //wrefresh(disp);
  wrefresh(disp_2);

  getch();

  //deallocates and ends ncurses
  endwin();

  return 0;
}
