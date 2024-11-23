#include "LiDAR.h"

bool Pico_LiDAR::init(uint8_t pin, i2c_inst_t *i2c) {
    if (!sensor.begin(VL53L0X_I2C_ADDR, i2c,  
                        Pico_VL53L0X::VL53L0X_Sense_config_t::VL53L0X_SENSE_DEFAULT))
    {
        return false;
    }
    return true;
}

bool Pico_LiDAR::startMearurement() {
    return sensor.startRangeContinuous(25);
}

bool Pico_LiDAR::stopMearurement() {
    if(sensor.stopMeasurement() == VL53L0X_ERROR_NONE)return true;
    return false;
}

bool Pico_LiDAR::isDataReady(){
    return sensor.isRangeComplete();
}

uint16_t Pico_LiDAR::readRange(uint8_t angle) {
    return sensor.readRange();
}

