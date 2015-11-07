cmake_minimum_required(VERSION 3.0)

add_executable(rand.elf rand.c)
target_link_libraries(rand.elf opencm3_stm32f4)
add_custom_target(rand.bin ALL ${CMAKE_OBJCOPY} -Obinary rand.elf rand.bin DEPENDS rand.elf)
