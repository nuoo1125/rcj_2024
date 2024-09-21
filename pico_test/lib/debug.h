#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
void led1(){
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN,1);
    sleep_ms(100);
    gpio_put(LED_PIN,0);
}
void led2(){
    gpio_init(27);
    gpio_set_dir(27,GPIO_OUT);
    gpio_put(27,1);
    sleep_ms(100);
    gpio_put(27,0);
}
void led3(){
    gpio_init(26);
    gpio_set_dir(26,GPIO_OUT);
    gpio_put(26,1);
    sleep_ms(100);
    gpio_put(26,0);
}
void bozzer(){
    gpio_init(1);
    gpio_set_dir(1,GPIO_OUT);
    gpio_put(1,1);
    sleep_ms(100);
    gpio_put(1,0);
}
