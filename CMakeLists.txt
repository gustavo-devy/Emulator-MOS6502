cmake_minimum_required(VERSION 3.10)
project(Emulator-MOS6502 VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

if (MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /WX")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
endif()

# Path to the source files
set(TEST_SOURCES
    tests/test_cpu_reset.c
    tests/test_lda_execution.c
    tests/test_ldx_execution.c
    tests/test_sta_execution.c
    tests/test_address_modes.c
)

add_executable(Emulator-MOS6502
    src/main.c
    src/bus/bus.c
    src/cpu/flags.c
    src/cpu/cpu.c
    src/instruction/instruction.c
    ${TEST_SOURCES}
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
)

target_include_directories(
    Emulator-MOS6502 PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)