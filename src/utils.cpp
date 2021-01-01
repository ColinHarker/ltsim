// Copyright (c) 2020 Colin Harker

#include "utils.h"

using std::string;
using std::vector;

void displayElement(WindowWrap& disp, int row, int col, string element,
                    flag::printType flag, flag::color c)
{
    switch (flag)
    {
        case flag::printType::use_color:
            wattron(disp.getWin(), COLOR_PAIR(c));
            mvwprintw(disp.getWin(), row, col, element.c_str());
            wattroff(disp.getWin(), COLOR_PAIR(c));
            break;
        case flag::printType::standard:
            mvwprintw(disp.getWin(), row, col, element.c_str());
            break;
        default:
            break;
    }
}

void displayPercentColor(WindowWrap& disp, float percent, string str, int row,
                         int col)
{
    if (percent == 0.0)
    {
        displayElement(disp, row, col, str, flag::printType::standard,
                       flag::color::none);
    }
    else if (percent < 60)
    {
        displayElement(disp, row, col, str, flag::printType::use_color,
                       flag::color::green);
    }
    else if (percent >= 60 && percent < 85)
    {
        displayElement(disp, row, col, str, flag::printType::use_color,
                       flag::color::yellow);
    }
    else
    {
        displayElement(disp, row, col, str, flag::printType::use_color,
                       flag::color::red);
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

vector<string> parseStorageInformation()
{
    // list size of files
    // du -h --max-depth=1 | sort -hr

    // display storage mounts
    // df
    auto buffer_container = parseCommandLineOutput("df -h | sort -hr");
    return buffer_container;
}

vector<string> parseCommandLineOutput(const char* cmd)
{
    vector<string> buffer_container;

    std::array<char, 512> buffer;
    string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result = buffer.data();

        // skipping over unneccessary data in stream
        if ((result.find("Filesystem") != string::npos) ||
            (result.find("/dev/loop") != string::npos))
        {
            continue;
        }
        buffer_container.emplace_back(result);
    }

    return buffer_container;
}
