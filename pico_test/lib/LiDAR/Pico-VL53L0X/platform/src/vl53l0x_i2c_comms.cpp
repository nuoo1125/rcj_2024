#include "../../vl53l0x_def.h"
#include "../../vl53l0x_i2c_platform.h"

#include <stdio.h>

// #define I2C_DEBUG
/*
int VL53L0X_i2c_init(i2c_inst_t *bus) {
  i2c_init(bus, 200 * 1000);

  if (bus == i2c0) {
        gpio_set_function(VL53L0X_I2C0_SDA, GPIO_FUNC_I2C);
        gpio_set_function(VL53L0X_I2C0_SCL, GPIO_FUNC_I2C);
        gpio_pull_up(VL53L0X_I2C0_SDA);
        gpio_pull_up(VL53L0X_I2C0_SCL);
    } else if (bus == i2c1) {
        gpio_set_function(VL53L0X_I2C1_SDA, GPIO_FUNC_I2C);
        gpio_set_function(VL53L0X_I2C1_SCL, GPIO_FUNC_I2C);
        gpio_pull_up(VL53L0X_I2C1_SDA);
        gpio_pull_up(VL53L0X_I2C1_SCL);
    }
  return VL53L0X_ERROR_NONE;
}

int VL53L0X_write_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata,
                        uint32_t count, i2c_inst_t *i2c) {
  // i2c->beginTransmission(deviceAddress);
  // i2c->write(index);
  // i2c->write((uint8_t)pdata[0]);
  uint8_t buff[count + 1];
  buff[0] = index;
  for (int i = 0; i < count; i++) {
    buff[i + 1] = pdata[i];
  }
  i2c_write_blocking(i2c, deviceAddress, buff, count + 1, false);

#ifdef I2C_DEBUG
  printf("Writing %d bytes data to addr 0x%02X: ", count, index);

  printf("0x%02x :", index);
  for (int i = 0; i < count; i++) {
    printf("0x%02x, ", pdata[i]);
  }
  printf("\n");
#endif

  return VL53L0X_ERROR_NONE;
}

int VL53L0X_read_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata,
                       uint32_t count, i2c_inst_t *i2c) {
  // i2c->beginTransmission(deviceAddress);
  // i2c->write(index);
  // i2c->endTransmission();
  // i2c->requestFrom(deviceAddress, (byte)count);
  i2c_write_blocking(i2c, deviceAddress, &index, 1, true);
  i2c_read_blocking(i2c, deviceAddress, pdata, count, false);
#ifdef I2C_DEBUG
  printf("Reading %d bytes data from addr 0x%02X: ", count, index);
  for(int i = 0; i < count; i++) {
    printf("0x%02x, ", pdata[i]);
  }
  printf("\n");
#endif
  return VL53L0X_ERROR_NONE;
}

int VL53L0X_write_byte(uint8_t deviceAddress, uint8_t index, uint8_t data,
                       i2c_inst_t *i2c) {
  return VL53L0X_write_multi(deviceAddress, index, &data, 1, i2c);
}

int VL53L0X_write_word(uint8_t deviceAddress, uint8_t index, uint16_t data,
                       i2c_inst_t *i2c) {
  uint8_t buff[2];
  buff[1] = data & 0xFF;
  buff[0] = data >> 8;
  return VL53L0X_write_multi(deviceAddress, index, buff, 2, i2c);
}

int VL53L0X_write_dword(uint8_t deviceAddress, uint8_t index, uint32_t data,
                        i2c_inst_t *i2c) {
  uint8_t buff[4];

  buff[3] = data & 0xFF;
  buff[2] = data >> 8;
  buff[1] = data >> 16;
  buff[0] = data >> 24;

  return VL53L0X_write_multi(deviceAddress, index, buff, 4, i2c);
}

int VL53L0X_read_byte(uint8_t deviceAddress, uint8_t index, uint8_t *data,
                      i2c_inst_t *i2c) {
  return VL53L0X_read_multi(deviceAddress, index, data, 1, i2c);
}

int VL53L0X_read_word(uint8_t deviceAddress, uint8_t index, uint16_t *data,
                      i2c_inst_t *i2c) {
  uint8_t buff[2];
  int r = VL53L0X_read_multi(deviceAddress, index, buff, 2, i2c);

  uint16_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  *data = tmp;

  return r;
}

int VL53L0X_read_dword(uint8_t deviceAddress, uint8_t index, uint32_t *data,
                       i2c_inst_t *i2c) {
  uint8_t buff[4];
  int r = VL53L0X_read_multi(deviceAddress, index, buff, 4, i2c);

  uint32_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  tmp <<= 8;
  tmp |= buff[2];
  tmp <<= 8;
  tmp |= buff[3];

  *data = tmp;

  return r;
}
*/