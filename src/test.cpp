
#include "system.h"
#include "utils.h"
#include "cpu.h"

void TEST_1()
{
    System ps = exec("ps -aux");
    ps.print();
}
void TEST_2()
{
    Cpu cpu;
    cpu.run();
    std::vector<CpuReader> cores = cpu.getCores();
    for (auto core : cores)
    {
        std::cout << core.getUtil() << "\n";
    }
}

int main()
{
    std::cout << "Starting tests..." << std::endl;
    TEST_1();
    TEST_2();

    return EXIT_SUCCESS;
}
