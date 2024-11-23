cmake_minimum_required(VERSION 3.12)

add_subdirectory(Pico-VL53L0X)

add_library(Pico_LiDAR
    LiDAR.cpp
)

target_include_directories(Pico_LiDAR PRIVATE ../SERVO)

target_link_libraries(Pico_LiDAR VL53L0X_API)
target_link_libraries(Pico_LiDAR pico_stdlib hardware_i2c hardware_pwm)
