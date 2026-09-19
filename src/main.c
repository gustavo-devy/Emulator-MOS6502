#include <stdio.h>
#include "cpu/cpu.h"
#include "bus/bus.h"
#include "instruction/instruction.h"

static void run_instruction(CPU *cpu)
{
    do
    {
        cpu_step(cpu);
    } while (cpu->cycles != 0);
}

static void reset_at(CPU *cpu, Bus *bus, uint16_t address)
{
    bus_init(bus);
    cpu->bus = bus;
    bus_write(bus, 0xFFFC, address & 0xFF);
    bus_write(bus, 0xFFFD, address >> 8);
    cpu_reset(cpu);
}

int main()
{
    CPU cpu = {0};
    Bus bus = {0};
    cpu.bus = &bus;

    init_instructions_table();

    return 0;
}