#ifndef SYSTEM_PROCESS_H
#define SYSTEM_PROCESS_H

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ncurses.h>

class SystemProcess
{
private:
    std::string user, pid, cpu, mem, vsz, rss, tty, stat, start, time, command;

public:
    SystemProcess();
    SystemProcess(std::string, std::string, std::string, std::string,
                  std::string, std::string, std::string, std::string,
                  std::string, std::string, std::string);

    void parse(const char*);
    void print();
    float getCpuAsFloat();
    float getMemAsFloat();
    std::string getCpuAsString();
    std::string getMemAsString();
    std::string toString();
    void setCpu(std::string std);
};

#endif