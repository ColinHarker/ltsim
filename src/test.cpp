
#include "system.h"
#include "utils.h"

void TEST_1()
{
    System ps = exec("ps -aux");
    ps.print();
}

int main()
{
    std::cout << "Starting tests..." << std::endl;
    TEST_1();

    return EXIT_SUCCESS;
}
