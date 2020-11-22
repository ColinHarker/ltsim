#include <ncurses.h>
#include <string>
#include <array>
#include <sys/ioctl.h>

using namespace std;

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
  //int start_y = 0;
  //int start_x = 0;

  WINDOW *disp = newwin(height / 2, width / 2, 0, 0);
  WINDOW *disp_2 = newwin(height, width / 2, 0, width / 2);
  WINDOW *menu = newwin((height / 2) + 1, width / 2, height / 2, 0);

  refresh();

  //wborder(win, left, right, top, bottom, tlc, trc, blc, brc);
  box(disp, 0, 0);
  box(disp_2, 0, 0);
  box(menu, 0, 0);

  wrefresh(disp);
  wrefresh(disp_2);
  wrefresh(menu);

  //allows us to use arrow keys
  keypad(menu, true);

  array<string, 3> choices = {"One", "Two", "Three"};
  int choice;
  int heighlight = 0;

  while (1)
  {
    for (int i = 0; i < 3; i++)
    {
      if (i == heighlight)
        //turn on element, reverse background color
        wattron(menu, A_REVERSE);
      mvwprintw(menu, i + 1, 1, choices.at(i).c_str());
      wattroff(menu, A_REVERSE);
    }
    choice = wgetch(menu);

    switch (choice)
    {
    case KEY_UP:
      heighlight--;
      if (heighlight < 0)
        heighlight = 0;
      break;
    case KEY_DOWN:
      heighlight++;
      if (heighlight > 2)
        heighlight = 2;
      break;
    default:
      break;
    }
    if (choice == 10)
      break;
  }

  mvwprintw(disp, 0, 0, choices.at(heighlight).c_str());

  getch();

  //deallocates and ends ncurses
  endwin();

  return 0;
}
