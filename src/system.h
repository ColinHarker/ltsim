#ifndef SYSTEM_H 
#define SYSTEM_H   

#include "linker.h"

class System{
private:
    std::vector<SystemProcess> processes;
public:
    System();
    void add(SystemProcess&);
};

class SystemProcess{
private:
    std::string
    user,
    pid,
    apu,
    mem,
    vsz,
    rss,
    tty,
    stat,
    start,
    time,
    command;

public:
    SystemProcess();
    SystemProcess(
        std::string,
        std::string, 
        std::string, 
        std::string, 
        std::string, 
        std::string,
        std::string, 
        std::string, 
        std::string, 
        std::string, 
        std::string);
    
    void parse(const char*);
};

#endif