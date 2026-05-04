#include "cpu/cpu.h"
#include "cpu/flags.h"

uint8_t get_flag(CPU *cpu, Flags f)
{
    return ((cpu->P & f) > 0) ? 1 : 0;
}

void set_flag(CPU *cpu, Flags f, bool v)
{
    if (v)
        cpu->P |= f; // Set the flag
    else
        cpu->P &= ~f; // Clear the flag
}