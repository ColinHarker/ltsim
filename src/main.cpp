#include <ncurses.h>
#include <string>
#include <array>
#include <sys/ioctl.h>

using namespace std;

class WindowWrap
{
public:
  WindowWrap(int _height, int _width, int _x, int _y)
  {
    height = _height;
    width = _width;
    start_y = _y;
    start_x = _x;
    createWindow();
  }

  WINDOW *getWin() { return win; }

  ~WindowWrap() { free(win); }

private:
  int height;
  int width;
  int start_y;
  int start_x;
  WINDOW *win;

  void createWindow()
  {
    win = newwin(height, width, start_x, start_y);
  }
};

int main()
{
  //initialize the screen
  //set up memory and clear screan
  initscr();
  raw();
  noecho();

  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  const int T_ROWS = w.ws_row;
  const int T_COLS = w.ws_col;

  //WINDOW *disp = newwin(WinHeight / 2, terminal_width / 2, 0, 0);
  //WINDOW *disp_2 = newwin(WinHeight, terminal_width / 2, 0, width / 2);

  WindowWrap disp(T_ROWS / 2, T_COLS / 2, 0, 0);
  WindowWrap disp_2(T_ROWS, T_COLS / 2, 0, T_COLS / 2);
  WindowWrap menu((T_ROWS / 2) + 1, T_COLS / 2, T_ROWS / 2, 0);

  //WINDOW *menu = newwin((T_ROWS / 2) + 1, T_COLS / 2, T_ROWS / 2, 0);

  refresh();

  //wborder(win, left, right, top, bottom, tlc, trc, blc, brc);
  box(disp.getWin(), 0, 0);
  box(disp_2.getWin(), 0, 0);
  box(menu.getWin(), 0, 0);

  wrefresh(disp.getWin());
  wrefresh(disp_2.getWin());
  wrefresh(menu.getWin());

  //allows us to use arrow keys
  keypad(menu.getWin(), true);

  array<string, 3> choices = {"One", "Two", "Three"};
  int choice;
  int highlight = 0;

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
