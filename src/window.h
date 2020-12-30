// Copyright (c) 2020 Colin Harker

#ifndef WINDOW_WRAP_H
#define WINDOW_WRAP_H

typedef struct _win_st WINDOW;

class WindowWrap
{
private:
    int m_height;
    int m_width;
    int m_start_x;
    int m_start_y;

    WINDOW* m_win;
    void createWindow();

public:
    WindowWrap(int h, int w, int x, int y);

    int getWidth() const;

    int getHeight() const;

    WINDOW* getWin() const;
};
#endif