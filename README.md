# stm32f4-discovery-cmake
STM32F4 Discovery samples with CMake

## Prerequisite
* [CMake](https://cmake.org/) 3.0 or later
* [GCC ARM Embedded](https://launchpad.net/gcc-arm-embedded) 4.9 or later

## Build
```
$ git clone https://github.com/yuya-oc/stm32f4-discovery-cmake.git
$ cd stm32f4-discovery-cmake
$ git submodule update --init
$ cmake -DCMAKE_TOOLCHAIN_FILE=Toolchain-arm-none-eabi.cmake .
$ make libopencm3
$ make
```
