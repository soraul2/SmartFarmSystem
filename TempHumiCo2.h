#ifndef TempHumiCo2_h
#define TempHumiCo2_h

#include <Wire.h>
#include "SparkFun_SCD4x_Arduino_Library.h"

class TempHumiCo2 {

private:
    uint16_t _co2;
    float _temperature;
    float _humidity;
    SCD4x _scd4x;

public:
    TempHumiCo2();
    bool begin();
    void readSensor();
    float getTemperature();
    float getHumidity();
    uint16_t getCo2();
};

#endif