cmake_minimum_required(VERSION 3.12)

add_library(VL53L0X_API
        core/src/vl53l0x_api.cpp
        core/src/vl53l0x_api_calibration.cpp
        core/src/vl53l0x_api_core.cpp
        core/src/vl53l0x_api_ranging.cpp
        core/src/vl53l0x_api_strings.cpp
        platform/src/vl53l0x_platform.cpp
        platform/src/vl53l0x_i2c_comms.cpp
        Pico_VL53L0X.cpp
)
    
target_link_libraries(VL53L0X_API pico_stdlib hardware_i2c)