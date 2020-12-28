// Copyright (c) 2020 Colin Harker

#ifndef WINDOW_WRAP_H
#define WINDOW_WRAP_H

typedef struct _win_st WINDOW;

class WindowWrap
{
private:
    int height_;
    int width_;
    int start_x_;
    int start_y_;
    WINDOW* win_;
    void createWindow();

public:
    WindowWrap(int h, int w, int x, int y);

    WINDOW* getWin() const;
    ~WindowWrap() {}
};
#endif