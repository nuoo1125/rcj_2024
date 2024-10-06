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
int ans = 0;
//typedef enum{
  //  car_left,
    //car_right,
    //car_turn,
   // car_serch,
   // car_hold,
    //car_throw
//}car_state;
void photo(){
    mcp3x08_init();
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
   // printf("%d\n",cds_data[0]);
    printf("%d\n",cds_data[1]);
    sleep_ms(500);
}
void linetrace(){//crossは交差点などの時にもう一段階判断する用　serchはサーチ
    photo();
    if(data[0] < shiki&&data[1]<shiki&&data[2]<shiki)cross();
    else if(data[2] < shiki&&data[3]<shiki&&data[4]<shiki)cross();   
 //   else if(data[0]>silver)serch();
    else{
        if(data[1]>shiki&&data[3]<shiki)stepper_slow(0,1);
        if(data[1]<shiki&&data[3]>shiki)stepper_slow(1,0);
        else stepper_slow(1,1);        
    }
}
void cross(){
    stepper_break();
    cds();
    if(cds_data[0]>green&&cds_data[1]>green)stepper_turn();
    else if(cds_data[0]>green)stepper_turn_left();
    else if(cds_data[1]>green)stepper_turn_right();
    else{
        stepper_angle(10,10);
        sleep_ms(1);
        photo();
        if(data[0]>shiki||data[1]<shiki||data[2]>shiki||data[3]>shiki||data[4]>shiki){
            stepper_angle(-10,-10);
            sleep_ms(1);//過去のデータをもってればここはなくてもいい
            photo();
            if(data[0] < shiki&&data[1]<shiki&&data[2]<shiki)stepper_turn_right();
            else if(data[2] < shiki&&data[3]<shiki&&data[4]<shiki)stepper_turn_left();
        }
    }
}//cross終了後はlinetrace()に戻す
void sw_init(){
    gpio_init(22);
    gpio_set_dir(22,GPIO_IN);
    gpio_pull_down(22);
}
void sw_do(){
    ans += 1;
    if(ans%4 == 1){
        led2_off();
        led3_off();
        led2_on();
    }
    if(ans%4 == 2){
        led3_off();
        led2_off();
        led3_on();
    }
    if(ans%4 == 3){
        led2_off();
        led3_off();
        led2_on();
        led3_on();
    }
    if(ans%4==0){
        led2_off();
        led3_off();        
    }
}
int main() {
    gpio_set_irq_enabled_with_callback(22, GPIO_IRQ_EDGE_RISE, true, &sw_do);
    stdio_init_all();
    stepper_setup();
    bozzer();
    sleep_ms(100);
    bozzer();
    // while(1){
        stepper_slow(1,1);
    // }
}