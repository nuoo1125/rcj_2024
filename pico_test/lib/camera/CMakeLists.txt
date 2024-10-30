add_library(camera camera.c)

target_link_libraries(camera  pico_stdlib hardware_i2c hardware_pwm hardware_adc hardware_spi hardware_i2c)