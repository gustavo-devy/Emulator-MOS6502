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

    // LDY Instructions
    instructions[0xA0] = (Instruction){"LDY", cpu_inst_ldy, addr_imm, 2};
    instructions[0xA4] = (Instruction){"LDY", cpu_inst_ldy, addr_zp, 3};
    instructions[0xB4] = (Instruction){"LDY", cpu_inst_ldy, addr_zpx, 4};
    instructions[0xAC] = (Instruction){"LDY", cpu_inst_ldy, addr_abs, 4};
    instructions[0xBC] = (Instruction){"LDY", cpu_inst_ldy, addr_abx, 4};

    // STA Instructions
    instructions[0x85] = (Instruction){"STA", cpu_inst_sta, addr_zp, 3};
    instructions[0x95] = (Instruction){"STA", cpu_inst_sta, addr_zpx, 4};
    instructions[0x8D] = (Instruction){"STA", cpu_inst_sta, addr_abs, 4};
    instructions[0x9D] = (Instruction){"STA", cpu_inst_sta, addr_abx, 5};
    instructions[0x99] = (Instruction){"STA", cpu_inst_sta, addr_aby, 5};
    instructions[0x81] = (Instruction){"STA", cpu_inst_sta, addr_izx, 6};
    instructions[0x91] = (Instruction){"STA", cpu_inst_sta, addr_izy, 6};

    // STX Instructions
    instructions[0x86] = (Instruction){"STX", cpu_inst_stx, addr_zp, 3};
    instructions[0x96] = (Instruction){"STX", cpu_inst_stx, addr_zpy, 4};
    instructions[0x8E] = (Instruction){"STX", cpu_inst_stx, addr_abs, 4};

    // STY Instructions
    instructions[0x84] = (Instruction){"STY", cpu_inst_sty, addr_zp, 3};
    instructions[0x94] = (Instruction){"STY", cpu_inst_sty, addr_zpx, 4};
    instructions[0x8C] = (Instruction){"STY", cpu_inst_sty, addr_abs, 4};

    // DEX Instruction
    instructions[0xCA] = (Instruction){"DEX", cpu_inst_dex, addr_impl, 2};

    // INX Instruction
    instructions[0xE8] = (Instruction){"INX", cpu_inst_inx, addr_impl, 2};

    // DEY Instruction
    instructions[0x88] = (Instruction){"DEY", cpu_inst_dey, addr_impl, 2};

    // INY Instruction
    instructions[0xC8] = (Instruction){"INY", cpu_inst_iny, addr_impl, 2};

    // INC Instructions
    instructions[0xE6] = (Instruction){"INC", cpu_inst_inc, addr_zp, 5};
    instructions[0xF6] = (Instruction){"INC", cpu_inst_inc, addr_zpx, 6};
    instructions[0xEE] = (Instruction){"INC", cpu_inst_inc, addr_abs, 6};
    instructions[0xFE] = (Instruction){"INC", cpu_inst_inc, addr_abx, 7};

    // DEC Instructions
    instructions[0xC6] = (Instruction){"DEC", cpu_inst_dec, addr_zp, 5};
    instructions[0xD6] = (Instruction){"DEC", cpu_inst_dec, addr_zpx, 6};
    instructions[0xCE] = (Instruction){"DEC", cpu_inst_dec, addr_abs, 6};
    instructions[0xDE] = (Instruction){"DEC", cpu_inst_dec, addr_abx, 7};

    // PHA Instruction
    instructions[0x48] = (Instruction){"PHA", cpu_inst_pha, addr_impl, 3};

    // PLA Instruction
    instructions[0x68] = (Instruction){"PLA", cpu_inst_pla, addr_impl, 4};

    // CMP Instructions
    instructions[0xC9] = (Instruction){"CMP", cpu_inst_cmp, addr_imm, 2};
    instructions[0xC5] = (Instruction){"CMP", cpu_inst_cmp, addr_zp, 3};
    instructions[0xD5] = (Instruction){"CMP", cpu_inst_cmp, addr_zpx, 4};
    instructions[0xCD] = (Instruction){"CMP", cpu_inst_cmp, addr_abs, 4};
    instructions[0xDD] = (Instruction){"CMP", cpu_inst_cmp, addr_abx, 4};
    instructions[0xD9] = (Instruction){"CMP", cpu_inst_cmp, addr_aby, 4};
    instructions[0xC1] = (Instruction){"CMP", cpu_inst_cmp, addr_izx, 6};
    instructions[0xD1] = (Instruction){"CMP", cpu_inst_cmp, addr_izy, 5};

    // CPX Instructions
    instructions[0xE0] = (Instruction){"CPX", cpu_inst_cpx, addr_imm, 2};
    instructions[0xE4] = (Instruction){"CPX", cpu_inst_cpx, addr_zp, 3};
    instructions[0xEC] = (Instruction){"CPX", cpu_inst_cpx, addr_abs, 4};

    // CPY Instructions
    instructions[0xC0] = (Instruction){"CPY", cpu_inst_cpy, addr_imm, 2};
    instructions[0xC4] = (Instruction){"CPY", cpu_inst_cpy, addr_zp, 3};
    instructions[0xCC] = (Instruction){"CPY", cpu_inst_cpy, addr_abs, 4};

    // BNE Instruction
    instructions[0xD0] = (Instruction){"BNE", cpu_inst_bne, addr_rel, 2};

    // BEQ Instruction
    instructions[0xF0] = (Instruction){"BEQ", cpu_inst_beq, addr_rel, 2};

    // JRS
    instructions[0x20] = (Instruction){"JSR", cpu_inst_jsr, addr_abs, 6};

    // RTS
    instructions[0x60] = (Instruction){"RTS", cpu_inst_rts, addr_impl, 6};

    // JMP Instructions
    instructions[0x4C] = (Instruction){"JMP", cpu_inst_jmp, addr_abs, 3};
    instructions[0x6C] = (Instruction){"JMP", cpu_inst_jmp, addr_ind, 5};

    // CLC Instruction
    instructions[0x18] = (Instruction){"CLC", cpu_inst_clc, addr_impl, 2};

    // SEC Instruction
    instructions[0x38] = (Instruction){"SEC", cpu_inst_sec, addr_impl, 2};

    // AND Instructions
    instructions[0x29] = (Instruction){"AND", cpu_inst_and, addr_imm, 2};
    instructions[0x25] = (Instruction){"AND", cpu_inst_and, addr_zp, 3};
    instructions[0x35] = (Instruction){"AND", cpu_inst_and, addr_zpx, 4};
    instructions[0x2D] = (Instruction){"AND", cpu_inst_and, addr_abs, 4};
    instructions[0x3D] = (Instruction){"AND", cpu_inst_and, addr_abx, 4};
    instructions[0x39] = (Instruction){"AND", cpu_inst_and, addr_aby, 4};
    instructions[0x21] = (Instruction){"AND", cpu_inst_and, addr_izx, 6};
    instructions[0x31] = (Instruction){"AND", cpu_inst_and, addr_izy, 5};

    // ORA Instructions
    instructions[0x09] = (Instruction){"ORA", cpu_inst_ora, addr_imm, 2};
    instructions[0x05] = (Instruction){"ORA", cpu_inst_ora, addr_zp, 3};
    instructions[0x15] = (Instruction){"ORA", cpu_inst_ora, addr_zpx, 4};
    instructions[0x0D] = (Instruction){"ORA", cpu_inst_ora, addr_abs, 4};
    instructions[0x1D] = (Instruction){"ORA", cpu_inst_ora, addr_abx, 4};
    instructions[0x19] = (Instruction){"ORA", cpu_inst_ora, addr_aby, 4};
    instructions[0x01] = (Instruction){"ORA", cpu_inst_ora, addr_izx, 6};
    instructions[0x11] = (Instruction){"ORA", cpu_inst_ora, addr_izy, 5};

    // EOR Instructions
    instructions[0x49] = (Instruction){"EOR", cpu_inst_eor, addr_imm, 2};
    instructions[0x45] = (Instruction){"EOR", cpu_inst_eor, addr_zp, 3};
    instructions[0x55] = (Instruction){"EOR", cpu_inst_eor, addr_zpx, 4};
    instructions[0x4D] = (Instruction){"EOR", cpu_inst_eor, addr_abs, 4};
    instructions[0x5D] = (Instruction){"EOR", cpu_inst_eor, addr_abx, 4};
    instructions[0x59] = (Instruction){"EOR", cpu_inst_eor, addr_aby, 4};
    instructions[0x41] = (Instruction){"EOR", cpu_inst_eor, addr_izx, 6};
    instructions[0x51] = (Instruction){"EOR", cpu_inst_eor, addr_izy, 5};

    // BIT Instructions
    instructions[0x24] = (Instruction){"BIT", cpu_inst_bit, addr_zp, 3};
    instructions[0x2C] = (Instruction){"BIT", cpu_inst_bit, addr_abs, 4};
}

uint8_t addr_impl(CPU *cpu)
{
    (void)cpu; // Unused parameter
    // Implied addressing mode does not require any additional data
    return 0;
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