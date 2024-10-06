#include "servo.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
//33 to 180
#define gpio 11
#define gpio2 10
void sg90_angle(float angle) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    gpio_set_function(gpio2,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num = pwm_gpio_to_slice_num(gpio);
    uint32_t pwm_slice_num2 = pwm_gpio_to_slice_num(gpio2);
    pwm_set_wrap(pwm_slice_num, 25000); 
    pwm_set_clkdiv(pwm_slice_num, 64.0f);
    pwm_set_wrap(pwm_slice_num2, 25000); 
    pwm_set_clkdiv(pwm_slice_num2, 64.0f);
    
    float duty_cycle = 0.5 + (angle * 2.0 / 180.0); 
    uint16_t level = (uint16_t)(duty_cycle * 25000.0 / 20.0); 

    pwm_set_chan_level(pwm_slice_num, pwm_gpio_to_channel(gpio), level);
    pwm_set_chan_level(pwm_slice_num2, pwm_gpio_to_channel(gpio2), level);
    pwm_set_enabled(pwm_slice_num, true);
    pwm_set_enabled(pwm_slice_num2, true);
}
void mg996r(float angle){
    gpio_set_function(7,GPIO_FUNC_PWM);
    uint32_t pwm_slice_num3 = pwm_gpio_to_slice_num(7);
    pwm_set_wrap(pwm_slice_num3, 25000); 
    pwm_set_clkdiv(pwm_slice_num3, 64.0f);
    float duty_cycle = 0.5 + (angle * 2.0 / 180.0); 
    uint16_t level = (uint16_t)(duty_cycle * 25000.0 / 20.0);
    pwm_set_chan_level(pwm_slice_num3, pwm_gpio_to_channel(7), level);
    pwm_set_enabled(pwm_slice_num3,true);
}
void up(){}
void down(){}
void open(){}
void close(){}