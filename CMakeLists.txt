cmake_minimum_required(VERSION 3.10)
project(Emulator-MOS6502 VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

if (MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /WX")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
endif()

add_executable(Emulator-MOS6502
    src/main.c
)

target_include_directories(
    Emulator-MOS6502 PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)