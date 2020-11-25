#include "utils.h"

void displayElement(WindowWrap &disp, int row, int col, std::string element, flag::print flag, flag::color c)
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

System exec(const char *cmd)
{
   System sys;
   
   std::array<char, 128> buffer;
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
      result += buffer.data();
   }
   return sys;
}