#include "tof.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "hardware/adc.h"
uint16_t distance(int i2c){
    uint8_t data[2];
    uint16_t distance;

    i2c_write_blocking(i2c0,i2c,NULL,0,true);
    i2c_read_blocking(i2c0,i2c,data,2,false);
    distance = (data[0]<<8)|data[1];
    return distance;
}
