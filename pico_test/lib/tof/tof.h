#pragma once
#ifndef TOF_H
#define TOF_H

#include <stdint.h>
#include <stdbool.h>

// I2C設定
#define VL53L0X_ADDR 0x29  // I2Cアドレス

// 初期化関数
bool VL53L0X_init(void);

// レジスタ操作関数
void VL53L0X_writeReg(uint8_t reg, uint8_t value);
void VL53L0X_writeReg16Bit(uint8_t reg, uint16_t value);
void VL53L0X_writeReg32Bit(uint8_t reg, uint32_t value);
uint8_t VL53L0X_readReg(uint8_t reg);
uint16_t VL53L0X_readReg16Bit(uint8_t reg);
uint32_t VL53L0X_readReg32Bit(uint8_t reg);
// 測定関数
uint16_t VL53L0X_readRangeContinuousMillimeters(void);

#endif // TOF_H
