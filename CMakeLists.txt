cmake_minimum_required(VERSION 3.10)
project(Emulator-MOS6502 VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

if (MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /WX")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
endif()

set(TEST_SOURCES
    tests/test_cpu_reset.c
    tests/test_lda_execution.c
    tests/test_ldx_execution.c
    tests/test_sta_execution.c
    tests/test_address_modes.c
    tests/test_dex_execution.c
    tests/test_inx_execution.c
    tests/test_jmp_execution.c
    tests/test_stx_execution.c
    tests/test_bne_execution.c
    tests/test_beq_execution.c
    tests/test_ldy_execution.c
    tests/test_sty_execution.c
    tests/test_cmp_execution.c
    tests/test_cpx_execution.c
    tests/test_cpy_execution.c
    tests/test_adc_execution.c
    tests/test_sbc_execution.c
    tests/test_dey_execution.c
    tests/test_iny_execution.c
    tests/test_clc_execution.c
    tests/test_sec_execution.c
    tests/test_pha_execution.c
    tests/test_pla_execution.c
    tests/test_jsr_execution.c
    tests/test_rts_execution.c
    tests/tests_and_modes.c
    tests/test_ora_execution.c
    tests/test_eor_execution.c
    tests/test_bit_execution.c
    tests/test_inc_dec_execution.c
    tests/test_tax_execution.c
    tests/test_txa_execution.c
    tests/test_tay_execution.c
    tests/test_tya_execution.c
    tests/test_tsx_execution.c
    tests/test_txs_execution.c
    tests/test_php_execution.c
    tests/test_plp_execution.c
    tests/test_asl_execution.c
    tests/test_lsr_execution.c
    tests/test_rol_execution.c
    tests/test_ror_execution.c
)

add_executable(Emulator-MOS6502
    src/main.c
    src/bus/bus.c
    src/cpu/flags.c
    src/cpu/cpu.c
    src/instruction/instruction.c
    ${TEST_SOURCES}
)

target_include_directories(
    Emulator-MOS6502 PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)