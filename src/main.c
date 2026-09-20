#include <stdio.h>
#include "cpu/cpu.h"
#include "bus/bus.h"
#include "instruction/instruction.h"

void execute_program(CPU *cpu, int view_registers)
{
    while (1)
    {
        do
        {
            cpu_step(cpu);
        } while (cpu->cycles != 0);

        if (view_registers)
        {
            cpu_dump_registers(cpu);
            cpu_current_instruction(cpu);

            char c = getchar();
            if (c == 'q')
                return;
        }
    }
}

int main()
{
    CPU cpu = {0};
    Bus bus = {0};

    bus_init(&bus);
    cpu.bus = &bus;

    init_instructions_table();

    bus_write(&bus, 0xFFFC, 0x00);
    bus_write(&bus, 0xFFFD, 0x80);
    cpu_reset(&cpu);

    bus_write(&bus, 0x8000, 0xA9); // LDA #0x00
    bus_write(&bus, 0x8001, 0x00);

    bus_write(&bus, 0x8002, 0x69); // ADC #0x01
    bus_write(&bus, 0x8003, 0x01);

    bus_write(&bus, 0x8004, 0xC9); // CMP #0x05
    bus_write(&bus, 0x8005, 0x05);

    bus_write(&bus, 0x8006, 0xD0); // BNE to 0x8000
    bus_write(&bus, 0x8007, 0xFA); // Relative address -6 (0x8000)

    bus_write(&bus, 0x8008, 0xA2); // LDX #0x10
    bus_write(&bus, 0x8009, 0x10);

    execute_program(&cpu, 1);

    return 0;
}