// Copyright (c) 2020 Colin Harker

#ifndef INIT_H
#define INIT_H

#ifdef _WIN32
std::cerr << "Program not built for windows os" << '\n';
exit(1);
#endif

#ifdef __APPLE__
std::cerr << "Program not built for apple os" << '\n';
exit(1);
#endif

#include <ncurses.h>

bool init()
{

    initscr();   // initialize the screen
    noecho();    // keyboard input not registered to screen
    curs_set(0); // curser invisible

    if (!has_colors()) // check to see if the terminal in use supports colors
    {
        printw("Terminal does not support color");
        getchar();
        return false;
    }

    // initialize color pairs
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);

    return true;
}

#endif