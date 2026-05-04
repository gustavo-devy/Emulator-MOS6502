#ifndef BUS_H
#define BUS_H

#include <stdint.h>

#define MEMORY_SIZE 65536

typedef struct Bus
{
    uint8_t memory[MEMORY_SIZE];
} Bus;

void bus_write(Bus *bus, uint16_t address, uint8_t data);
uint8_t bus_read(Bus *bus, uint16_t address);

#endif // BUS_H