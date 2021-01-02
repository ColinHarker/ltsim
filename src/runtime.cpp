// Copyright (c) 2020 Colin Harker

#include "runtime.h"

void updateCpuWindow(WindowWrap& disp, Cpu& cpuContainer, RandomAccessMemory& memory)
{
   constexpr int k_StartColumn      = 0;
   constexpr int k_StartRow         = 3;
   constexpr int k_GraphStartRow    = 7;
   constexpr int k_GraphStartColumn = 25;

   cpuContainer.run();
   memory.run();

   float util = cpuContainer.getCpu().getUtilization();
   float mem  = memory.getMemUsage();
   float swap = memory.getSwapUsage();

   std::vector<CpuReader> core = cpuContainer.getCores();

   displayUtilizationLevel(disp, util, "CPU", k_StartRow, k_StartColumn, flag::displayLength::standard);
   displayUtilizationLevel(disp, mem, "MEM", k_StartRow + 1, k_StartColumn, flag::displayLength::standard);
   displayUtilizationLevel(disp, swap, "SWAP", k_StartRow + 2, k_StartColumn, flag::displayLength::standard);

   displayCpuCores(disp, core, k_StartRow + 4, flag::displayLength::small);
}

void displayUtilizationLevel(WindowWrap& disp, float util, const std::string& label, int row, int startColumn, flag::displayLength length)
{
   constexpr int k_StandardLength = 32;
   constexpr int k_SmallLength    = 10;

   int displayLength = (length == flag::displayLength::standard) ? k_StandardLength : k_SmallLength;

   displayElement(disp, row, startColumn, label, flag::printType::standard, flag::color::none);
   displayElement(disp, row, startColumn + 5, "[", flag::printType::standard, flag::color::none);

   int level = static_cast<int>((displayLength * (util / 100)) + startColumn + 6);
   for(int i = 0; i < displayLength; i++)
   {
      int offset = i + startColumn + 6;
      if(offset > level)
      {
         mvwprintw(disp.getWin(), row, offset, " ");
      }
      else
      {
         displayPercentColor(disp, util, "|", row, offset);
      }
      wrefresh(disp.getWin());
   }
   mvwprintw(disp.getWin(), row, startColumn + displayLength + 6, "]");

   std::ostringstream ss;
   ss << std::setprecision(2) << std::setw(4) << std::fixed << util << "%%";
   displayPercentColor(disp, util, ss.str() + " ", row, startColumn + displayLength + 8);
}

void displayCpuCores(WindowWrap& disp, const std::vector<CpuReader> cores, int startRow, flag::displayLength length)
{
   int coreNumber = 1;  // Index 0 is taken up by full CPU
   for(auto& core : cores)
   {
      displayUtilizationLevel(disp, core.getUtilization(), "Core" + std::to_string(coreNumber), startRow, 0, length);
      startRow++;
      coreNumber++;
   }
}

void displayStorageInformation(WindowWrap& disp)
{
   displayElement(disp, 1, 0, "Filesystem      Size  Used Avail Use% Mounted on", flag::printType::standard, flag::color::none);

   auto storageVector = parseStorageInformation();

   int row = 2;
   for(auto element : storageVector)
   {
      displayElement(disp, row++, 0, element, flag::printType::standard, flag::color::none);
   }
}

void displaySystemProcesses(WindowWrap& disp)
{
   System sys = parseSystemInformation();
   sys.remove(0);  // removing the menu string
   sys.sort();
   sys.display(disp);
}
