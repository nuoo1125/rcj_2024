#include "pico/stdlib.h"
#include "hardware/i2c.h"
#define address 0x28
int camera_data[1];
int data[1];
void i2c_setup() {
    i2c_init(i2c1, 100*1000);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_pull_up(15);
    gpio_pull_up(14);
}
void i2c_send(uint8_t data){
    i2c_write_blocking(i2c1,address,data,1,false);
}
void i2c_receive(){
    i2c_read_blocking(i2c1, address, camera_data, 1, false);
}
