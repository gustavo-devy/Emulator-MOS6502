#include <stdio.h>
#include "cpu/cpu.h"
#include "bus/bus.h"
#include "instruction/instruction.h"

void test_cpu_reset(CPU *cpu);
void test_lda_execution(CPU *cpu);
void test_sta_execution(CPU *cpu);

int main()
{
    CPU cpu = {0};
    Bus bus = {0};

    cpu.bus = &bus;

    init_instructions_table();
    test_sta_execution(&cpu);

    return 0;
}