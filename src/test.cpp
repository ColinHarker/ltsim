// Copyright (c) 2020 Colin Harker

#include "system.h"
#include "memory.h"
#include "utils.h"
#include "cpu.h"

void TEST_1()
{
    std::cout << "Testing system processes"
              << "\n";
    System ps = exec("ps -aux");
    ps.print();
}
void TEST_2()
{
    std::cout << "Testing cpu core utilization"
              << "\n";
    Cpu cpu;
    cpu.run();
    std::vector<CpuReader> cores = cpu.getCores();
    for (auto core : cores)
    {
        std::cout << core.getUtil() << "\n";
    }
}

void TEST_3()
{
    std::cout << "Testing memory usage"
              << "\n";
    RandomAccessMemory ram;
    ram.run();
    std::cout << "Mem: " << ram.getMemUsage() << "\n"
              << "Swap: " << ram.getSwapUsage() << "\n";
}

int main()
{
    std::cout << "Starting tests..." << std::endl;
    TEST_1();
    TEST_2();
    TEST_3();

    return EXIT_SUCCESS;
}
