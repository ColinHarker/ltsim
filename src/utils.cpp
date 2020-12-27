// Copyright (c) 2020 Colin Harker

#include "utils.h"

void displayElement(WindowWrap& disp, int row, int col, std::string element,
                    flag::print_type flag, flag::color c)
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

System parseSystemInformation()
{
    auto buffer_container = parseCommandLineOutput("ps -aux");
    System sys;

    for (auto buffer : buffer_container)
    {
        SystemProcess sp;
        sp.parse(buffer);
        sys.add(sp);
    }
    return sys;
}

std::vector<std::string> parseStorageInformation()
{
    // list size of files
    // du -h --max-depth=1 | sort -hr

    // display storage mounts
    // df
    auto buffer_container =
        parseCommandLineOutput("du -h --max-depth=1 | sort -hr");
    return buffer_container;
}

std::vector<std::string> parseCommandLineOutput(const char* cmd)
{
    std::vector<std::string> buffer_container;

    std::array<char, 512> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        buffer_container.emplace_back(buffer.data());
    }

    return buffer_container;
}