#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "hardware/adc.h"

#define clock_l 18
#define direction_l  19
#define clock_r 16
#define direction_r 17 
#define reset 21 
void stepper_setup(){
    gpio_init(clock_l);
    gpio_init(clock_r);
    gpio_init(direction_l);
    gpio_init(direction_r);
    gpio_set_function(clock_l,GPIO_FUNC_PWM);
    gpio_set_function(clock_r,GPIO_FUNC_PWM);
    gpio_set_dir(direction_l,GPIO_OUT);
    gpio_set_dir(direction_r,GPIO_OUT);
}
void stepper_slow(bool forward_l,bool forward_r){
    if(forward_l == 1 && forward_r == 1){
        gpio_put(direction_l,1);
        gpio_put(direction_r,0);        
    }
    if(forward_l == 0 && forward_r == 1){
        gpio_put(direction_l,0);
        gpio_put(direction_r,0);        
    }
    if(forward_l == 0 && forward_r == 0){
        gpio_put(direction_l,0);
        gpio_put(direction_r,1);        
    }
    if(forward_l == 1 && forward_r == 0){
        gpio_put(direction_l,1);
        gpio_put(direction_r,1);        
    }
    uint slice_num_l = pwm_gpio_to_slice_num(clock_l);
    uint chan_l = pwm_gpio_to_channel(clock_l);
    pwm_set_clkdiv(slice_num_l,3500);
    pwm_set_wrap(slice_num_l,1250);
    pwm_set_chan_level(slice_num_l, chan_l, 500);
    uint slice_num_r = pwm_gpio_to_slice_num(clock_r);
    uint chan_r = pwm_gpio_to_channel(clock_r);
    pwm_set_clkdiv(slice_num_r,3500);
    pwm_set_wrap(slice_num_r, 1250);
    pwm_set_chan_level(slice_num_r, chan_r, 500);
    pwm_set_enabled(slice_num_l,true);
    pwm_set_enabled(slice_num_r, true);
}
void stepper_fast(bool forward_l,bool forward_r){
    if(forward_l == 1 && forward_r ==1){
        gpio_put(direction_l,1);
        gpio_put(direction_r,0);        
    }
    if(forward_l == 0 && forward_r ==1){
        gpio_put(direction_l,0);
        gpio_put(direction_r,0);
    }
    if(forward_l == 0 && forward_r == 0){
        gpio_put(direction_l,0);
        gpio_put(direction_r,1);        
    }
    if(forward_l == 1 && forward_r ==0){
        gpio_put(direction_l,1);
        gpio_put(direction_r,1);        
    }
    uint slice_num_l = pwm_gpio_to_slice_num(clock_l);
    uint chan_l = pwm_gpio_to_channel(clock_l);
    pwm_set_clkdiv(slice_num_l,3500);
    pwm_set_wrap(slice_num_l,1000);
    pwm_set_chan_level(slice_num_l, chan_l, 250);
    uint slice_num_r = pwm_gpio_to_slice_num(clock_r);
    uint chan_r = pwm_gpio_to_channel(clock_r);
    pwm_set_clkdiv(slice_num_r,3500);
    pwm_set_wrap(slice_num_r, 1000);
    pwm_set_chan_level(slice_num_r, chan_r, 250);
    pwm_set_enabled(slice_num_l,true);
    pwm_set_enabled(slice_num_r, true);
}
void stepper_angle(int16_t angle_l,int16_t angle_r){
    if(angle_l > 0 && angle_r >0){
        gpio_put(direction_l,1);
        gpio_put(direction_r,0);        
    }
    if(angle_l < 0 && angle_r >0){
        gpio_put(direction_l,0);
        gpio_put(direction_r,0);
        angle_l *= -1;   
    }
    if(angle_l < 0 && angle_r < 0){
        gpio_put(direction_l,0);
        gpio_put(direction_r,1); 
        angle_l *= -1;
        angle_r *= -1;       
    }
    if(angle_l >0 && angle_r < 0){
        gpio_put(direction_l,0);
        gpio_put(direction_r,1);        
        angle_r *= -1;
    }
    uint slice_num_l = pwm_gpio_to_slice_num(clock_l);
    uint chan_l = pwm_gpio_to_channel(clock_l);
    pwm_set_clkdiv(slice_num_l,3500);
    pwm_set_wrap(slice_num_l,499);
    pwm_set_chan_level(slice_num_l, chan_l, 250);
    uint slice_num_r = pwm_gpio_to_slice_num(clock_r);
    uint chan_r = pwm_gpio_to_channel(clock_r);
    pwm_set_clkdiv(slice_num_r,3500);
    pwm_set_wrap(slice_num_r, 499);
    pwm_set_chan_level(slice_num_r, chan_r, 250);
    pwm_set_enabled(slice_num_l, true);
    pwm_set_enabled(slice_num_r, true);
    sleep_ms((angle_l/1.8)*14);
    pwm_set_enabled(slice_num_l, false);
    pwm_set_enabled(slice_num_r, false);
}
