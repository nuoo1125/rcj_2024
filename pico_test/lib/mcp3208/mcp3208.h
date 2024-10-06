#pragma once

#include "pico/stdlib.h"

#define SPI_PIN_SCK  2
#define SPI_PIN_MOSI 3
#define SPI_PIN_MISO 4
#define SPI_PIN_CS   5

#define SPI_PORT spi0

#ifdef __cplusplus
extern "C" {
#endif
void mcp3x08_init();
uint16_t mcp3208_read(uint8_t ch);
#ifdef __cplusplus
}
#endif