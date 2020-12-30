// Copyright (c) 2020 Colin Harker

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

    void parse(const std::string&);
    void print();
    float getCpuAsFloat() const;
    float getMemAsFloat() const;
    std::string getCpuAsString() const;
    std::string getMemAsString() const;
    std::string toString();
    void setCpu(const std::string& std);
};

#endif