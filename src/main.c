#include <stdio.h>
#include "cpu/cpu.h"
#include "bus/bus.h"

void test_cpu_reset(CPU *cpu, Bus *bus);

int main()
{
    CPU cpu = {0};
    Bus bus = {0};

    test_cpu_reset(&cpu, &bus);

    return 0;
}