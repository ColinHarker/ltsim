// Copyright (c) 2020 Colin Harker

#include "system-process.h"

SystemProcess::SystemProcess(){};

void SystemProcess::parse(const std::string& buffer)
{
   std::istringstream ss(buffer);

   ss >> user >> pid >> cpu >> mem >> vsz >> rss >> tty >> stat >> start >> time;
   std::string word;
   while(ss >> word)
   {
      command += word;
   }

   size_t bufferSize = COLS - 63;

   if(command.length() > bufferSize)
   {
      command = command.substr(1, bufferSize);
   }
}

std::ostream& operator<<(std::ostream& os, SystemProcess& sp)
{
   os << sp.toString();
   return os;
}

std::string SystemProcess::toString()
{
   std::ostringstream oss;
   oss << std::setw(5) << user << "" << std::setw(5) << pid << " "
       << std::setw(8) << vsz << " " << std::setw(6) << rss << " "
       << std::setw(5) << tty << " " << std::setw(5) << stat << " "
       << std::setw(5) << start << " " << std::setw(5) << time << " "
       << command << std::endl;
   return oss.str();
}

float SystemProcess::getCpuAsFloat() const { return atoi(cpu.c_str()); }

std::string SystemProcess::getCpuAsString() const { return cpu; }

float SystemProcess::getMemAsFloat() const { return atoi(mem.c_str()); }

std::string SystemProcess::getMemAsString() const { return mem; }

void SystemProcess::setCpu(const std::string& str) { cpu = str; }
