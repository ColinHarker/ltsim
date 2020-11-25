#ifndef UTILS_H
#define UTILS_H

#define APP_VERS 0.1
#define APP_NAME "ltsim"
#define APP_NAME_FULL "Linux Terminal System Information Monitor"

#ifdef _WIN32
std::cerr << "Program not built for windows os" << '\n';
exit(1);
#endif

#ifdef __APPLE__
std::cerr << "Program not built for apple os" << '\n';
exit(1);
#endif

#include "linker.h"

namespace flag
{
   enum color
   {
      none,
      green,
      yellow,
      red
   };

   enum print
   {
      use_color,
      standard
   };
} // namespace flag

void displayElement(WindowWrap &, int, int, std::string, flag::print, flag::color);
std::string exec(const char *);
#endif