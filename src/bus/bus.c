#include "bus/bus.h"

void bus_write(Bus *bus, uint16_t address, uint8_t data)
{
    bus->memory[address] = data;
}

uint8_t bus_read(Bus *bus, uint16_t address)
{
    return bus->memory[address];
}