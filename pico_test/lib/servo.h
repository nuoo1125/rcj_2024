#include "pico/stdlib.h"
#include "hardware/pwm.h"

void set_servo_angle(uint gpio, uint slice_num, float angle) {
    float pulse_width = 0.5f + (angle / 180.0f) * 2.0f;
    uint16_t level = (uint16_t)((pulse_width / 20.0f) * pwm_get_wrap(slice_num));
    pwm_set_gpio_level(gpio, level);
}
