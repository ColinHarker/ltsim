#include "system.h"

System::System(){};

void System::add(SystemProcess& sp) { processes.emplace_back(sp); }
