#include "stepper.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"

void stepper_setup(){
    gpio_set_function(clock_l,GPIO_FUNC_PWM);
    gpio_set_function(clock_r,GPIO_FUNC_PWM);
    gpio_init(direction_l);
    gpio_init(direction_r);
    gpio_init(reset);
    gpio_set_dir(direction_l,GPIO_OUT);
    gpio_set_dir(reset,GPIO_OUT);
    gpio_set_dir(direction_r,GPIO_OUT);
} 
void stepper_slow(bool forward_l,bool forward_r){
    if(forward_l == 1 && forward_r == 1){
        gpio_put(direction_l,0);
        gpio_put(direction_r,1);        
    }
    else if(forward_l == 0 && forward_r == 1){
        gpio_put(direction_l,0);
        gpio_put(direction_r,0);        
    }
    else if(forward_l == 0 && forward_r == 0){
        gpio_put(direction_l,1);
        gpio_put(direction_r,0);        
    }
    else{
        gpio_put(direction_l,0);
        gpio_put(direction_r,0);        
    }
    uint slice_num_l = pwm_gpio_to_slice_num(clock_l);
    uint chan_l = pwm_gpio_to_channel(clock_l);
    pwm_set_clkdiv(slice_num_l, 124);
    pwm_set_wrap(slice_num_l, 2000);
    pwm_set_chan_level(slice_num_l, chan_l, 1000);
    pwm_set_enabled(slice_num_l, true);
    uint slice_num_r = pwm_gpio_to_slice_num(clock_r);
    uint chan_r = pwm_gpio_to_channel(clock_r);
    pwm_set_clkdiv(slice_num_r, 124);
    pwm_set_wrap(slice_num_r, 2000);
    pwm_set_chan_level(slice_num_r, chan_r, 1000);
    pwm_set_enabled(slice_num_r, true);
}
void stepper_angle(int16_t angle_l,int16_t angle_r){
    if(angle_l > 0 && angle_r> 0){
        gpio_put(direction_l,0);
        gpio_put(direction_r,1);        
    }
    else if(angle_l < 0 && angle_r > 0){
        gpio_put(direction_l,0);
        gpio_put(direction_r,0);
        angle_l *= -1;
    }
    else if(angle_l < 0 && angle_r < 0){
        gpio_put(direction_l,1);
        gpio_put(direction_r,0);
        angle_l *= -1;
        angle_r *= -1;        
    }
    else{
        angle_r *= -1;
        gpio_put(direction_l,0);
        gpio_put(direction_r,0);        
    }
    uint slice_num_l = pwm_gpio_to_slice_num(clock_l);
    uint chan_l = pwm_gpio_to_channel(clock_l);
    pwm_set_clkdiv(slice_num_l, 124);
    pwm_set_wrap(slice_num_l, 2000);
    pwm_set_chan_level(slice_num_l, chan_l, 1000);
    uint slice_num_r = pwm_gpio_to_slice_num(clock_r);
    uint chan_r = pwm_gpio_to_channel(clock_r);
    pwm_set_clkdiv(slice_num_r, 124);
    pwm_set_wrap(slice_num_r, 2000);
    pwm_set_chan_level(slice_num_r, chan_r, 1000);
    pwm_set_enabled(slice_num_r, true);
    pwm_set_enabled(slice_num_l, true);
    sleep_ms(angle_l);
    pwm_set_enabled(slice_num_l, false);
    pwm_set_enabled(slice_num_r, false);
}
void stepper_break(){
    uint slice_num_r = pwm_gpio_to_slice_num(clock_r);
    uint slice_num_l = pwm_gpio_to_slice_num(clock_l);
    pwm_set_enabled(slice_num_l,false);
    pwm_set_enabled(slice_num_r, false);
}
void stepper_turn(){
    stepper_angle(1180,-1180);
}
void stepper_right(){
    stepper_angle(-591.5,591.5);
}
void stepper_left(){
    stepper_angle(591.5,-591.5);
}