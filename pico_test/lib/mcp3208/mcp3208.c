#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "mcp3208.h"

#define SPI_PIN_SCK  2
#define SPI_PIN_MOSI 3
#define SPI_PIN_MISO 4
#define SPI_PIN_CS   5

#define SPI_PORT spi0

void mcp3x08_init(){
    spi_init(SPI_PORT, 1000 * 1000);
    gpio_set_function(SPI_PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(SPI_PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(SPI_PIN_MOSI, GPIO_FUNC_SPI);

    gpio_init(SPI_PIN_CS);
    gpio_set_dir(SPI_PIN_CS, GPIO_OUT);
    gpio_put(SPI_PIN_CS, 1);
}

uint16_t mcp3208_read(uint8_t ch){
    uint8_t reg[3] = {0b00000110, 0x00, 0x00};
    reg[0] = reg[0] | (0b00000001 & (ch >> 2));
    reg[1] = 0b11000000 & (ch << 6);

    uint8_t buf[3];
    gpio_put(SPI_PIN_CS,0);
    spi_write_read_blocking(SPI_PORT, reg, buf, 3);
    gpio_put(SPI_PIN_CS,1);

    return (buf[1] & 0b00001111) << 8 | buf[2];
}
void cds_init(){
    gpio_init(green_led);
    gpio_set_dir(green_led,GPIO_OUT);
    mcp3x08_init();
}