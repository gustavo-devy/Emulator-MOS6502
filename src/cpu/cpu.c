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

        cpu->cycles = inst.cycles; // Set the cycles for the instruction

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