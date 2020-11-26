#include "linker.h"

void TEST_1() { System ps = exec("ps -aux"); }

int main()
{
    TEST_1();

    return EXIT_SUCCESS;
}
