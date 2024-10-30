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

#define silver 2000
#define shiki 800
#define green 1000//適当
#define green_led 12
#define red_led 13
int cds_data[2];
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
    for(int i=0;i<5;i++){
        data[i] = mcp3208_read(i+2);
        printf("%d",i);
        printf("  ");
        printf("%d\n",data[i]);
    }
}

void cds_init(){
    gpio_init(red_led);
    gpio_set_dir(red_led,GPIO_OUT);
    gpio_init(green_led);
    gpio_set_dir(green_led,GPIO_OUT);
    mcp3x08_init();
}
void cds(){
    gpio_put(green_led,1);
    cds_data[0] = mcp3208_read(0);
    cds_data[1] = mcp3208_read(1);
    printf("%d\n",cds_data[0]);
    printf("%d\n",cds_data[1]);
    sleep_ms(500);
}
void serch(){
    bozzer();
}
void cross(){
    stepper_break();
    cds();
    if(cds_data[0]>green&&cds_data[1]>green){//turn
        stepper_turn();
        linetrace();
    }
    else if(cds_data[0]>green){//right
        stepper_right();
        linetrace();
    }
    else if(cds_data[1]>green){//left
        stepper_left();
        linetrace();
    }
    else{
        stepper_angle(10,10);
        photo();
        if(data[0]>shiki&data[1]>shiki&data[2]>shiki&data[3]>shiki&data[4]>shiki){
            stepper_angle(-10,-10);
            if(data[0] < shiki&&data[1]<shiki&&data[2]<shiki){
                stepper_right();
            }
            else if(data[2] < shiki&&data[3]<shiki&&data[4]<shiki){
                stepper_left();//ちょっと前行く必要かるかも
                }
        linetrace();
        }
        else if(data[2]<shiki){
            linetrace();
        }
    }
    
}
void linetrace(){//crossは交差点などの時にもう一段階判断する用　serchはサーチ
    photo();
    if(data[0] < shiki&&data[1]<shiki&&data[2]<shiki)cross();
    else if(data[2] < shiki&&data[3]<shiki&&data[4]<shiki)cross();
    else if(data[0]>silver||data[1]>silver||data[2]>silver||data[3]>silver||data[4]>silver)serch();
    else{
        if(data[1]>shiki&&data[3]<shiki)stepper_slow(1,0);
        if(data[1]<shiki&&data[3]>shiki)stepper_slow(0,1);
        else stepper_slow(1,1);        
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
        printf("touch");
    }
}

int main() {//silverチェックをタイムでチェックする
    gpio_set_irq_enabled_with_callback(22, GPIO_IRQ_EDGE_RISE, true, &sw_do);
    sw_init();
    stdio_init_all();
    bozzer();
    stepper_setup();
    mcp3x08_init();
    cds_init();
    stepper_slow(1,0);
}