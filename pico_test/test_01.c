#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "lib/mcp3208.h"
#include "lib/stepper.h"
#include "lib/servo.h"
#include "lib/tof.h"
＃include "lib/debug.h"
#define shiki 800
int data[6];
typedef enum{
    car_left;
    car_right;
    car_turn;
    car_serch;
    car_hold;
    car_throw;
}car_state;
void photo(){
    mcp3x08_init();
    for(int i=2;i<8;i++){
        data[i-2] = mcp3208_read(i);
    }
}
void linetrace(){
    photo();
    if((data[0]>shiki)&&(data[5]<shiki))stepper_slow(true,false);
    if((data[0]<shiki)&&(data[5]>shiki))stepper_slow(false,true);
    else stepper_slow(true,true);
    sleep_ms(500);
}

void main(){
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN,1);
    stepper_setup();
    stepper_slow(true,true);
}
