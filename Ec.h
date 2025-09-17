#ifndef Ec_H
#define Ec_H

#include <Arduino.h>

class Ec {
public:
    Ec(int pin);
    void begin();
    float readEcValue(float temperature);
    void calibrate(float analogValue, float temp);

private:
    int _ecPin;
    float _calibrationValue;
    float _calibrationTemp;
};

#endif