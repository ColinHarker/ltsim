// Copyright (c) 2020 Colin Harker

#include "window.h"
#include "ncurses.h"

WindowWrap::WindowWrap(int h, int w, int x, int y)
   : m_height(h), m_width(w), m_start_x(x), m_start_y(y)
{
   createWindow();
}

void WindowWrap::createWindow()
{
   m_win = newwin(m_height, m_width, m_start_x, m_start_y);
}

WINDOW* WindowWrap::getWin() const { return m_win; }

int WindowWrap::getWidth() const { return m_width; }

int WindowWrap::getHeight() const { return m_height; }