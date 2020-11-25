#include "system.h"

System::System(){};

void System::add(SystemProcess& sp){
    processes.emplace_back(sp);
}

SystemProcess::SystemProcess(){};

SystemProcess::SystemProcess(
    std::string t_user,
    std::string t_pid,
    std::string t_apu,
    std::string t_mem,
    std::string t_vsz,
    std::string t_rss,
    std::string t_tty,
    std::string t_stat,
    std::string t_start,
    std::string t_time,
    std::string t_command) : 
    user(t_user),
    pid(t_pid),
    apu(t_apu),
    mem(t_mem),
    vsz(t_vsz),
    rss(t_rss),
    tty(t_tty),
    stat(t_stat),
    start(t_start),
    time(t_time),
    command(t_command)
    {};

void SystemProcess::parse(const char* buffer){

}