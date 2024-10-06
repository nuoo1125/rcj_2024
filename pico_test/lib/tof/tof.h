#pragma once

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#define sda_1 8
#define scl_1 9

#ifdef __cplusplus
extern "C" {
#endif
uint16_t distance(int i2c);
#ifdef __cplusplus
}
#endif