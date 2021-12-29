
cmake_minimum_required(VERSION 3.12)

set(CC  arm-none-eabi-gcc)
set(CXX arm-none-eabi-g++)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(kbd-mapper)

pico_sdk_init()

add_compile_definitions(__RP2040__)

add_subdirectory(third-part)

add_subdirectory(src)
