#pragma once

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#define gpio 11
#define gpio2 10
#ifdef __cplusplus
extern "C" {
#endif
void sg90_angle(float angle);
#ifdef __cplusplus
}
#endif