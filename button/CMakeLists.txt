cmake_minimum_required(VERSION 3.0)

add_executable(button.elf button.c)
target_link_libraries(button.elf opencm3_stm32f4)
add_custom_target(button.bin ALL ${CMAKE_OBJCOPY} -Obinary button.elf button.bin DEPENDS button.elf)
