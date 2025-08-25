#include "TempHumiCo2.h"
#include "Arduino.h"

//pin을 A4 , A5에 고정으로 해야하기에 매개변수 X

//SCL -> 우노 : A4 , 나노 : A5

//SDA -> 우노 : A5 , 나노 : A4
TempHumiCo2::TempHumiCo2() {
}

bool TempHumiCo2::begin() {
 
    return _scd4x.begin();
}

void TempHumiCo2::readSensor() {
    // 2초마다 데이터가 준비되므로, 루프는 짧게 유지
    if (_scd4x.startPeriodicMeasurement()) {
        _temperature = _scd4x.getTemperature();
        _co2 = _scd4x.getCO2();
        _humidity = _scd4x.getHumidity();
    }
}

float TempHumiCo2::getTemperature() {
    readSensor();
    return _temperature;
}

float TempHumiCo2::getHumidity() {
    readSensor();
    return _humidity;
}

uint16_t TempHumiCo2::getCo2() {
    readSensor();
    return _co2;
}