#cmake_minimum_required(VERSION 3.0)

add_executable(pwm.elf pwm.cpp)
target_link_libraries(pwm.elf opencm3_stm32f4)
add_bin_from_elf(pwm.bin pwm.elf)
