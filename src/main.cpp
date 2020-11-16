#include <ncurses.h>

WINDOW* borders;

int main(){
  //initialize the screen
  //set up memory and clear screan
  initscr();

  getch();

  //refreshes screen to match what is in memory
  refresh();


  getch();

  //deallocates and ends ncurses
  endwin();

  return 0;
}
