#include <stdio.h>
#include <string.h>
#include "cpu/cpu.h"
#include "instruction/instruction.h"

void cpu_current_instruction(CPU *cpu)
{
    printf("Opcode: 0x%02X, Instruction: %s, Cycles: %d\n",
           cpu->opcode, instructions[cpu->opcode].name, instructions[cpu->opcode].cycles);
}

void cpu_dump_registers(CPU *cpu)
{
    printf("A:  0x%02X \nX:  0x%02X \nY:  0x%02X \nSP: 0x%02X \nPC: 0x%04X \nP:  0x%02X\n--------------> ",
           cpu->A, cpu->X, cpu->Y, cpu->SP, cpu->PC, cpu->P);
}

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

int cpu_step(CPU *cpu)
{
    if (cpu->cycles == 0)
    {
        // Fetch the next instruction
        cpu->opcode = bus_read(cpu->bus, cpu->PC);
        cpu->PC++;

        if (strcmp(instructions[cpu->opcode].name, "INV") == 0)
        {
            printf("Invalid opcode: 0x%02X at PC: 0x%04X\n", cpu->opcode, cpu->PC - 1);
            return -1;
        }

        // Execute the instruction
        Instruction inst = instructions[cpu->opcode];

        cpu->cycles = inst.cycles;

        uint8_t c1 = inst.addrmode(cpu);
        uint8_t c2 = inst.operate(cpu);
        cpu->cycles += (c1 & c2);
    }

    cpu->cycles--;
    cpu->total_cycles++;

    return 0;
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

uint8_t cpu_inst_tax(CPU *cpu)
{
    cpu->X = cpu->A;

    set_flag(cpu, Z, cpu->X == 0);
    set_flag(cpu, N, cpu->X & 0x80);

    return 0;
}

uint8_t cpu_inst_txa(CPU *cpu)
{
    cpu->A = cpu->X;

    set_flag(cpu, Z, cpu->A == 0);
    set_flag(cpu, N, cpu->A & 0x80);

    return 0;
}

uint8_t cpu_inst_tay(CPU *cpu)
{
    cpu->Y = cpu->A;

    set_flag(cpu, Z, cpu->Y == 0);
    set_flag(cpu, N, cpu->Y & 0x80);

    return 0;
}

uint8_t cpu_inst_tya(CPU *cpu)
{
    cpu->A = cpu->Y;

    set_flag(cpu, Z, cpu->A == 0);
    set_flag(cpu, N, cpu->A & 0x80);

    return 0;
}

uint8_t cpu_inst_tsx(CPU *cpu)
{
    cpu->X = cpu->SP;

    set_flag(cpu, Z, cpu->X == 0);
    set_flag(cpu, N, cpu->X & 0x80);

    return 0;
}

uint8_t cpu_inst_txs(CPU *cpu)
{
    cpu->SP = cpu->X;

    return 0;
}

uint8_t cpu_inst_adc(CPU *cpu)
{
    uint8_t data = bus_read(cpu->bus, cpu->addr_abs);
    uint16_t temp = (uint16_t)cpu->A + (uint16_t)data + (uint16_t)get_flag(cpu, C);

    set_flag(cpu, C, temp > 255);
    set_flag(cpu, Z, (temp & 0x00FF) == 0);
    set_flag(cpu, N, temp & 0x80);

    set_flag(cpu, V, (~((uint16_t)cpu->A ^ (uint16_t)data) & ((uint16_t)cpu->A ^ (uint16_t)temp)) & 0x0080);

    cpu->A = temp & 0x00FF;

    return 1;
}

uint8_t cpu_inst_sbc(CPU *cpu)
{
    uint8_t data = bus_read(cpu->bus, cpu->addr_abs);
    uint16_t value = ((uint16_t)data) ^ 0x00FF;

    uint16_t temp = (uint16_t)cpu->A + value + (uint16_t)get_flag(cpu, C);

    set_flag(cpu, C, temp & 0xFF00);
    set_flag(cpu, Z, (temp & 0x00FF) == 0);
    set_flag(cpu, N, temp & 0x80);
    set_flag(cpu, V, ((temp ^ (uint16_t)cpu->A) & (temp ^ value)) & 0x0080);

    cpu->A = temp & 0x00FF;

    return 1;
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

uint8_t cpu_inst_inc(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    value++;
    bus_write(cpu->bus, cpu->addr_abs, value);

    set_flag(cpu, Z, value == 0);
    set_flag(cpu, N, value & 0x80);

    return 0;
}

uint8_t cpu_inst_dec(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    value--;
    bus_write(cpu->bus, cpu->addr_abs, value);

    set_flag(cpu, Z, value == 0);
    set_flag(cpu, N, value & 0x80);

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

uint8_t cpu_inst_php(CPU *cpu)
{
    uint8_t status = cpu->P | U; // Set the unused flag before pushing
    bus_write(cpu->bus, 0x0100 + cpu->SP, status);
    cpu->SP--;

    return 0;
}

uint8_t cpu_inst_plp(CPU *cpu)
{
    cpu->SP++;
    cpu->P = bus_read(cpu->bus, 0x0100 + cpu->SP);
    cpu->P |= U; // Ensure the unused flag is always set

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

static uint8_t cpu_branch_if(CPU *cpu, bool condition)
{
    if (condition)
    {
        uint16_t old_pc = cpu->PC;

        cpu->PC += cpu->addr_rel;
        cpu->cycles++;

        if ((cpu->PC & 0xFF00) != (old_pc & 0xFF00))
            cpu->cycles++;
    }

    return 0;
}

uint8_t cpu_inst_bne(CPU *cpu)
{
    return cpu_branch_if(cpu, !get_flag(cpu, Z));
}

uint8_t cpu_inst_beq(CPU *cpu)
{
    return cpu_branch_if(cpu, get_flag(cpu, Z));
}

uint8_t cpu_inst_bpl(CPU *cpu)
{
    return cpu_branch_if(cpu, !get_flag(cpu, N));
}

uint8_t cpu_inst_bmi(CPU *cpu)
{
    return cpu_branch_if(cpu, get_flag(cpu, N));
}

uint8_t cpu_inst_bvc(CPU *cpu)
{
    return cpu_branch_if(cpu, !get_flag(cpu, V));
}

uint8_t cpu_inst_bvs(CPU *cpu)
{
    return cpu_branch_if(cpu, get_flag(cpu, V));
}

uint8_t cpu_inst_bcc(CPU *cpu)
{
    return cpu_branch_if(cpu, !get_flag(cpu, C));
}

uint8_t cpu_inst_bcs(CPU *cpu)
{
    return cpu_branch_if(cpu, get_flag(cpu, C));
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

uint8_t cpu_inst_rti(CPU *cpu)
{
    cpu->SP++;
    cpu->P = bus_read(cpu->bus, 0x0100 + cpu->SP);
    cpu->P |= U;

    cpu->SP++;
    uint16_t low_byte = bus_read(cpu->bus, 0x0100 + cpu->SP);

    cpu->SP++;
    uint16_t high_byte = bus_read(cpu->bus, 0x0100 + cpu->SP);

    cpu->PC = (high_byte << 8) | low_byte;

    return 0;
}

uint8_t cpu_inst_brk(CPU *cpu)
{
    cpu->PC++;

    bus_write(cpu->bus, 0x0100 + cpu->SP, (cpu->PC >> 8) & 0xFF);
    cpu->SP--;
    bus_write(cpu->bus, 0x0100 + cpu->SP, cpu->PC & 0xFF);
    cpu->SP--;

    set_flag(cpu, B, true);
    set_flag(cpu, I, true);
    bus_write(cpu->bus, 0x0100 + cpu->SP, cpu->P | U | B);
    cpu->SP--;

    uint16_t lo = bus_read(cpu->bus, 0xFFFE);
    uint16_t hi = bus_read(cpu->bus, 0xFFFF);
    cpu->PC = (hi << 8) | lo;

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

uint8_t cpu_inst_cli(CPU *cpu)
{
    set_flag(cpu, I, false);

    return 0;
}

uint8_t cpu_inst_cld(CPU *cpu)
{
    set_flag(cpu, D, false);

    return 0;
}

uint8_t cpu_inst_clv(CPU *cpu)
{
    set_flag(cpu, V, false);

    return 0;
}

uint8_t cpu_inst_sec(CPU *cpu)
{
    set_flag(cpu, C, true);

    return 0;
}

uint8_t cpu_inst_sei(CPU *cpu)
{
    set_flag(cpu, I, true);

    return 0;
}

uint8_t cpu_inst_sed(CPU *cpu)
{
    set_flag(cpu, D, true);

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

uint8_t cpu_inst_eor(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    cpu->A = (cpu->A ^ value);

    set_flag(cpu, Z, cpu->A == 0);
    set_flag(cpu, N, cpu->A & 0x80);

    return 1;
}

uint8_t cpu_inst_bit(CPU *cpu)
{
    uint8_t value = bus_read(cpu->bus, cpu->addr_abs);
    uint8_t result = cpu->A & value;

    set_flag(cpu, Z, result == 0);
    set_flag(cpu, N, value & 0x80);
    set_flag(cpu, V, value & 0x40);

    return 0;
}

uint8_t cpu_inst_asl(CPU *cpu)
{
    uint8_t value = cpu->opcode == 0x0A
                        ? cpu->A
                        : bus_read(cpu->bus, cpu->addr_abs);
    set_flag(cpu, C, value & 0x80); // Set carry flag if bit 7 is set
    value <<= 1;                    // Shift left

    if (cpu->opcode == 0x0A)
        cpu->A = value;
    else
        bus_write(cpu->bus, cpu->addr_abs, value);

    set_flag(cpu, Z, value == 0);
    set_flag(cpu, N, value & 0x80);

    return 0;
}

uint8_t cpu_inst_lsr(CPU *cpu)
{
    uint8_t value = cpu->opcode == 0x4A
                        ? cpu->A
                        : bus_read(cpu->bus, cpu->addr_abs);
    set_flag(cpu, C, value & 0x01); // Set carry flag if bit 0 is set
    value >>= 1;                    // Shift right

    if (cpu->opcode == 0x4A)
        cpu->A = value;
    else
        bus_write(cpu->bus, cpu->addr_abs, value);

    set_flag(cpu, Z, value == 0);
    set_flag(cpu, N, value & 0x80);

    return 0;
}

uint8_t cpu_inst_rol(CPU *cpu)
{
    uint8_t value = cpu->opcode == 0x2A
                        ? cpu->A
                        : bus_read(cpu->bus, cpu->addr_abs);
    bool carry_in = get_flag(cpu, C);
    set_flag(cpu, C, value & 0x80); // Set carry flag if bit 7 is set
    value <<= 1;                    // Shift left

    if (carry_in)
        value |= 0x01; // Set bit 0 if carry was set

    if (cpu->opcode == 0x2A)
        cpu->A = value;
    else
        bus_write(cpu->bus, cpu->addr_abs, value);

    set_flag(cpu, Z, value == 0);
    set_flag(cpu, N, value & 0x80);

    return 0;
}

uint8_t cpu_inst_ror(CPU *cpu)
{
    uint8_t value = cpu->opcode == 0x6A
                        ? cpu->A
                        : bus_read(cpu->bus, cpu->addr_abs);
    bool carry_in = get_flag(cpu, C);
    set_flag(cpu, C, value & 0x01); // Set carry flag if bit 0 is set
    value >>= 1;                    // Shift right

    if (carry_in)
        value |= 0x80; // Set bit 7 if carry was set

    if (cpu->opcode == 0x6A)
        cpu->A = value;
    else
        bus_write(cpu->bus, cpu->addr_abs, value);

    set_flag(cpu, Z, value == 0);
    set_flag(cpu, N, value & 0x80);

    return 0;
}

uint8_t cpu_inst_nop(CPU *cpu)
{
    (void)cpu; // NOP does nothing

    return 0;
}