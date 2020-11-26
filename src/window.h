#ifndef WINDOW_WRAP_H
#define WINDOW_WRAP_H

#include "linker.h"

class WindowWrap
{
private:
    int height, width, start_x, start_y;
    WINDOW* win;
    void createWindow();

public:
    WindowWrap(int h, int w, int x, int y);
    WINDOW* getWin();
    ~WindowWrap() {}
};
#endif