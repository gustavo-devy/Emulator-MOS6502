#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>
#include <stdbool.h>

// Forward declaration
typedef struct CPU CPU;

typedef enum Flags
{
    C = (1 << 0), // Carry Flag
    Z = (1 << 1), // Zero Flag
    I = (1 << 2), // Interrupt Disable
    D = (1 << 3), // Decimal Mode
    B = (1 << 4), // Break Command
    U = (1 << 5), // Unused
    V = (1 << 6), // Overflow Flag
    N = (1 << 7)  // Negative Flag
} Flags;

uint8_t get_flag(CPU *cpu, Flags f);
void set_flag(CPU *cpu, Flags f, bool v);

#endif // FLAGS_H