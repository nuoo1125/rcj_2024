#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"
#include "mcp3208/mcp3208.h"
#include "stepper/stepper.h"
#include "servo/servo.h"
#include "tof/tof.h"
#include "debagu/debagu.h"

#define silver 4000000000000000000
#define shiki 850
#define green_white 3600
#define green_black 3000
int cds_green[2];
int cds_red[2];
int data[6];
int switch_sum = 0;
void linetrace();
void serch();
typedef enum{
    car_left,
    car_right,
    car_turn,
    car_serch,
    car_hold,
    car_throw,
    car_cross,
    car_start
}car_state;
car_state car = car_start;
void photo(){
    gpio_put(red_led,0);
    for(int i=0;i<5;i++){
        data[i] = mcp3208_read(i+2);
    }
}
void cds(){
    gpio_put(red_led,1);
    sleep_ms(500);
    cds_red[0] = mcp3208_read(0);
    cds_red[1] = mcp3208_read(1);
    gpio_put(red_led,0);
    gpio_put(green_led,1);
    sleep_ms(500);
    cds_green[0] = mcp3208_read(0);
    cds_green[1] = mcp3208_read(1);
    gpio_put(green_led,0);
}
void serch(){
    led1_on();
    led2_on();
    led3_on();
    bozzer();
    led1_off();
    led2_off();
    led3_off();
}
void cross_half(){
    bozzer();
    stepper_break();
    sleep_ms(500);    
    cds();
    if(cds_red[0]>green_white&&cds_red[1]>green_white){//turn
        led1_on();
        stepper_turn();
        stepper_angle(200,200);
        led1_off();
        linetrace();
    }
    else if(cds_red[0]>green_white){//right
        led2_on();  
        stepper_angle(50,50);
        bozzer();
        stepper_right();
        led2_off();
        stepper_angle(200,200);
        linetrace();
    }
    else if(cds_red[1]>green_white){//left
        led3_on();
        stepper_angle(50,50);
        stepper_left();
        led3_off();
        stepper_angle(200,200);
        linetrace();

    }
    else{
        stepper_angle(200,200);
        photo();
        if(data[0] > shiki&&data[1] > shiki&&data[2] > shiki&&data[3] > shiki&&data[4] > shiki){
            stepper_angle(-200,-200);
            if(car = car_left){
                stepper_left();
            }        
            else{
                stepper_right();
            }
        }
        else{
            linetrace();
        }
    }
}
void cross(){
    bozzer();
    stepper_break();
    sleep_ms(500);
    cds();/*
    if(cds_green[0]<green_black&&cds_green[1]<green_black){
        stepper_angle(-200,-200);
        linetrace();
    }
    else if(cds_green[0]<green_black){
        stepper_angle(100,-100);
        linetrace();
    }
    else if(cds_green[1]<green_black){
        stepper_angle(-100,100);
        linetrace();
    }
    */
        if(cds_red[0]>green_white&&cds_red[1]>green_white){//turn
            led1_on();
            stepper_turn();
            stepper_angle(200,200);
            led1_off();
            linetrace();
        }
        else if(cds_red[0]>green_white){//right
            led2_on();
            stepper_angle(50,50);
            bozzer();
            stepper_right();
            led2_off();
            stepper_angle(200,200);
            linetrace();
        }
        else if(cds_red[1]>green_white){//left
            led3_on();
            stepper_angle(50,50);
            stepper_left();
            led3_off();
            stepper_angle(200,200);
            linetrace();
        }
        else{
            stepper_angle(100,100);
            linetrace();

        }
    }
    /*
    else{
        stepper_angle(100,100);
        photo();
        if(data[0]>shiki&data[1]>shiki&data[2]>shiki&data[3]>shiki&data[4]>shiki){
            stepper_angle(-100,-100);
            photo();
            if(data[0] < shiki&&data[1]<shiki&&data[2]<shiki){
                stepper_right();
            }
            else if(data[2] < shiki&&data[3]<shiki&&data[4]<shiki){
                stepper_left();//ちょっと前行く必要かるかも
            }
            linetrace();
        }
        else{
            linetrace();
        }
    }
    */
void linetrace(){
    while(1){//crossは交差点などの時にもう一段階判断する用　serchはサーチ
        photo();
        if(data[0] < shiki&&data[1]<shiki&&data[2]<shiki&&data[3]<shiki&&data[4]<shiki)cross();
        else if(data[0]<shiki&&data[1]<shiki&&data[2]<shiki){
            cross_half();
            car = car_right;
        }
        else if(data[2]<shiki&&data[3]<shiki&&data[4]<shiki){
            cross_half();
            car = car_left;
        }
        else if(data[0]>silver||data[1]>silver||data[2]>silver||data[3]>silver||data[4]>silver)serch();
        else{
            if(data[1]>shiki&&data[3]<shiki)stepper_slow(1,0);
            else if(data[1]<shiki&&data[3]>shiki)stepper_slow(0,1);
            else stepper_slow(1,1);
        }
    }
}
void sw_init(){
    gpio_init(22);
    gpio_set_dir(22,GPIO_IN);
    gpio_pull_down(22);
}
void sw_do(){
    if(switch_sum==0){
        linetrace();
        switch_sum += 1;
    }
    else{
        led3_on();
        sleep_ms(500);
        led3_off();
    }
}
int main() {
    gpio_set_irq_enabled_with_callback(22, GPIO_IRQ_EDGE_RISE, true, &sw_do);
    stdio_init_all();
    sw_init();
    bozzer();
    stepper_setup();
    mcp3x08_init();
    cds_init();
    linetrace();
}