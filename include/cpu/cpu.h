#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "flags.h"
#include "bus/bus.h"

typedef struct CPU
{
    uint8_t A;   // Accumulator
    uint8_t X;   // X Register
    uint8_t Y;   // Y Register
    uint8_t SP;  // Stack Pointer
    uint16_t PC; // Program Counter
    Flags P;     // Processor Status (Flags)

    Bus *bus; // Pointer to the bus for memory access

    uint8_t cycles;        // Cycles for the current instruction
    uint32_t total_cycles; // Total cycles executed
} CPU;

void cpu_reset(CPU *cpu, Bus *bus);

#endif // CPU_H