#include "cpu/cpu.h"
#include "instruction/instruction.h"

void cpu_reset(CPU *cpu)
{
    uint16_t lo = bus_read(cpu->bus, 0xFFFC);
    uint16_t hi = bus_read(cpu->bus, 0xFFFD);

    cpu->PC = (hi << 8) | lo; // Set the program counter

    cpu->A = 0;
    cpu->X = 0;
    cpu->Y = 0;
    cpu->SP = 0xFD;    // Stack Pointer starts at 0xFD
    cpu->P = 0x00 | U; // Clear all flags except the unused one

    cpu->cycles = 0;
    cpu->total_cycles = 0;
}

void cpu_step(CPU *cpu)
{
    if (cpu->cycles == 0)
    {
        // Fetch the next instruction
        cpu->opcode = bus_read(cpu->bus, cpu->PC);
        cpu->PC++;

        // Execute the instruction
        Instruction inst = instructions[cpu->opcode];

        cpu->cycles = inst.cycles;

        uint8_t c1 = inst.addrmode(cpu);
        uint8_t c2 = inst.operate(cpu);
        cpu->cycles += (c1 & c2);
    }

    cpu->cycles--;
    cpu->total_cycles++;
}

uint8_t cpu_inst_lda(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    cpu->A = value;

    set_flag(cpu, Z, cpu->A == 0);
    set_flag(cpu, N, cpu->A & 0x80);

    return 1;
}

uint8_t cpu_inst_ldx(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    cpu->X = value;

    set_flag(cpu, Z, cpu->X == 0);
    set_flag(cpu, N, cpu->X & 0x80);

    return 1;
}

uint8_t cpu_inst_ldy(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    cpu->Y = value;

    set_flag(cpu, Z, cpu->Y == 0);
    set_flag(cpu, N, cpu->Y & 0x80);

    return 1;
}

uint8_t cpu_inst_sta(CPU *cpu)
{
    bus_write(cpu->bus, cpu->addr_abs, cpu->A);

    return 0;
}

uint8_t cpu_inst_stx(CPU *cpu)
{
    bus_write(cpu->bus, cpu->addr_abs, cpu->X);

    return 0;
}

uint8_t cpu_inst_sty(CPU *cpu)
{
    bus_write(cpu->bus, cpu->addr_abs, cpu->Y);

    return 0;
}

uint8_t cpu_inst_dex(CPU *cpu)
{
    cpu->X--;

    set_flag(cpu, Z, cpu->X == 0);
    set_flag(cpu, N, cpu->X & 0x80);

    return 0;
}

uint8_t cpu_inst_inx(CPU *cpu)
{
    cpu->X++;

    set_flag(cpu, Z, cpu->X == 0);
    set_flag(cpu, N, cpu->X & 0x80);

    return 0;
}

uint8_t cpu_inst_dey(CPU *cpu)
{
    cpu->Y--;

    set_flag(cpu, Z, cpu->Y == 0);
    set_flag(cpu, N, cpu->Y & 0x80);

    return 0;
}

uint8_t cpu_inst_iny(CPU *cpu)
{
    cpu->Y++;

    set_flag(cpu, Z, cpu->Y == 0);
    set_flag(cpu, N, cpu->Y & 0x80);

    return 0;
}

uint8_t cpu_inst_pha(CPU *cpu)
{
    bus_write(cpu->bus, 0x0100 + cpu->SP, cpu->A);
    cpu->SP--;

    return 0;
}

uint8_t cpu_inst_pla(CPU *cpu)
{
    cpu->SP++;
    cpu->A = bus_read(cpu->bus, 0x0100 + cpu->SP);

    set_flag(cpu, Z, cpu->A == 0);
    set_flag(cpu, N, cpu->A & 0x80);

    return 0;
}

uint8_t cpu_inst_cmp(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    uint16_t temp = (uint16_t)cpu->A - (uint16_t)value;

    set_flag(cpu, C, cpu->A >= value);
    set_flag(cpu, Z, (temp & 0x00FF) == 0);
    set_flag(cpu, N, temp & 0x80);

    return 1;
}

uint8_t cpu_inst_cpx(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    uint16_t temp = (uint16_t)cpu->X - (uint16_t)value;

    set_flag(cpu, C, cpu->X >= value);
    set_flag(cpu, Z, (temp & 0x00FF) == 0);
    set_flag(cpu, N, temp & 0x80);

    return 1;
}

uint8_t cpu_inst_cpy(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    uint16_t temp = (uint16_t)cpu->Y - (uint16_t)value;

    set_flag(cpu, C, cpu->Y >= value);
    set_flag(cpu, Z, (temp & 0x00FF) == 0);
    set_flag(cpu, N, temp & 0x80);

    return 1;
}

uint8_t cpu_inst_bne(CPU *cpu)
{
    if (!get_flag(cpu, Z))
    {
        cpu->PC += cpu->addr_rel;

        if ((cpu->PC & 0xFF00) != ((cpu->PC - cpu->addr_rel) & 0xFF00))
            return 2; // Page boundary crossed

        return 1; // Branch taken
    }

    return 0; // Branch not taken
}

uint8_t cpu_inst_beq(CPU *cpu)
{
    if (get_flag(cpu, Z))
    {
        cpu->PC += cpu->addr_rel;

        if ((cpu->PC & 0xFF00) != ((cpu->PC - cpu->addr_rel) & 0xFF00))
            return 2; // Page boundary crossed

        return 1; // Branch taken
    }

    return 0; // Branch not taken
}

uint8_t cpu_inst_jsr(CPU *cpu)
{
    uint16_t return_addr = cpu->PC - 1;

    bus_write(cpu->bus, 0x0100 + cpu->SP, (return_addr >> 8) & 0xFF);
    cpu->SP--;
    bus_write(cpu->bus, 0x0100 + cpu->SP, return_addr & 0xFF);
    cpu->SP--;

    cpu->PC = cpu->addr_abs;

    return 0;
}

uint8_t cpu_inst_rts(CPU *cpu)
{
    uint16_t low_byte, high_byte;

    cpu->SP++;
    low_byte = bus_read(cpu->bus, 0x0100 + cpu->SP);

    cpu->SP++;
    high_byte = bus_read(cpu->bus, 0x0100 + cpu->SP);

    uint16_t return_addr = (high_byte << 8) | low_byte;

    cpu->PC = return_addr + 1;

    return 0;
}

uint8_t cpu_inst_jmp(CPU *cpu)
{
    cpu->PC = cpu->addr_abs;

    return 0;
}

uint8_t cpu_inst_clc(CPU *cpu)
{
    set_flag(cpu, C, false);

    return 0;
}

uint8_t cpu_inst_sec(CPU *cpu)
{
    set_flag(cpu, C, true);

    return 0;
}

uint8_t cpu_inst_and(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    cpu->A = (cpu->A & value);

    set_flag(cpu, Z, cpu->A == 0);
    set_flag(cpu, N, cpu->A & 0x80);

    return 1;
}

uint8_t cpu_inst_ora(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    cpu->A = (cpu->A | value);

    set_flag(cpu, Z, cpu->A == 0);
    set_flag(cpu, N, cpu->A & 0x80);

    return 1;
}