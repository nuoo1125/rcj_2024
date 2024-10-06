add_library(servo servo.c)

target_link_libraries(servo hardware_pwm pico_stdlib)