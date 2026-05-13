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

    // LDA Instructions
    instructions[0xA9] = (Instruction){"LDA", cpu_inst_lda, addr_imm, 2};
    instructions[0xA5] = (Instruction){"LDA", cpu_inst_lda, addr_zp, 3};
    instructions[0xB5] = (Instruction){"LDA", cpu_inst_lda, addr_zpx, 4};
    instructions[0xAD] = (Instruction){"LDA", cpu_inst_lda, addr_abs, 4};
    instructions[0xBD] = (Instruction){"LDA", cpu_inst_lda, addr_abx, 4};
    instructions[0xB9] = (Instruction){"LDA", cpu_inst_lda, addr_aby, 4};
    instructions[0xA1] = (Instruction){"LDA", cpu_inst_lda, addr_izx, 6};
    instructions[0xB1] = (Instruction){"LDA", cpu_inst_lda, addr_izy, 5};

    // LDX Instructions
    instructions[0xA2] = (Instruction){"LDX", cpu_inst_ldx, addr_imm, 2};
    instructions[0xA6] = (Instruction){"LDX", cpu_inst_ldx, addr_zp, 3};
    instructions[0xB6] = (Instruction){"LDX", cpu_inst_ldx, addr_zpy, 4};
    instructions[0xAE] = (Instruction){"LDX", cpu_inst_ldx, addr_abs, 4};
    instructions[0xBE] = (Instruction){"LDX", cpu_inst_ldx, addr_aby, 4};

    // STA Instructions
    instructions[0x8D] = (Instruction){"STA", cpu_inst_sta, addr_abs, 4};
}

uint8_t addr_imm(CPU *cpu)
{
    cpu->addr_abs = cpu->PC;
    cpu->PC++;

    return 0;
}

uint8_t addr_zp(CPU *cpu)
{
    cpu->addr_abs = bus_read(cpu->bus, cpu->PC++);

    return 0;
}

uint8_t addr_zpx(CPU *cpu)
{
    cpu->addr_abs = (bus_read(cpu->bus, cpu->PC++) + cpu->X) & 0xFF;

    return 0;
}

uint8_t addr_zpy(CPU *cpu)
{
    cpu->addr_abs = (bus_read(cpu->bus, cpu->PC++) + cpu->Y) & 0xFF;

    return 0;
}

uint8_t addr_abs(CPU *cpu)
{
    uint16_t lo = bus_read(cpu->bus, cpu->PC++);
    uint16_t hi = bus_read(cpu->bus, cpu->PC++);

    cpu->addr_abs = (hi << 8) | lo;

    return 0;
}

uint8_t addr_abx(CPU *cpu)
{
    uint16_t lo = bus_read(cpu->bus, cpu->PC++);
    uint16_t hi = bus_read(cpu->bus, cpu->PC++);

    cpu->addr_abs = ((hi << 8) | lo) + cpu->X;

    if ((cpu->addr_abs & 0xFF00) != (hi << 8)) // Verify if page boundary is crossed
        return 1;

    return 0;
}

uint8_t addr_aby(CPU *cpu)
{
    uint16_t lo = bus_read(cpu->bus, cpu->PC++);
    uint16_t hi = bus_read(cpu->bus, cpu->PC++);

    cpu->addr_abs = ((hi << 8) | lo) + cpu->Y;

    if ((cpu->addr_abs & 0xFF00) != (hi << 8)) // Verify if page boundary is crossed
        return 1;

    return 0;
}

uint8_t addr_ind(CPU *cpu)
{
    uint16_t ptr_lo = bus_read(cpu->bus, cpu->PC++);
    uint16_t ptr_hi = bus_read(cpu->bus, cpu->PC++);

    uint16_t ptr = (ptr_hi << 8) | ptr_lo;

    // Handle page boundary bug
    if (ptr_lo == 0xFF)
    {
        cpu->addr_abs = (bus_read(cpu->bus, ptr & 0xFF00) << 8) | bus_read(cpu->bus, ptr);
    }
    else
    {
        cpu->addr_abs = (bus_read(cpu->bus, ptr + 1) << 8) | bus_read(cpu->bus, ptr);
    }

    return 0;
}

uint8_t addr_izx(CPU *cpu)
{
    uint16_t t = bus_read(cpu->bus, cpu->PC++);
    uint16_t lo = bus_read(cpu->bus, (t + cpu->X) & 0xFF);
    uint16_t hi = bus_read(cpu->bus, (t + cpu->X + 1) & 0xFF);

    cpu->addr_abs = (hi << 8) | lo;

    return 0;
}

uint8_t addr_izy(CPU *cpu)
{
    uint16_t t = bus_read(cpu->bus, cpu->PC++);
    uint16_t lo = bus_read(cpu->bus, t & 0xFF);
    uint16_t hi = bus_read(cpu->bus, (t + 1) & 0xFF);

    cpu->addr_abs = ((hi << 8) | lo) + cpu->Y;

    if ((cpu->addr_abs & 0xFF00) != (hi << 8)) // Verify if page boundary is crossed
        return 1;

    return 0;
}

uint8_t addr_rel(CPU *cpu)
{
    cpu->addr_rel = bus_read(cpu->bus, cpu->PC++);

    if (cpu->addr_rel & 0x80) // If the sign bit is set, we need to convert to a negative offset
        cpu->addr_rel |= 0xFF00;

    return 0;
}