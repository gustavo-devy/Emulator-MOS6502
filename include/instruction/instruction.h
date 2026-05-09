#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>

// Forward declaration
typedef struct CPU CPU;

typedef uint8_t (*CPU_Func)(CPU *cpu);

typedef struct Instruction
{
    char name[4];
    CPU_Func operate;
    CPU_Func addrmode;
    uint8_t cycles;
} Instruction;

extern Instruction instructions[256];

void init_instructions_table();

// Addressing mode functions
uint8_t addr_imm(CPU *cpu);
uint8_t addr_abs(CPU *cpu);

#endif // INSTRUCTION_H