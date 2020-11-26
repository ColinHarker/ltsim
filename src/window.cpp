#include "window.h"

WindowWrap::WindowWrap(int h, int w, int x, int y)
    : height(h), width(w), start_x(x), start_y(y)
{
    createWindow();
}

void WindowWrap::createWindow()
{
    win = newwin(height, width, start_x, start_y);
}

WINDOW* WindowWrap::getWin() { return win; }