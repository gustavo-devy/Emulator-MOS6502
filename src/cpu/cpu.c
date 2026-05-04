#include "cpu/cpu.h"

void cpu_reset(CPU *cpu, Bus *bus)
{
    uint16_t lo = bus_read(bus, 0xFFFC);
    uint16_t hi = bus_read(bus, 0xFFFD);

    cpu->PC = (hi << 8) | lo; // Set the program counter

    cpu->A = 0;
    cpu->X = 0;
    cpu->Y = 0;
    cpu->SP = 0xFD;    // Stack Pointer starts at 0xFD
    cpu->P = 0x00 | U; // Clear all flags except the unused one

    cpu->cycles = 0;
    cpu->total_cycles = 0;
}