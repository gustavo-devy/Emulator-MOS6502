#include "instruction/instruction.h"
#include "cpu/cpu.h"
#include <stdio.h>

Instruction instructions[256];

void init_instructions_table()
{
    for (int i = 0; i < 256; i++)
    {
        instructions[i] = (Instruction){"???", NULL, NULL, 0}; // Default to an invalid instruction
    }

    instructions[0xA9] = (Instruction){"LDA", cpu_inst_lda, addr_imm, 2};
    instructions[0x8D] = (Instruction){"STA", cpu_inst_sta, addr_abs, 4};
}

uint8_t addr_imm(CPU *cpu)
{
    cpu->addr_abs = cpu->PC;
    cpu->PC++;

    return 0;
}

uint8_t addr_abs(CPU *cpu)
{
    uint16_t lo = bus_read(cpu->bus, cpu->PC++);
    uint16_t hi = bus_read(cpu->bus, cpu->PC++);

    cpu->addr_abs = (hi << 8) | lo;

    return 0;
}