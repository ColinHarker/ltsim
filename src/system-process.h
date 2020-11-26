#ifndef SYSTEM_PROCESS_H
#define SYSTEM_PROCESS_H

#include "linker.h"

class SystemProcess
{
private:
    std::string user, pid, apu, mem, vsz, rss, tty, stat, start, time, command;

public:
    SystemProcess();
    SystemProcess(std::string, std::string, std::string, std::string,
                  std::string, std::string, std::string, std::string,
                  std::string, std::string, std::string);

    void parse(const char*);
};

#endif