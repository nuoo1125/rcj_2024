add_library(stepper stepper.c)

target_link_libraries(stepper  pico_stdlib hardware_i2c hardware_pwm hardware_adc hardware_spi hardware_i2c)