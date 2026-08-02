#include "bus/bus.h"

void bus_init(Bus *bus)
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        bus->memory[i] = 0xEA; // Initialize memory with NOP instruction (0xEA)
    }
}

void bus_write(Bus *bus, uint16_t address, uint8_t data)
{
    bus->memory[address] = data;
}

uint8_t bus_read(Bus *bus, uint16_t address)
{
    return bus->memory[address];
}