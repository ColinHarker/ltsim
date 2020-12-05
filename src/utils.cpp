// Copyright (c) 2020 Colin Harker

#include "utils.h"

void displayElement(WindowWrap& disp, int row, int col, std::string element,
                    flag::print flag, flag::color c)
{
    switch (flag)
    {
        case 0:
            wattron(disp.getWin(), COLOR_PAIR(c));
            mvwprintw(disp.getWin(), row, col, element.c_str());
            wattroff(disp.getWin(), COLOR_PAIR(c));
            break;
        case 1:
            mvwprintw(disp.getWin(), row, col, element.c_str());
            break;
        default:
            break;
    }
}

void displayPercentColor(WindowWrap& disp, float percent, std::string str,
                         int row, int col)
{
    if (percent == 0.0)
    {
        displayElement(disp, row, col, str, flag::standard, flag::none);
    }
    else if (percent < 60)
    {
        displayElement(disp, row, col, str, flag::use_color, flag::green);
    }
    else if (percent >= 60 && percent < 85)
    {
        displayElement(disp, row, col, str, flag::use_color, flag::yellow);
    }
    else
    {
        displayElement(disp, row, col, str, flag::use_color, flag::red);
    }
}

System exec(const char* cmd)
{
    System sys;

    std::array<char, 512> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        SystemProcess sp;
        sp.parse(buffer.data());
        sys.add(sp);
    }
    return sys;
}