#include "init.h"

bool init()
{
   //initialize the screen
   //set up memory and clear screan
   initscr();
   noecho();
   curs_set(0);

   if (!has_colors())
   {
      printw("Terminal does not support color");
      getchar();
      return false;
   }


   //setting color enum for uses with color_pair()
   //offset by 1 so that it starts on proper number

   start_color();
   init_pair(1, COLOR_GREEN, COLOR_BLACK);
   init_pair(2, COLOR_YELLOW, COLOR_BLACK);
   init_pair(3, COLOR_RED, COLOR_BLACK);

   return true;
}