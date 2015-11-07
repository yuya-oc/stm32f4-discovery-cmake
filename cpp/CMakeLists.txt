#cmake_minimum_required(VERSION 3.0)

add_executable(cpp.elf cpp.cpp)
target_link_libraries(cpp.elf opencm3_stm32f4)
add_custom_target(cpp.bin ALL ${CMAKE_OBJCOPY} -Obinary cpp.elf cpp.bin DEPENDS cpp.elf)
