cmake_minimum_required(VERSION 3.0)

add_executable(rand.elf rand.c)
target_link_libraries(rand.elf opencm3_stm32f4)
add_bin_from_elf(rand.bin rand.elf)
