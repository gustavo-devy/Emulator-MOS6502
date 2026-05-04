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
}

uint8_t addr_imm(CPU *cpu)
{
    cpu->addr_abs = cpu->PC;
    cpu->PC++;

    return 0;
}