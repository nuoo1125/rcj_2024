#Set the mimum required version of CMake
cmake_minimum_required(VERSION 3.12)

#Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
include_directories(../lib)

#Set the project name, the programming language
project(project1 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

#Initialize the SDK
pico_sdk_init()

#Add an executable target to be build from the source files
add_executable(pico_test main.c)

#Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(pico_test pico_stdlib hardware_spi hardware_adc hardware_i2c hardware_pwm)

#Enable USB output, disable UART output
pico_enable_stdio_usb(pico_test 1)
pico_enable_stdio_uart(pico_test 0)

#Create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(pico_test)