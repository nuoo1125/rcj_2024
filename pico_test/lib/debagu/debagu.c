#include "pico/stdlib.h"
#include "debagu.h"
void led1_on(){
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN,1);
}
void led1_off(){
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN,0);
}
void led2_on(){
    gpio_init(0);
    gpio_set_dir(0,GPIO_OUT);
    gpio_put(0,1);
}
void led2_off(){
    gpio_init(0);
    gpio_set_dir(0,GPIO_OUT);
    gpio_put(0,0);
}
void led3_on(){
    gpio_init(1);
    gpio_set_dir(1,GPIO_OUT);
    gpio_put(1,1);
}
void led3_off(){
    gpio_init(1);
    gpio_set_dir(1,GPIO_OUT);
    gpio_put(1,0);
}
void bozzer(){
    gpio_init(6);
    gpio_set_dir(6,GPIO_OUT);
    gpio_put(6,1);
    sleep_ms(100);
    gpio_put(6,0);
}