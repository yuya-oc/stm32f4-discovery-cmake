#cmake_minimum_required(VERSION 3.0)

add_executable(printf.elf printf.c)
target_link_libraries(printf.elf opencm3_stm32f4)
add_bin_from_elf(printf.bin printf.elf)
