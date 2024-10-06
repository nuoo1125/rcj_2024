add_executable(PICO_TEST main.c)

target_include_directories(PICO_TEST PRIVATE ../lib)

target_link_libraries(PICO_TEST debagu mcp3208 servo stepper tof)
target_link_libraries(PICO_TEST pico_stdlib hardware_pwm hardware_spi hardware_i2c)

pico_enable_stdio_usb(PICO_TEST 1)
pico_enable_stdio_uart(PICO_TEST 0)

pico_add_extra_outputs(PICO_TEST)