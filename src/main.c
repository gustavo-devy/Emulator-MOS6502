#include <assert.h>
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

    init_instructions_table();

    reset_at(&cpu, &bus, 0x8000);
    set_flag(&cpu, Z, false);
    bus_write(&bus, 0x8000, 0xF0); // BEQ
    bus_write(&bus, 0x8001, 0x02); // Relative offset
    run_instruction(&cpu);
    assert(cpu.PC == 0x8002);
    assert(cpu.total_cycles == 2); // Branch not taken

    reset_at(&cpu, &bus, 0x8000);
    set_flag(&cpu, Z, true);
    bus_write(&bus, 0x8000, 0xF0); // BEQ
    bus_write(&bus, 0x8001, 0x02); // Relative offset
    run_instruction(&cpu);
    assert(cpu.PC == 0x8004);
    assert(cpu.total_cycles == 3); // Branch taken: 2 + 1

    reset_at(&cpu, &bus, 0x80FD);
    set_flag(&cpu, Z, true);
    bus_write(&bus, 0x80FD, 0xF0); // BEQ
    bus_write(&bus, 0x80FE, 0x02); // Crosses from 0x80xx to 0x81xx
    run_instruction(&cpu);
    assert(cpu.PC == 0x8101);
    assert(cpu.total_cycles == 4); // Branch + page crossing: 2 + 1 + 1

    printf("BEQ branch and cycle tests passed.\n");
    return 0;
}