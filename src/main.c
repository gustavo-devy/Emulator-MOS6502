#include <stdio.h>
#include "cpu/cpu.h"
#include "bus/bus.h"
#include "instruction/instruction.h"

int main()
{
    CPU cpu = {0};
    Bus bus = {0};

    bus_init(&bus);
    cpu.bus = &bus;
    cpu_reset(&cpu);

    init_instructions_table();

    return 0;
}