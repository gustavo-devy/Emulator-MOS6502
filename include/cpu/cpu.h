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

    uint16_t addr_abs;
    uint16_t addr_rel;
    uint8_t opcode;
    uint8_t cycles;        // Cycles for the current instruction
    uint32_t total_cycles; // Total cycles executed
} CPU;

void cpu_step(CPU *cpu);
void cpu_reset(CPU *cpu);

// Instruction implementations
uint8_t cpu_inst_lda(CPU *cpu);
uint8_t cpu_inst_ldx(CPU *cpu);
uint8_t cpu_inst_sta(CPU *cpu);
uint8_t cpu_inst_dex(CPU *cpu);
uint8_t cpu_inst_inx(CPU *cpu);

#endif // CPU_H