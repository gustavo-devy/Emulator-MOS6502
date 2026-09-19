#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "flags.h"
#include "bus/bus.h"

typedef struct CPU
{
    uint8_t A;   // Accumulator
    uint8_t X;   // X Register
    uint8_t Y;   // Y Register
    uint8_t SP;  // Stack Pointer
    uint16_t PC; // Program Counter
    Flags P;     // Processor Status (Flags)

    Bus *bus; // Pointer to the bus for memory access

    uint16_t addr_abs;
    uint16_t addr_rel;
    uint8_t opcode;
    uint8_t cycles;        // Cycles for the current instruction
    uint32_t total_cycles; // Total cycles executed
} CPU;

void cpu_step(CPU *cpu);
void cpu_reset(CPU *cpu);

// Instruction implementations
uint8_t cpu_inst_lda(CPU *cpu);
uint8_t cpu_inst_ldx(CPU *cpu);
uint8_t cpu_inst_ldy(CPU *cpu);
uint8_t cpu_inst_sta(CPU *cpu);
uint8_t cpu_inst_stx(CPU *cpu);
uint8_t cpu_inst_sty(CPU *cpu);
uint8_t cpu_inst_tax(CPU *cpu);
uint8_t cpu_inst_txa(CPU *cpu);
uint8_t cpu_inst_tay(CPU *cpu);
uint8_t cpu_inst_tya(CPU *cpu);
uint8_t cpu_inst_tsx(CPU *cpu);
uint8_t cpu_inst_txs(CPU *cpu);
uint8_t cpu_inst_adc(CPU *cpu);
uint8_t cpu_inst_sbc(CPU *cpu);
uint8_t cpu_inst_dex(CPU *cpu);
uint8_t cpu_inst_inx(CPU *cpu);
uint8_t cpu_inst_inc(CPU *cpu);
uint8_t cpu_inst_dec(CPU *cpu);
uint8_t cpu_inst_dey(CPU *cpu);
uint8_t cpu_inst_iny(CPU *cpu);
uint8_t cpu_inst_pha(CPU *cpu);
uint8_t cpu_inst_pla(CPU *cpu);
uint8_t cpu_inst_php(CPU *cpu);
uint8_t cpu_inst_plp(CPU *cpu);
uint8_t cpu_inst_cmp(CPU *cpu);
uint8_t cpu_inst_cpx(CPU *cpu);
uint8_t cpu_inst_cpy(CPU *cpu);
uint8_t cpu_inst_bne(CPU *cpu);
uint8_t cpu_inst_beq(CPU *cpu);
uint8_t cpu_inst_bpl(CPU *cpu);
uint8_t cpu_inst_bmi(CPU *cpu);
uint8_t cpu_inst_bvc(CPU *cpu);
uint8_t cpu_inst_bvs(CPU *cpu);
uint8_t cpu_inst_bcc(CPU *cpu);
uint8_t cpu_inst_bcs(CPU *cpu);
uint8_t cpu_inst_jsr(CPU *cpu);
uint8_t cpu_inst_rts(CPU *cpu);
uint8_t cpu_inst_rti(CPU *cpu);
uint8_t cpu_inst_brk(CPU *cpu);
uint8_t cpu_inst_jmp(CPU *cpu);
uint8_t cpu_inst_clc(CPU *cpu);
uint8_t cpu_inst_sec(CPU *cpu);
uint8_t cpu_inst_cli(CPU *cpu);
uint8_t cpu_inst_sei(CPU *cpu);
uint8_t cpu_inst_cld(CPU *cpu);
uint8_t cpu_inst_sed(CPU *cpu);
uint8_t cpu_inst_clv(CPU *cpu);
uint8_t cpu_inst_and(CPU *cpu);
uint8_t cpu_inst_ora(CPU *cpu);
uint8_t cpu_inst_eor(CPU *cpu);
uint8_t cpu_inst_bit(CPU *cpu);
uint8_t cpu_inst_asl(CPU *cpu);
uint8_t cpu_inst_lsr(CPU *cpu);
uint8_t cpu_inst_rol(CPU *cpu);
uint8_t cpu_inst_ror(CPU *cpu);
uint8_t cpu_inst_nop(CPU *cpu);

#endif // CPU_H