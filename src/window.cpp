// Copyright (c) 2020 Colin Harker

#include "window.h"
#include "ncurses.h"

WindowWrap::WindowWrap(int h, int w, int x, int y)
    : height_(h), width_(w), start_x_(x), start_y_(y)
{
    createWindow();
}

void WindowWrap::createWindow()
{
    win_ = newwin(height_, width_, start_x_, start_y_);
}

WINDOW* WindowWrap::getWin() const { return win_; }