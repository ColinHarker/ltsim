// Copyright (c) 2020 Colin Harker

#ifndef SYSTEM_PROCESS_H
#define SYSTEM_PROCESS_H

#include <iomanip>
#include <iostream>
#include <ncurses.h>
#include <ostream>
#include <sstream>
#include <string>

class SystemProcess
{
private:
   std::string user, pid, cpu, mem, vsz, rss, tty, stat, start, time, command;

public:
   SystemProcess();

   /** Takes in buffer from command line output, assigns values to class
     * members
     * @param buffer string of chars from command line output
     */
   void parse(const std::string& buffer);

   friend std::ostream& operator<<(std::ostream& os, SystemProcess& sp);

   float getCpuAsFloat() const;
   float getMemAsFloat() const;

   std::string getCpuAsString() const;
   std::string getMemAsString() const;
   std::string toString();

   void setCpu(const std::string& std);
};

#endif