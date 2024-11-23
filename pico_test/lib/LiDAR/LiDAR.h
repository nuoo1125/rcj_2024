#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "Pico-VL53L0X/Pico_VL53L0X.h"

class Pico_LiDAR {
public:
    bool init(uint8_t servo_pin, i2c_inst_t *i2c);
    bool startMearurement();
    bool stopMearurement();
    bool isDataReady();
    uint16_t readRange(uint8_t angle);
    void readAll();
private:
    uint8_t servo_pin;
    uint16_t servo_angle_min = 0;
    uint16_t servo_angle_max = 180;

    Pico_VL53L0X sensor;
    uint16_t servo_angle;

    uint16_t single_measurement;
    uint16_t distance[100];
};
