#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define VL53L0X_I2C_SDA 8
#define VL53L0X_I2C_SCL 9


// initialize I2C
int VL53L0X_i2c_init(i2c_inst_t *i2c);
int VL53L0X_write_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata,
                        uint32_t count, i2c_inst_t *i2c);
int VL53L0X_read_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata,
                       uint32_t count, i2c_inst_t *i2c);
int VL53L0X_write_byte(uint8_t deviceAddress, uint8_t index, uint8_t data,
                       i2c_inst_t *i2c);
int VL53L0X_write_word(uint8_t deviceAddress, uint8_t index, uint16_t data,
                       i2c_inst_t *i2c);
int VL53L0X_write_dword(uint8_t deviceAddress, uint8_t index, uint32_t data,
                        i2c_inst_t *i2c);
int VL53L0X_read_byte(uint8_t deviceAddress, uint8_t index, uint8_t *data,
                      i2c_inst_t *i2c);
int VL53L0X_read_word(uint8_t deviceAddress, uint8_t index, uint16_t *data,
                      i2c_inst_t *i2c);
int VL53L0X_read_dword(uint8_t deviceAddress, uint8_t index, uint32_t *data,
                       i2c_inst_t *i2c);
