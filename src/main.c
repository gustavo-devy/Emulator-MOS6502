#include <stdio.h>
#include "cpu/cpu.h"
#include "bus/bus.h"
#include "instruction/instruction.h"

void test_cpu_reset(CPU *cpu);
void test_lda_execution(CPU *cpu);
void test_ldx_execution(CPU *cpu);
void test_ldy_execution(CPU *cpu);
void test_sta_execution(CPU *cpu);
void test_stx_execution(CPU *cpu);
void test_sty_execution(CPU *cpu);
void test_address_modes(CPU *cpu);
void test_dex_execution(CPU *cpu);
void test_inx_execution(CPU *cpu);
void test_dey_execution(CPU *cpu);
void test_iny_execution(CPU *cpu);
void test_cmp_execution(CPU *cpu);
void test_cpx_execution(CPU *cpu);
void test_cpy_execution(CPU *cpu);
void test_bne_execution(CPU *cpu);
void test_beq_execution(CPU *cpu);
void test_jmp_execution(CPU *cpu);
void test_clc_execution(CPU *cpu);

int main()
{
    CPU cpu = {0};
    Bus bus = {0};

    cpu.bus = &bus;

    init_instructions_table();
    test_clc_execution(&cpu);

    return 0;
}