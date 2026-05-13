#include <stdio.h>
#include "cpu/cpu.h"
#include "bus/bus.h"
#include "instruction/instruction.h"

void test_cpu_reset(CPU *cpu);
void test_lda_execution(CPU *cpu);
void test_ldx_execution(CPU *cpu);
void test_sta_execution(CPU *cpu);
void test_address_modes(CPU *cpu);
void test_dex_execution(CPU *cpu);
void test_inx_execution(CPU *cpu);
void test_jmp_execution(CPU *cpu);

int main()
{
    CPU cpu = {0};
    Bus bus = {0};

    /*
    Program:

    LDX #$05      ; Load 5 into X
    INX          ; Increment X (X should now be 6)
    JMP $8000     ; Jump back to the start of the program (infinite loop)
    */

    // Reset vector points to 0x8000 where our test program is located
    bus_write(&bus, 0xFFFC, 0x00); // Reset vector low byte
    bus_write(&bus, 0xFFFD, 0x80); // Reset vector high byte

    bus_write(&bus, 0x8000, 0xA2); // LDX Immediate opcode
    bus_write(&bus, 0x8001, 0x05); // Value to load into X
    bus_write(&bus, 0x8002, 0xE8); // INX opcode
    bus_write(&bus, 0x8003, 0x4C); // JMP opcode
    bus_write(&bus, 0x8004, 0x02); // JMP address low byte
    bus_write(&bus, 0x8005, 0x80); // JMP address high byte

    cpu.bus = &bus;
    cpu_reset(&cpu);

    init_instructions_table();

    while (1)
    {
        do
        {
            cpu_step(&cpu);

            // Simple debugging output to show the state of the CPU after each instruction
            printf("A: %02X, X: %02X, Y: %02X, SP: %02X, PC: %04X, P: %02X, Cycles: %d\n",
                   cpu.A, cpu.X, cpu.Y, cpu.SP, cpu.PC, cpu.P, cpu.cycles);

            scanf("%*c"); // Wait for user input to step through instructions
        } while (cpu.cycles > 0); // Continue until cycles are consumed
    }

    return 0;
}