add_library(tof tof.c)

target_link_libraries(tof  pico_stdlib hardware_i2c hardware_pwm hardware_adc hardware_spi hardware_i2c)