#include <ncurses.h>

WINDOW* borders;

int main(){
  //initialize the screen
  //set up memory and clear screan
  initscr();

  WINDOW* win = newwin(10, 10, 1, 1);
  box(win, '*', '*');
  touchwin(win);
  wrefresh(win);

  getch();

  //refreshes screen to match what is in memory
  refresh();


  getch();

  //deallocates and ends ncurses
  endwin();

  return 0;
}
