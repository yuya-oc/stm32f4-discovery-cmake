#cmake_minimum_required(VERSION 3.0)

add_executable(cpp.elf cpp.cpp)
target_link_libraries(cpp.elf opencm3_stm32f4)
add_bin_from_elf(cpp.bin cpp.elf)
