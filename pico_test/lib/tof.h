#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "hardware/adc.h"
#define sda_1 8
#define scl_1 9
uint16_t distance(int i2c){
    uint8_t data[2];
    uint16_t distance;

    i2c_write_blocking(i2c0,i2c,0x03,1,true);
    i2c_read_blocking(i2c0,i2c,data,2,false);
    distance = (data[0]<<8)|data[1];
    return distance;
}