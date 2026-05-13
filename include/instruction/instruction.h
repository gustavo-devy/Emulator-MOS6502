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
uint8_t addr_impl(CPU *cpu); // Implied
uint8_t addr_imm(CPU *cpu);  // Immediate
uint8_t addr_zp(CPU *cpu);   // Zero Page
uint8_t addr_zpx(CPU *cpu);  // Zero Page,X
uint8_t addr_zpy(CPU *cpu);  // Zero Page,Y
uint8_t addr_abs(CPU *cpu);  // Absolute
uint8_t addr_abx(CPU *cpu);  // Absolute,X
uint8_t addr_aby(CPU *cpu);  // Absolute,Y
uint8_t addr_ind(CPU *cpu);  // Indirect
uint8_t addr_izx(CPU *cpu);  // Indexed Indirect,X
uint8_t addr_izy(CPU *cpu);  // Indexed Indirect,Y
uint8_t addr_rel(CPU *cpu);  // Relative

#endif // INSTRUCTION_H